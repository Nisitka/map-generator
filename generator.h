#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>

#include "map.h"

class generator : public QObject
{
    Q_OBJECT
signals:
    void update();
    void readyLayer();

public slots:
    void setMap(QVector <bool*>* pLayers);
    void builtBlocks();

public:
    generator();

    static bool P(int p = 500);

private:
    //void law1(int idLayer, );

    int sumLive(bool*);
    void builtRandBlock(bool*);
    void removeRandBlock(bool*);

    QVector <bool*>* pLayers;

    int epochs = 45;
};

#endif // GENERATOR_H
