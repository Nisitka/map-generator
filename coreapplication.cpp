#include "coreapplication.h"

#include <QThread>

CoreApplication::CoreApplication()
{
    visualMap = new visualMapWidget;
    map = new Map;
    mapBuilder = new generator;

    //
    QObject::connect(
                     map,       SIGNAL(built(QVector <bool*>*)),
                     visualMap, SLOT(setMap(QVector <bool*>*))
                     );

    QObject::connect(
                     map,        SIGNAL(built(QVector <bool*>*)),
                     mapBuilder, SLOT(setMap(QVector <bool*>*))
                     );

    //
    QObject::connect(
                     visualMap,  SIGNAL(runBuilt()),
                     mapBuilder, SLOT(builtBlocks())
                     );
    QObject::connect(
                     visualMap,  SIGNAL(runBuilt()),
                     map,        SLOT(clear())
                     );

    QObject::connect(
                     mapBuilder, SIGNAL(readyLayer()),
                     visualMap,  SLOT(readyLayer())
                     );
    QObject::connect(
                     mapBuilder, SIGNAL(update()),
                     visualMap,  SLOT(repaintMap())
                     );
    map->buildMap();
    //mapBuilder->setMap(map->getBlocks());

    QThread* builtThread = new QThread;
    mapBuilder->moveToThread(builtThread);
    builtThread->start();
}

void CoreApplication::run()
{
    visualMap->show();
}
