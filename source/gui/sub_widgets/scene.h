#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QtMath>
#include "core/turingclass.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int width, int height, TuringClass *turing = nullptr);
    ~Scene();

    void showState();
    void clearRects();

private:
    TuringClass *turing;
    QVector<QGraphicsRectItem *> rect_word;
    QVector<QGraphicsSimpleTextItem *> text_word;
    QGraphicsPathItem *pointer_of_machine;
    int width;
    int height;

    void createPointerOfMachine();
    const int SIDE_OF_CELL = 50;
};

#endif // SCENE_H
