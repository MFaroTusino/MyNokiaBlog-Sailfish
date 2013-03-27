#ifndef POSTMODEL_H
#define POSTMODEL_H

#include <QtCore/QAbstractListModel>

class QNetworkAccessManager;
class QNetworkReply;
class SharedObjectsPool;
class Post;
class PostModel: public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
public:
    enum PostModelRoles {
        PostRole
    };

    explicit PostModel(QObject *parent = 0);
    /**
     * @short Count
     * @return number of rows in this model.
     */
    int count() const;
    bool loading() const;
    QString error() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
public slots:
    void load(const QUrl &url, const QByteArray &arguments = QByteArray());
    void loadMore(const QUrl &url);
signals:
    void countChanged();
    void loadingChanged();
    void errorChanged();
    void loaded();
protected:
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    /**
     * @brief Role names
     * @return role names.
     */
    QHash<int, QByteArray> roleNames() const;
#endif
private:
    void setError(const QString &error);
    QNetworkAccessManager *m_networkAccessManager;
    QNetworkReply *m_reply;
    SharedObjectsPool *m_sharedObjectsPool;
    QList<Post *> m_posts;
    QString m_error;
    int m_page;
    int m_count;
private slots:
    void slotFinished();

};

#endif // POSTMODEL_H
