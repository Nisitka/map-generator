#include "areadrawwidget.h"

#include "map.h"

#include <QDebug>

areaDrawWidget::areaDrawWidget(int length, int width)
{
    this->setFixedSize(width, length);

    dHeight = Map::height / colors.size();

    if (length / Map::length > width / Map::width)
    {
        lBlock = (length-10) / Map::length;
    }
    else
    {
        lBlock =  (width-10) / Map::width;
    }

    for (int i=0; i<Map::length; i++)
    {
        QVector <QColor*> newStrPix;
        for (int j=0; j<Map::width; j++)
        {
            newStrPix.append(new QColor);
        }
        pixArea.append(newStrPix);
    }

    painter = new QPainter;

    pCoordsArea = new int[4];
    pCoordsArea[leftUpX] = 5;
    pCoordsArea[leftUpY] = 5;
    pCoordsArea[rightDownX] = width - 5;
    pCoordsArea[rightDownY] = length - 5;

    optRepaint = paintMap;

    callRender = true;
}

void areaDrawWidget::saveImage()
{
    if (callRender) {
        callRender = false;
        QPixmap pixmap(this->size());
        this->render(&pixmap);
        pixmap.save("test.png");
        callRender = true;
    }

    //this->grab().save("image.png");
}

QColor areaDrawWidget::colorHeight(int value)
{
    int r, g, b;

    int id = value / dHeight;
    // если не предельный цвет
    if (id == colors.size() - 1)
    {
        return colors[id];
    }
    else
    {
        QColor currentColor = colors[id];
        QColor nextColor = colors[id + 1];

        double part = double(value%dHeight) / dHeight;

        r = currentColor.red();
        g = currentColor.green();
        b = currentColor.blue();

        r += (nextColor.red() - currentColor.red()) * part;
        g += (nextColor.green() - currentColor.green()) * part;
        b += (nextColor.blue() - currentColor.blue()) * part;

        return QColor(r, g, b);
    }
}

void areaDrawWidget::Clear()
{
    optRepaint = clear;
    repaint();
}

void areaDrawWidget::drawMap()
{
     optRepaint = paintMap;
     repaint();
}

void areaDrawWidget::setMap(QVector<bool *>* pLayers_)
{
    pLayers = pLayers_;
}

void areaDrawWidget::paintEvent(QPaintEvent *pEvent)
{
    painter->begin(this);

    drawFrame();
    switch (optRepaint)
    {
        case clear:


            break;
        case paintMap:
            for (int i=0; i<Map::width; i++)
            {
                for (int j=0; j<Map::length; j++)
                {
                    // вычисляется цвет по данным
                    QColor color = colorHeight(Map::getHeight(pLayers, i, j));

                    pixArea[i][j]->setRgb(color.red(), color.green(), color.blue());

                    drawBlock(i, j, color);
                }
            }

            saveImage();
            break;

        case null:
            updatePixArea(); // отрисовка последней маски
            break;
    }
    painter->end();

    optRepaint = null;
}

void areaDrawWidget::updatePixArea()
{
    for (int i=0; i<Map::width; i++)
    {
        for (int j=0; j<Map::length; j++)
        {
            drawBlock(i, j, *pixArea[i][j]);
        }
    }
}

void areaDrawWidget::drawFrame()
{
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(pCoordsArea[leftUpX] - 1, pCoordsArea[leftUpY] - 1,
                 pCoordsArea[rightDownX] - pCoordsArea[leftUpX] + 2,
                 pCoordsArea[rightDownY] - pCoordsArea[leftUpY] + 2);
}

void areaDrawWidget::drawBlock(int idX, int idY,  const QColor& color)
{
    painter->setPen(color);
    painter->setBrush(QBrush(color));

    painter->drawRect(5 + idX*lBlock, 5 + idY*lBlock, lBlock, lBlock);
}
