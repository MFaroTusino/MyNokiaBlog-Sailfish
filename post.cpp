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

#include "post.h"
#include "sharedobjectspool.h"
#include "datetimeformat_p.h"

static const char *POST_ID_KEY = "id";
static const char *POST_SLUG_KEY = "slug";
static const char *POST_URL_KEY = "url";
static const char *POST_TITLE_KEY = "title";
static const char *POST_CONTENT_KEY = "content";
static const char *POST_EXCERPT_KEY = "excerpt";
static const char *POST_DATE_KEY = "date";
static const char *POST_MODIFIED_KEY = "modified";
static const char *POST_AUTHOR_KEY = "author";

Post::Post(QObject *parent)
    : QObject(parent)
{
}

Post * Post::create(const JsonObject &data, SharedObjectsPool *pool, QObject *parent)
{
    if (!isValid(data)) {
        return 0;
    }
    Post * post = new Post(parent);
    post->setData(data, pool, false);
    return post;
}

QString Post::id() const
{
    return m_id;
}

QString Post::slug() const
{
    return m_slug;
}

QUrl Post::url() const
{
    return m_url;
}

QString Post::title() const
{
    return m_title;
}

QString Post::content() const
{
    return m_content;
}

QString Post::excerpt() const
{
    return m_excerpt;
}

QDateTime Post::date() const
{
    return m_date;
}

QDateTime Post::modified() const
{
    return m_modified;
}

Author  * Post::author() const
{
    return m_author;
}

void Post::update(const JsonObject &data, SharedObjectsPool *pool)
{
    if (!isValid(data)) {
        return;
    }
    setData(data, pool);
}

bool Post::isValid(const JsonObject &data)
{
    if (!data.contains(POST_ID_KEY)) {
        return false;
    }
    if (!data.contains(POST_SLUG_KEY)) {
        return false;
    }
    if (!data.contains(POST_URL_KEY)) {
        return false;
    }
    if (!data.contains(POST_TITLE_KEY)) {
        return false;
    }
    if (!data.contains(POST_CONTENT_KEY)) {
        return false;
    }
    if (!data.contains(POST_EXCERPT_KEY)) {
        return false;
    }
    if (!data.contains(POST_DATE_KEY)) {
        return false;
    }
    if (!data.contains(POST_MODIFIED_KEY)) {
        return false;
    }
    if (!data.contains(POST_AUTHOR_KEY)) {
        return false;
    }
    return true;
}

void Post::setData(const JsonObject &data, SharedObjectsPool *pool, bool signalChange)
{
    QString id = JSON_GET_STRING(data.value(POST_ID_KEY));
    QString slug = JSON_GET_STRING(data.value(POST_SLUG_KEY));
    QString urlString = JSON_GET_STRING(data.value(POST_URL_KEY));
    QUrl url = QUrl(urlString);
    QString title = JSON_GET_STRING(data.value(POST_TITLE_KEY));
    QString content = JSON_GET_STRING(data.value(POST_CONTENT_KEY));
    QString excerpt = JSON_GET_STRING(data.value(POST_EXCERPT_KEY));
    QString dateString = JSON_GET_STRING(data.value(POST_DATE_KEY));
    QDateTime date = QDateTime::fromString(dateString, DATE_TIME_FORMAT);
    QString modifiedString = JSON_GET_STRING(data.value(POST_MODIFIED_KEY));
    QDateTime modified = QDateTime::fromString(modifiedString, DATE_TIME_FORMAT);
    JsonObject authorObject = JSON_GET_OBJECT(data.value(POST_AUTHOR_KEY));
    Author *author = pool->createAuthor(authorObject);
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
    if (m_url != url) {
        m_url = url;
        if (signalChange) {
            emit urlChanged();
        }
    }
    if (m_title != title) {
        m_title = title;
        if (signalChange) {
            emit titleChanged();
        }
    }
    if (m_content != content) {
        m_content = content;
        if (signalChange) {
            emit contentChanged();
        }
    }
    if (m_excerpt != excerpt) {
        m_excerpt = excerpt;
        if (signalChange) {
            emit excerptChanged();
        }
    }
    if (m_date != date) {
        m_date = date;
        if (signalChange) {
            emit dateChanged();
        }
    }
    if (m_modified != modified) {
        m_modified = modified;
        if (signalChange) {
            emit modifiedChanged();
        }
    }
    if (m_author != author) {
        m_author = author;
        if (signalChange) {
            emit authorChanged();
        }
    }
}
