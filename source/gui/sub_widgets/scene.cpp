#include "scene.h"

Scene::Scene(int width, int height, TuringClass *turing)
{
    this->turing = turing;
    this->width = width;
    this->height = height;
    pointer_of_machine = new QGraphicsPathItem();
    pointer_text = new QGraphicsSimpleTextItem();
    pointer_text->setFont(font);
    createPointerOfMachine();
    setSceneRect(0, 0, width-10, height-10);
    showState();
    addItem(pointer_of_machine);
    addItem(pointer_text);
    pointer_of_machine->setPos(width/2 - SIDE_OF_CELL/2, height/2 - SIDE_OF_CELL);
}

Scene::~Scene()
{
    clearRects();
}

void Scene::showState()
{
    clearRects();

    pointer_text->setText(turing->states[turing->machine_point_copy.q]);
    qreal text_width = pointer_text->boundingRect().width();
    qreal text_height = pointer_text->boundingRect().height();
    QPointF point_p = QPointF(width/2 - SIDE_OF_CELL/2, height/2 - SIDE_OF_CELL);
    pointer_text->setPos(point_p.x() + (SIDE_OF_CELL-text_width)/2, point_p.y() + (SIDE_OF_CELL-text_height)/2);
    pointer_text->setPos(point_p.x() + (SIDE_OF_CELL-text_width)/2, point_p.y() + (SIDE_OF_CELL-text_height)/4);

    for (int i = 0; i < turing->word_copy.size(); ++i)
    {
        int x_cell = (i - turing->machine_point_copy.p)*SIDE_OF_CELL + width/2 - SIDE_OF_CELL/2;
        int y_cell = height/2;
        rect_word.append(new QGraphicsRectItem(x_cell, y_cell, SIDE_OF_CELL, SIDE_OF_CELL));

        QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(turing->alphabet[turing->word_copy[i]]);
        text->setFont(font);

        qreal text_width = text->boundingRect().width();
        qreal text_height = text->boundingRect().height();

        text_word.append(text);
        text_word.back()->setPos(x_cell + (SIDE_OF_CELL - text_width)/2, y_cell + (SIDE_OF_CELL - text_height)/2);
        addItem(text_word.back());
        addItem(rect_word.back());
//        if (rect_word.back()->mapToScene(rect_word.back()->rect().bottomLeft()).x() >
//            0)
//        {
//            // Здесь ответ
//            qDebug() << rect_word.back()->mapToScene(rect_word.back()->rect().bottomLeft()).x();
//            qDebug() << this->sceneRect().width();
//            qDebug() << ",jkmit";
//        }
    }
}

void Scene::clearRects()
{
    foreach (auto e, rect_word)
    {
        delete e;
    }
    foreach (auto e, text_word)
    {
        delete e;
    }
    rect_word.clear();
    text_word.clear();
}

void Scene::createPointerOfMachine()
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(SIDE_OF_CELL, 0);
    path.lineTo(SIDE_OF_CELL/2, SIDE_OF_CELL);
    path.lineTo(0, 0);

    pointer_of_machine->setPath(path);
}
