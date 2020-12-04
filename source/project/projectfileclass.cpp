#include "projectfileclass.h"

ProjectFileClass::ProjectFileClass(bool is_new_project)
{
    alphabet_whitout_empty = {"1", "*"};
    named_states = {"aaa"};
    states = {"aaa", "q1"};



    this->is_new_proj = is_new_project;
    turing = new TuringClass;
}

ProjectFileClass::~ProjectFileClass()
{
    delete turing;
}

void ProjectFileClass::createAutomaticStates(int len)
{
    states.clear();
    for (int i = 0; i < len; ++i)
    {
        states.append("q" + QString::number(i));
    }
}

void ProjectFileClass::createStates(QString arg1)
{
    createAutomaticStates(len_of_states);
    QList<QString> temp_states = arg1.split(" ", Qt::SkipEmptyParts);
    for (int i = 0; i < states.size() && i < temp_states.size(); ++i)
    {
        states[i] = temp_states[i];
    }
}


