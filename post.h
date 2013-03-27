/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Jolla Ltd. nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef POST_H
#define POST_H

#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include "author.h"
#include "jsonhelper_p.h"

class SharedObjectsPool;
class Post: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString slug READ slug NOTIFY slugChanged)
    Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString content READ content NOTIFY contentChanged)
    Q_PROPERTY(QString excerpt READ excerpt NOTIFY excerptChanged)
    Q_PROPERTY(QDateTime date READ date NOTIFY dateChanged)
    Q_PROPERTY(QDateTime modified READ modified NOTIFY modifiedChanged)
    Q_PROPERTY(Author * author READ author NOTIFY authorChanged)
public:
    explicit Post(QObject *parent = 0);
    static Post * create(const JsonObject &data, SharedObjectsPool *pool, QObject *parent = 0);
    QString id() const;
    QString slug() const;
    QUrl url() const;
    QString title() const;
    QString content() const;
    QString excerpt() const;
    QDateTime date() const;
    QDateTime modified() const;
    Author * author() const;
public slots:
    void update(const JsonObject &data, SharedObjectsPool *pool);
signals:
    void idChanged();
    void slugChanged();
    void urlChanged();
    void titleChanged();
    void contentChanged();
    void excerptChanged();
    void dateChanged();
    void modifiedChanged();
    void authorChanged();
private:
    static bool isValid(const JsonObject &data);
    void setData(const JsonObject &data, SharedObjectsPool *pool, bool signalChange = true);
    QString m_id;
    QString m_slug;
    QUrl m_url;
    QString m_title;
    QString m_content;
    QString m_excerpt;
    QDateTime m_date;
    QDateTime m_modified;
    Author *m_author;
};

Q_DECLARE_METATYPE(Post*)

#endif // POST_H
