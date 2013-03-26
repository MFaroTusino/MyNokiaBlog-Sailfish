
#include <QApplication>
#include <QDir>
#include <QGraphicsObject>

#ifdef DESKTOP
#include <QGLWidget>
#endif

#include <QDeclarativeComponent>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeView>
//#include <QNetworkAccessManager>

#ifdef HAS_BOOSTER
#include <MDeclarativeCache>
#endif

#include "sailfishapplication.h"

QApplication *Sailfish::createApplication(int &argc, char **argv)
{
#ifdef HAS_BOOSTER
    return MDeclarativeCache::qApplication(argc, argv);
#else
    return new QApplication(argc, argv);
#endif
}

QDeclarativeView *Sailfish::createUninitializedView()
{
    QDeclarativeView *view;
#ifdef HAS_BOOSTER
    view = MDeclarativeCache::qDeclarativeView();
#else
    view = new QDeclarativeView;
#endif

    bool isDesktop = qApp->arguments().contains("-desktop");

    if (isDesktop) {
#ifdef DESKTOP
        view->setViewport(new QGLWidget);
#endif
    }

    return view;
}

void Sailfish::initializeView(QDeclarativeView *view, const QString &file)
{
    bool isDesktop = qApp->arguments().contains("-desktop");

    QString path;
    if (isDesktop) {
        path = qApp->applicationDirPath() + QDir::separator();
    } else {
        path = QString(DEPLOYMENT_PATH);
    }
    view->setSource(QUrl::fromLocalFile(path + file));
}

void Sailfish::showView(QDeclarativeView* view) {
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    bool isDesktop = qApp->arguments().contains("-desktop");

    if (isDesktop) {
        view->setFixedSize(480, 854);
        view->rootObject()->setProperty("_desktop", true);
        view->show();
    } else {
        view->setAttribute(Qt::WA_OpaquePaintEvent);
        view->setAttribute(Qt::WA_NoSystemBackground);
        view->viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
        view->viewport()->setAttribute(Qt::WA_NoSystemBackground);

        view->showFullScreen();
    }
}
