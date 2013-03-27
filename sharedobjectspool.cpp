#include "sharedobjectspool.h"

static const char *ID_KEY = "id";

SharedObjectsPool::SharedObjectsPool(QObject *parent) :
    QObject(parent)
{
}

Author * SharedObjectsPool::createAuthor(const JsonObject &jsonObject)
{
    QString id = JSON_GET_STRING(jsonObject.value(ID_KEY));
    if (m_authors.contains(id)) {
        return m_authors.value(id);
    }

    Author *author = Author::create(jsonObject);
    m_authors.insert(id, author);
    return author;
}

