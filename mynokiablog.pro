# The name of your app
TARGET = mynokiablog

# C++ sources
SOURCES += main.cpp

# C++ headers
HEADERS +=

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
    pages/Search.qml

