#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

#include <QObject>

#include "visualmapwidget.h"
#include "generator.h"

// ядро приложения
class CoreApplication
{
public:
    CoreApplication();

    void run();

private:
    // отображение изменений карты
    visualMapWidget* visualMap;

    Map* map;
    generator* mapBuilder;
};

#endif // COREAPPLICATION_H
