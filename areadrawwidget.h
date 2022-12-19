#ifndef AREADRAWWIDGET_H
#define AREADRAWWIDGET_H

#include <QObject>
#include <QWidget>

#include <QEvent>
#include <QPaintEvent>
#include <QPainter>

#include <QVector2D>

class areaDrawWidget : public QWidget
{
    Q_OBJECT
public:
    areaDrawWidget(int length, int width);

    void setMap(QVector <bool*>* pLayers);

    void Clear();

    // получаем цвет в зависимости от высоты
    QColor colorHeight(int value = 0);

    void drawMap();

protected:
    void paintEvent(QPaintEvent* pEvent);

private:
    void saveImage();

    enum coordAreaPainter{leftUpX,    leftUpY,
                          rightDownX, rightDownY};

    enum optionRepaint{clear, paintMap, null};
    int optRepaint;

    bool callRender;

    QPainter* painter;
    void drawFrame();
    void drawBlock(int idX, int idY, const QColor& color);
    void updatePixArea();

    int* pCoordsArea;

    int lBlock;

    QVector <QVector <QColor*>> pixArea;

    QVector <bool*>* pLayers;

    int dHeight;
    QVector <QColor> colors =
    {
        QColor(129, 203, 140), QColor(174, 225, 150), QColor(224, 245, 180),
        QColor(249, 244, 180), QColor(251, 228, 148), QColor(250, 216, 118),
        QColor(252, 189, 96),  QColor(254, 179, 96),  QColor(247, 153, 79),
        QColor(221, 128, 69),  QColor(209, 105, 54),  QColor(215, 92, 61),
        QColor(184, 40, 37),   QColor(169, 27, 27),   QColor(134, 21, 21),
    };
};

#endif // AREADRAWWIDGET_H
