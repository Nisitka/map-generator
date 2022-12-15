#ifndef MAP_H
#define MAP_H

#include <QObject>

#include <QVector>

class Map : public QObject
{
    Q_OBJECT
signals:
    void built(QVector <bool*>* pLayers);

public slots:
    void clear();

public:
    Map();
    QVector <bool*>* getBlocks();


    static bool getBlock(QVector <bool*>* layers,
                         int X, int Y, int Z);
    static int getHeight(QVector <bool*>* layers,
                         int X, int Y);

    void buildMap();

    static const int height = 200; // кратно 15
    static const int width = 100;
    static const int length = 100;

private:
    // наличие блоков хранится в слоях
    QVector <bool*> layers;
};

#endif // MAP_H
