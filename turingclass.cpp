#include "turingclass.h"

TuringClass::TuringClass()
{
    alphabet = {"a0", "1", "*"};
    states = {"q0", "q1"};

    table_of_actions.clear();
    for (int i = 0; i < states.size(); ++i)
    {
        QVector<Action> temp;
        for (int j = 0; j < alphabet.size(); ++j)
        {
            Action act_temp;
            temp.append(act_temp);
        }
        table_of_actions.append(temp);
    }

    setAction(0, 2, 2, 0, 2);
    setAction(0, 1, 1, 1, 2);
    setAction(1, 2, 2, 1, 2);
    setAction(1, 1, 2, 0, 2);
    setAction(0, 0, 0, 0, 2);

    word = {2, 1, 2, 1, 1, 1};
    checkEdges();
    debugOutputWord();
}

void TuringClass::takeStep()
{
    Action cur_action = table_of_actions[machine_point.q][word[machine_point.p]];
    if (cur_action.a != -1) word[machine_point.p] = cur_action.a;
    if (cur_action.q != -1) machine_point.q = cur_action.q;
    if (cur_action.d != 0)
    {
        if (cur_action.d == 1)
        {
            --machine_point.p;
        }
        else
        {
            ++machine_point.p;
        }
    }

    checkEdges();
    debugOutputWord();
}

void TuringClass::setAction(int cur_q, int cur_a, int a, int q, int d)
{
    table_of_actions[cur_q][cur_a].a = a;
    table_of_actions[cur_q][cur_a].q = q;
    table_of_actions[cur_q][cur_a].d = d;
}

void TuringClass::setAlphabetStates(QList<QString> alphabet, QList<QString> states)
{
    this->alphabet = alphabet;
    this->states = states;
}

void TuringClass::debugOutputWord()
{
    QList<QString> output;
    foreach (auto e, word)
    {
        output.append(alphabet[e]);
    }
    output.insert(machine_point.p, states[machine_point.q]);
    qDebug() << output;
}

void TuringClass::checkEdges()
{
    if (machine_point.p == 0)
    {
        word.push_front(0);
        machine_point.p = 1;
    }

    if (word.size() == machine_point.p)
    {
        word.append(0);
    }

    int i = 0;
    while (i < machine_point.p - 1)
    {
        if (word[i] != 0)
        {
            break;
        }
        else
        {
            word.removeFirst();
            --machine_point.p;
        }
    }

    while (word.size() > machine_point.p+1)
    {
        if (word.last() != 0)
        {
            break;
        }
        else
        {
            word.removeLast();
        }
    }
}
