#include "map.h"

#include <QDebug>

Map::Map()
{

}

void Map::buildMap()
{
    // первый слой всегда существует
    layers.append(new bool[width*length]);
    bool* pLayer = layers.last();
    for (int j=0; j<width*length; j++)
    {
        pLayer[j] =  true;
    }

    for (int i=1; i<height; i++)
    {
        layers.append(new bool[width*length]);

        pLayer = layers.last();
        for (int j=0; j<width*length; j++)
        {
            pLayer[j] = false;
        }
    }

    emit built(&layers);
}

void Map::clear()
{
    for (int i=1; i<height; i++)
    {
        for (int j=0; j<width*length; j++)
        {
            layers[i][j] = false;
        }
    }
}

QVector <bool*>* Map::getBlocks()
{
    return &layers;
}

bool Map::getBlock(QVector <bool*>* layers_, int X, int Y, int Z)
{
    return *(layers_->at(Z) + width*Y + X);
}

int Map::getHeight(QVector<bool *> *layers, int X, int Y)
{
    int h = height - 1;

    while (!*(layers->at(h)+ width*Y + X))
    {
        h--;
    }

    return h;
}
