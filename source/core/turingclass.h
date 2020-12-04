#ifndef TURINGCLASS_H
#define TURINGCLASS_H

#include <QList>
#include <QDebug>

struct Action
{
    // new letter under machine
    int a = -1;
    // new machine's state
    int q = -1;
    // direct
    int d = 0;
};

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

    void takeStep();
    void setAction(int cur_q, int cur_a, int a, int q, int d);
    void setAlphabetStates(QList<QString> alphabet, QList<QString> states);

    // alphabet
    QList<QString> alphabet;
    // machine's state
    QList<QString> states;

    QVector<QVector<Action>> table_of_actions;
    QVector<int> word;
    CurrentState machine_point;

private:
    // moves
    QList<QString> moves = {"Stay", "Left", "Right"};


    // history of actions
    QVector<Action> vector_of_actions;

    void debugOutputWord();

    void checkEdges();
};

#endif // TURINGCLASS_H
