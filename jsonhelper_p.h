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


#ifndef JSONHELPER_P_H
#define JSONHELPER_P_H

// Warning
//
// This file exists for the convenience
// of other classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file jsonhelper_p.h
 * @short JSON helper macros
 */

/**
 * @internal
 * @typedef JsonObject
 * @short A JSON object
 */
/**
 * @internal
 * @typedef JsonValue
 * @short A JSON value
 */
/**
 * @internal
 * @typedef JsonArray
 * @short A JSON array
 */
/**
 * @internal
 * @def JSON_IS_ARRAY
 * @short Check if a JSON value is an array
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_IS_BOOL
 * @short Check if a JSON value is a boolean
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_IS_DOUBLE
 * @short Check if a JSON value is a double
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_IS_OBJECT
 * @short Check if a JSON value is an object
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_IS_STRING
 * @short Check if a JSON value is a string
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_GET_ARRAY
 * @short Get an array from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_GET_BOOL
 * @short Get a boolean from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_GET_DOUBLE
 * @short Get a double from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_GET_OBJECT
 * @short Get an object from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_GET_STRING
 * @short Get a string from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def JSON_GET_DOCUMENT
 * @short Extract a JSON document from a data source
 * @param jsonDocument name of the JSON document variable.
 * @param dataSource data source, as a QIODevice.
 */
/**
 * @internal
 * @def JSON_CHECK_DOCUMENT
 * @short Check if a JSON document is valid
 * @param jsonDocument JSON document to check.
 */
/**
 * @internal
 * @def JSON_GET_ROOT_OBJECT
 * @short Get the root object from the JSON document
 * @param jsonDocument JSON document.
 * @param rootObject name of the root object.
 */

#include <QtCore/QtGlobal>

// Includes
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtCore/QVariantMap>
#include <QtCore/QVariantList>
#include <qjson/parser.h>
#else
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#endif


#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
// Typedefs
typedef QVariantMap JsonObject;
typedef QVariant JsonValue;
typedef QVariantList JsonArray;
// Checks
#define JSON_IS_ARRAY(jsonValue) jsonValue.type() == QVariant::List
#define JSON_IS_BOOL(jsonValue) jsonValue.type() == QVariant::Bool
#define JSON_IS_DOUBLE(jsonValue) jsonValue.type() == QVariant::Double
#define JSON_IS_OBJECT(jsonValue) jsonValue.type() == QVariant::Map
#define JSON_IS_STRING(jsonValue) jsonValue.type() != QVariant::List && \
        jsonValue.type() != QVariant::Bool && jsonValue.type() != QVariant::Double &&\
        jsonValue.type() != QVariant::Map
// Getters
#define JSON_GET_ARRAY(jsonValue) jsonValue.toList()
#define JSON_GET_BOOL(jsonValue) jsonValue.toBool()
#define JSON_GET_DOUBLE(jsonValue) jsonValue.toDouble()
#define JSON_GET_OBJECT(jsonValue) jsonValue.toMap()
#define JSON_GET_STRING(jsonValue) jsonValue.toString()
// Helpers
#define JSON_GET_DOCUMENT(jsonDocument, dataSource) QJson::Parser parser; \
    QVariant jsonDocument = parser.parse(dataSource)
#define JSON_CHECK_DOCUMENT(jsonDocument) jsonDocument.isValid()
#define JSON_GET_ROOT_OBJECT(rootObject, jsonDocument) \
    JsonObject rootObject = jsonDocument.toMap()
#else
// Typedefs
typedef QJsonObject JsonObject;
typedef QJsonValue JsonValue;
typedef QJsonArray JsonArray;
// Checks
#define JSON_IS_ARRAY(jsonValue) jsonValue.isArray()
#define JSON_IS_BOOL(jsonValue) jsonValue.isBool()
#define JSON_IS_DOUBLE(jsonValue) jsonValue.isDouble()
#define JSON_IS_OBJECT(jsonValue) jsonValue.isObject()
#define JSON_IS_STRING(jsonValue) jsonValue.isString()
// Getters
#define JSON_GET_ARRAY(jsonValue) jsonValue.toArray()
#define JSON_GET_BOOL(jsonValue) jsonValue.toBool()
#define JSON_GET_DOUBLE(jsonValue) jsonValue.toDouble()
#define JSON_GET_OBJECT(jsonValue) jsonValue.toObject()
#define JSON_GET_STRING(jsonValue) jsonValue.toString()
// Helpers
#define JSON_GET_DOCUMENT(jsonDocument, dataSource) \
    QJsonDocument jsonDocument = QJsonDocument::fromJson(dataSource->readAll())
#define JSON_CHECK_DOCUMENT(jsonDocument) !jsonDocument.isNull()
#define JSON_GET_ROOT_OBJECT(rootObject, jsonDocument) \
    JsonObject rootObject = jsonDocument.object()
#endif

#endif // JSONHELPER_P_H
