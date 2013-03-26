#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/qdeclarative.h>
#include <QFile>
#include <QTextStream>
#include "sailfishapplication.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(Sailfish::createUninitializedView());

    QFile file("/home/nemo/Documents/changelog");
    file.open(QIODevice::ReadOnly | QIODevice::Text);


    QTextStream in(&file);
    QString line = in.readAll();

    view.data()->rootContext()->setContextProperty("CHANGELOG", line);
    Sailfish::initializeView(view.data(), "main.qml");
    Sailfish::showView(view.data());

    return app->exec();
}
