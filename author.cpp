/*
* Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
*
* You may use this file under the terms of the BSD license as follows:
*
* "Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in
* the documentation and/or other materials provided with the
* distribution.
* * Neither the name of Jolla Ltd. nor the names of its contributors
* may be used to endorse or promote products derived from this
* software without specific prior written permission.
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

#include "author.h"

static const char *AUTHOR_ID_KEY = "id";
static const char *AUTHOR_SLUG_KEY = "slug";
static const char *AUTHOR_NAME_KEY = "name";
static const char *AUTHOR_FIRST_NAME_KEY = "first_name";
static const char *AUTHOR_LAST_NAME_KEY = "last_name";
static const char *AUTHOR_NICKNAME_KEY = "nickname";
static const char *AUTHOR_URL_KEY = "url";
static const char *AUTHOR_DESCRIPTION_KEY = "description";

Author::Author(QObject *parent)
    : QObject(parent)
{
}

Author * Author::create(const JsonObject &data, QObject *parent)
{
    if (!isValid(data)) {
        return 0;
    }
    Author * author = new Author(parent);
    author->setData(data, false);
    return author;
}

QString Author::id() const
{
    return m_id;
}

QString Author::slug() const
{
    return m_slug;
}

QString Author::name() const
{
    return m_name;
}

QString Author::firstName() const
{
    return m_firstName;
}

QString Author::lastName() const
{
    return m_lastName;
}

QString Author::nickname() const
{
    return m_nickname;
}

QUrl Author::url() const
{
    return m_url;
}

QString Author::description() const
{
    return m_description;
}

void Author::update(const JsonObject &data)
{
    if (!isValid(data)) {
        return;
    }
    setData(data);
}

bool Author::isValid(const JsonObject &data)
{
    if (!data.contains(AUTHOR_ID_KEY)) {
        return false;
    }
    if (!data.contains(AUTHOR_SLUG_KEY)) {
        return false;
    }
    if (!data.contains(AUTHOR_NAME_KEY)) {
        return false;
    }
    if (!data.contains(AUTHOR_FIRST_NAME_KEY)) {
        return false;
    }
    if (!data.contains(AUTHOR_LAST_NAME_KEY)) {
        return false;
    }
    if (!data.contains(AUTHOR_NICKNAME_KEY)) {
        return false;
    }
    if (!data.contains(AUTHOR_URL_KEY)) {
        return false;
    }
    if (!data.contains(AUTHOR_DESCRIPTION_KEY)) {
        return false;
    }
    return true;
}

void Author::setData(const JsonObject &data, bool signalChange)
{
    QString id = JSON_GET_STRING(data.value(AUTHOR_ID_KEY));
    QString slug = JSON_GET_STRING(data.value(AUTHOR_SLUG_KEY));
    QString name = JSON_GET_STRING(data.value(AUTHOR_NAME_KEY));
    QString firstName = JSON_GET_STRING(data.value(AUTHOR_FIRST_NAME_KEY));
    QString lastName = JSON_GET_STRING(data.value(AUTHOR_LAST_NAME_KEY));
    QString nickname = JSON_GET_STRING(data.value(AUTHOR_NICKNAME_KEY));
    QString urlString = JSON_GET_STRING(data.value(AUTHOR_URL_KEY));
    QUrl url = QUrl(urlString);
    QString description = JSON_GET_STRING(data.value(AUTHOR_DESCRIPTION_KEY));
    if (m_id != id) {
        m_id = id;
        if (signalChange) {
            emit idChanged();
        }
    }
    if (m_slug != slug) {
        m_slug = slug;
        if (signalChange) {
            emit slugChanged();
        }
    }
    if (m_name != name) {
        m_name = name;
        if (signalChange) {
            emit nameChanged();
        }
    }
    if (m_firstName != firstName) {
        m_firstName = firstName;
        if (signalChange) {
            emit firstNameChanged();
        }
    }
    if (m_lastName != lastName) {
        m_lastName = lastName;
        if (signalChange) {
            emit lastNameChanged();
        }
    }
    if (m_nickname != nickname) {
        m_nickname = nickname;
        if (signalChange) {
            emit nicknameChanged();
        }
    }
    if (m_url != url) {
        m_url = url;
        if (signalChange) {
            emit urlChanged();
        }
    }
    if (m_description != description) {
        m_description = description;
        if (signalChange) {
            emit descriptionChanged();
        }
    }
}
