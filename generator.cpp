#include "generator.h"

generator::generator()
{

}

void generator::setMap(QVector <bool*>* pLayers_)
{
    pLayers = pLayers_;

    //builtBlocks();
}

void generator::builtBlocks()
{
    int countLayers = pLayers->size();

    // начинаем с 1-го слоя (0-й всегда заполнен)
    for (int i=1; i<countLayers; i++)
    {
        // рандомно бросаем блоки на нижний слой
        for (int j=0; j<Map::width * Map::length; j++)
        {
            if (pLayers->at(i-1)[j] && 330 > rand()%1000)
            {
                pLayers->at(i)[j] = true;
            }
        }

        // выполняем все правила каждую эпоху
        bool* layer = pLayers->at(i);
        for (int j=0; j<epochs; j++)
        {
            // для случанйых живых клеток
            for (int k=0; k<Map::length * Map::width; k++)
            {
                // выбираем случайный блок
                bool* newBlock = layer + (1 + rand()%(Map::length-2)) * Map::width + 1 + rand()%(Map::width-2);

                // если блок существует, то выполняем следующие правила:
                if (*newBlock)
                {
                    // 1)
                    if (sumLive(newBlock) >= 3) builtRandBlock(newBlock);

                    // 2)
                    if (sumLive(newBlock) <= 2) *newBlock = false;
                }
            }
        }

        emit readyLayer();
    }

    emit update();
}

void generator::removeRandBlock(bool* block)
{
    switch (rand()%4)
    {
        case 0:
            block[1] = false;
            break;
        case 1:
            block[-1] = false;
            break;
        case 2:
            block[Map::width] = false;
            break;
        case 3:
            block[-Map::width] = false;
            break;
    }
}

int generator::sumLive(bool* block)
{
    int numLived = 0;
    if (block[1]) numLived++;
    if (block[-1]) numLived++;
    if (block[Map::width]) numLived++;
    if (block[-Map::width]) numLived++;

    if (block[Map::width + 1]) numLived++;
    if (block[Map::width - 1]) numLived++;
    if (block[-Map::width + 1]) numLived++;
    if (block[-Map::width - 1]) numLived++;

    return numLived;
}

void generator::builtRandBlock(bool* block)
{
    switch (rand()%4)
    {
        case 0:
            block[1] = P(850);
            break;
        case 1:
            block[-1] = P(850);
            break;
        case 2:
            block[Map::width] = P(850);
            break;
        case 3:
            block[-Map::width] = P(850);
            break;
    }

}

bool generator::P(int p)
{
    return p > rand()%1000;
}

//void generator::law1(int idLayer)
//{
//    bool* layer = pLayers->at(idLayer);


//}
