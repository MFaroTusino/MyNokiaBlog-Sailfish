# The name of your app
TARGET = mynokiablog
QT += network

lessThan(QT_MAJOR_VERSION, 5) {
    CONFIG += link_pkgconfig
    PKGCONFIG += QJson
}

# C++ sources
SOURCES += main.cpp \
    author.cpp \
    post.cpp \
    sharedobjectspool.cpp \
    postmodel.cpp \
    posthelper.cpp \
    posthelper.cpp \
    postmodel.cpp \
    sharedobjectspool.cpp \

# C++ headers
HEADERS += \
    jsonhelper_p.h \
    author.h \
    post.h \
    sharedobjectspool.h \
    datetimeformat_p.h \
    postmodel.h \
    posthelper.h \
    posthelper.h \
    postmodel.h \
    sharedobjectspool.h \

# QML files and folders
qml.files = *.qml pages cover main.qml

# The .desktop file
desktop.files = mynokiablog.desktop

# Please do not modify the following line.
include(sailfishapplication/sailfishapplication.pri)

OTHER_FILES = \
    pages/About.qml \
    pages/Changelog.qml \
    pages/ContactUs.qml \
    rpm/mynokiablog.yaml \
    pages/Index.qml \
    pages/Search.qml \
    pages/PostPage.qml \

