#include "scene.h"

Scene::Scene(int width, int height, TuringClass *turing)
{
    this->turing = turing;
    this->width = width;
    this->height = height;
    pointer_of_machine = new QGraphicsPathItem();
    createPointerOfMachine();
    setSceneRect(0, 0, width-10, height-10);
    showState();
    addItem(pointer_of_machine);
    pointer_of_machine->setPos(width/2 - SIDE_OF_CELL/2, height/2 - SIDE_OF_CELL);
}

Scene::~Scene()
{
    clearRects();
}

void Scene::showState()
{
    clearRects();

    qDebug() << turing->machine_point.p;
    for (int i = 0; i < turing->word.size(); ++i)
    {
        int x_cell = (i - turing->machine_point.p)*SIDE_OF_CELL + width/2 + SIDE_OF_CELL/2;
        int y_cell = height/2;
        rect_word.append(new QGraphicsRectItem(x_cell, y_cell, SIDE_OF_CELL, SIDE_OF_CELL));
        text_word.append(new QGraphicsSimpleTextItem(turing->alphabet[turing->word[i]]));
        text_word.back()->setPos(x_cell, y_cell);
        addItem(rect_word.back());
        addItem(text_word.back());
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
