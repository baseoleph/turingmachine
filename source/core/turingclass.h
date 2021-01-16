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

#ifndef TURINGCLASS_H
#define TURINGCLASS_H

#include <QList>
#include <QDebug>
#include "Action.h"

struct CurrentState
{
    // init pos
    int p = 0;

    // init machine's state
    int q = 0;
};

class TuringClass
{
public:
    TuringClass();

    void setStart();
    void takeStep();
    bool isStepPossible();
    void setAction(int cur_q, int cur_a, int a, int q, int d);
    void setAlphabetStates(QList<QString> alphabet, QList<QString> states);

    QString project_name = "Unnamed project";
    // alphabet
    QList<QString> alphabet = {};
    // machine's state
    QList<QString> states = {};
    int step = 0;
    bool is_signature_fixed = false;

    // just for shows only named
    QList<QString> named_states = {};
    QList<QString> unnamed_states = {};

    QVector<QVector<Action>> table_of_actions = {};
    QVector<int> word_copy = {};
    QVector<int> word = {};
    QVector<QVector<int>> words = {};
    CurrentState machine_point;
    CurrentState machine_point_copy;

    void generateTableOfActions();
    void checkEdges();
private:
    // moves
    QList<QString> moves = {"Stay", "Left", "Right"};


    // history of actions
    QVector<Action> vector_of_actions;

    void debugTemplateTuring();
    void debugOutputWord();
};

#endif // TURINGCLASS_H
