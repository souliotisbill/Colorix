#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "colorfiller.h"
#include <QQmlContext>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    ImageProvider *imageProvider = new ImageProvider();

    QtQuick2ApplicationViewer viewer;
    viewer.engine()->addImageProvider(QLatin1String("imageprovider"), imageProvider);
    viewer.setMainQmlFile(QStringLiteral("qml/ColoringAlgo/main.qml"));
    viewer.rootContext()->setContextProperty("imageProvider", (QObject *)imageProvider);

    viewer.showExpanded();

    return app.exec();
}
