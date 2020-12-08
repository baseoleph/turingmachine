#include "turingclass.h"

TuringClass::TuringClass()
{
}

void TuringClass::setStart()
{
    word_copy = word;
    machine_point_copy = machine_point;
}

void TuringClass::takeStep()
{
    Action cur_action = table_of_actions[machine_point_copy.q][word_copy[machine_point_copy.p]];
    if (cur_action.a != -1) word_copy[machine_point_copy.p] = cur_action.a;
    if (cur_action.q != -1) machine_point_copy.q = cur_action.q;
    if (cur_action.d != 0)
    {
        if (cur_action.d == 1)
        {
            --machine_point_copy.p;
        }
        else
        {
            ++machine_point_copy.p;
        }
    }

    checkEdges();
}

bool TuringClass::isStepPossible()
{
    Action cur_action = table_of_actions[machine_point_copy.q][word_copy[machine_point_copy.p]];
    return ((cur_action.a != -1) && (cur_action.q != -1));
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

void TuringClass::generateTableOfActions()
{
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
}

void TuringClass::debugTemplateTuring()
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

    word_copy = {2, 1, 2, 1, 1, 1};
    checkEdges();
}

void TuringClass::debugOutputWord()
{
    QList<QString> output;
    foreach (auto e, word_copy)
    {
        output.append(alphabet[e]);
    }
    output.insert(machine_point_copy.p, states[machine_point_copy.q]);
}

void TuringClass::checkEdges()
{
    if (machine_point_copy.p == 0)
    {
        word_copy.push_front(0);
        machine_point_copy.p = 1;
    }

    if (word_copy.size() == machine_point_copy.p+1)
    {
        word_copy.append(0);
    }


    int i = 0;
    while (i < machine_point_copy.p - 1)
    {
        if (word_copy[i] != 0)
        {
            break;
        }
        else
        {
            word_copy.removeFirst();
            --machine_point_copy.p;
        }
    }

    while (word_copy.size() > machine_point_copy.p+2)
    {
        if (word_copy.last() != 0)
        {
            break;
        }
        else
        {
            word_copy.removeLast();
        }
    }
}
