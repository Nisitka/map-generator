#ifndef VISUALMAPWIDGET_H
#define VISUALMAPWIDGET_H

#include <QWidget>

#include "areadrawwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class visualMapWidget; }
QT_END_NAMESPACE

class visualMapWidget : public QWidget
{
    Q_OBJECT

signals:
    void runBuilt();

public slots:
    void repaintMap();

    void setMap(QVector <bool*>* pLayers);

    void startBuilt();
    void readyLayer();

public:
    visualMapWidget(QWidget *parent = nullptr);

    ~visualMapWidget();

private:
    areaDrawWidget* areaDraw;

    enum infoProgress {built, draw};
    QVector <QString> infoStrings = {"Генерация карты...",
                                     "Отрисовка карты..."
                                     };

    int progress;

    Ui::visualMapWidget *ui;
};
#endif // VISUALMAPWIDGET_H
