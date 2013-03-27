#ifndef SHAREDOBJECTSPOOL_H
#define SHAREDOBJECTSPOOL_H

#include <QtCore/QObject>
#include "author.h"

class SharedObjectsPool : public QObject
{
    Q_OBJECT
public:
    explicit SharedObjectsPool(QObject *parent = 0);
    Author * createAuthor(const JsonObject &jsonObject);
private:
    QMap<QString, Author *> m_authors;

};

#endif // SHAREDOBJECTSPOOL_H
