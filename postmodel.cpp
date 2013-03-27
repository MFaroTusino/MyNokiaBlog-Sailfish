#include "postmodel.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "post.h"
#include "sharedobjectspool.h"
#include "jsonhelper_p.h"

static const char *STATUS_KEY = "status";
static const char *COUNT_KEY = "count";
static const char *COUNT_TOTAL_KEY = "count_total";
static const char *PAGES_KEY = "pages";
static const char *POSTS_KEY = "posts";

static const char *USER_AGENT = "Mozilla/5.0 (iPhone; CPU iPhone OS 5_0 like Mac OS X) \
AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9A334 Safari/7534.48.3";

PostModel::PostModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_networkAccessManager(new QNetworkAccessManager(this))
    , m_reply(0)
    , m_sharedObjectsPool(new SharedObjectsPool(this))
    , m_page(0)
    , m_count(0)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    setRoleNames(roleNames());
#endif
}

int PostModel::count() const
{
    return rowCount();
}

bool PostModel::loading() const
{
    return (m_reply != 0);
}

QString PostModel::error() const
{
    return m_error;
}

QUrl PostModel::api() const
{
    return m_api;
}

QString PostModel::method() const
{
    return m_method;
}

int PostModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_posts.count();
}

QVariant PostModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    Post *post = m_posts.at(row);

    switch (role) {
    case PostRole:
        return QVariant::fromValue(post);
        break;
    default:
        return QVariant();
        break;
    }
}

void PostModel::setApi(const QUrl &api)
{
    if (m_api != api) {
        m_api = api;
        emit apiChanged();
    }
}

void PostModel::setMethod(const QString &method)
{
    if (m_method != method) {
        m_method = method;
        emit methodChanged();
    }
}

void PostModel::load()
{
    if (m_reply) {
        return;
    }

    if (m_api.isEmpty()) {
        return;
    }

    if (m_method.isEmpty()) {
        return;
    }

    QUrl url = m_api;
    QString path = url.path();
    path.append(QString("/%1/").arg(m_method));
    url.setPath(path);

    m_page = 1;
    m_count = 0;

    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    qDeleteAll(m_posts);
    m_posts.clear();
    emit countChanged();
    endRemoveRows();

    QNetworkRequest request (url);
    request.setRawHeader("User-Agent", USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    m_reply = m_networkAccessManager->post(request, QByteArray());
    connect(m_reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    emit loadingChanged();
}

void PostModel::loadMore()
{
    if (m_reply) {
        return;
    }

    if (m_api.isEmpty()) {
        return;
    }

    if (m_method.isEmpty()) {
        return;
    }

    if (m_count == 0) {
        return;
    }

    QUrl url = m_api;
    QString path = url.path();
    path.append(QString("/%1/").arg(m_method));
    url.setPath(path);

    m_page ++;
    QByteArray arguments = QByteArray("count=");
    arguments.append(QByteArray::number(m_count));
    arguments.append("&page=");
    arguments.append(QByteArray::number(m_page));

    QNetworkRequest request (url);
    request.setRawHeader("User-Agent", USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_reply = m_networkAccessManager->post(request, arguments);
    connect(m_reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    emit loadingChanged();
}

QHash<int, QByteArray> PostModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(PostRole, "post");
    return roles;
}

void PostModel::setError(const QString &error)
{
    if (m_error != error) {
        m_error = error;
        emit errorChanged();
    }
}

void PostModel::slotFinished()
{
    if (m_reply->error() != QNetworkReply::NoError) {
        setError("Network error: " + m_reply->errorString());
        m_reply->deleteLater();
        m_reply = 0;
        emit loadingChanged();
        emit loaded();
        return;
    }

    JSON_GET_DOCUMENT(jsonDocument, m_reply);
    m_reply->deleteLater();
    m_reply = 0;
    if (!JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Invalid JSON document got from server");

        emit loadingChanged();
        emit loaded();
        return;
    }

    JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);
    if (!rootObject.contains(STATUS_KEY)
        || !rootObject.contains(COUNT_KEY)
        || !rootObject.contains(COUNT_TOTAL_KEY)
        || !rootObject.contains(PAGES_KEY)
        || !rootObject.contains(POSTS_KEY)) {
        setError("The JSON document do not contain correct fields");
        emit loadingChanged();
        emit loaded();
        return;
    }

    QString status = JSON_GET_STRING(rootObject.value(STATUS_KEY));
    if (status != "ok") {
        setError("API reported bad status");
        emit loadingChanged();
        emit loaded();
        return;
    }

    QList<Post *> newPosts;
    m_count = JSON_GET_STRING(rootObject.value(COUNT_KEY)).toInt();
    JsonArray postArray = JSON_GET_ARRAY(rootObject.value(POSTS_KEY));
    foreach (JsonValue post, postArray) {
        newPosts.append(Post::create(JSON_GET_OBJECT(post), m_sharedObjectsPool, this));
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + newPosts.count() - 1);
    m_posts.append(newPosts);
    emit countChanged();
    endInsertRows();

    emit loadingChanged();
    emit loaded();
}
