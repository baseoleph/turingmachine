// Turing Machine
// Copyright (C) 2020 baseoleph@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    QFont font = QFont("Tahoma", 15);
    QVector<QGraphicsRectItem *> rect_word;
    QVector<QGraphicsSimpleTextItem *> text_word;
    QGraphicsPathItem *pointer_of_machine;
    QGraphicsSimpleTextItem *pointer_text;
    int width;
    int height;

    void setPointer();
    void createPointerOfMachine();
    const int SIDE_OF_CELL = 50;
};

#endif // SCENE_H
