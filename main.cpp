#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/qdeclarative.h>
#include <QJson>

#include "sailfishapplication.h"
#include "author.h"
#include "post.h"
#include "postmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(Sailfish::createUninitializedView());

    // Register QML types
    qmlRegisterType<Author>("BlogViewer", 1, 0, "Author");
    qmlRegisterType<Post>("BlogViewer", 1, 0, "Post");
    qmlRegisterType<PostModel>("BlogViewer", 1, 0, "PostModel");

    // Read the changelog
    QFile file("/home/nemo/Documents/changelog");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line = in.readAll();
    view.data()->rootContext()->setContextProperty("CHANGELOG", line);

    Sailfish::initializeView(view.data(), "main.qml");
    Sailfish::showView(view.data());

    return app->exec();
}
