#include "visualmapwidget.h"
#include "ui_visualmapwidget.h"

#include <QDebug>

#include "map.h"

visualMapWidget::visualMapWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::visualMapWidget)
{
    ui->setupUi(this);
    areaDraw = new areaDrawWidget(810, 810);

    ui->areaDrawLayout->addWidget(areaDraw);
    areaDraw->Clear();
    //clearArea();

    ui->builtProgressBar->setValue(0);
    connect(
            ui->startBuiltButton, SIGNAL(clicked()),
            this,                 SLOT(startBuilt())
            );

    ui->infoProgressLabel->clear();
}

void visualMapWidget::startBuilt()
{
    ui->builtProgressBar->setMaximum(Map::height);
    progress = 0;
    ui->infoProgressLabel->setText(infoStrings[built]);

    emit runBuilt();
}

void visualMapWidget::readyLayer()
{
    progress++;
    ui->builtProgressBar->setValue(progress);
}

void visualMapWidget::setMap(QVector <bool*>* pLayers_)
{
    areaDraw->setMap(pLayers_);
}

void visualMapWidget::repaintMap()
{
    progress = 0;
    ui->builtProgressBar->setValue(progress);
    ui->infoProgressLabel->setText(infoStrings[draw]);

    areaDraw->drawMap();
    ui->infoProgressLabel->clear();
}

visualMapWidget::~visualMapWidget()
{
    delete ui;
}

