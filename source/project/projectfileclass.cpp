#include "projectfileclass.h"

ProjectFileClass::ProjectFileClass(QWidget *parent, bool is_new_project)
{
    this->parent = parent;
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

void ProjectFileClass::saveAsProject()
{
    updateTuringData();
//    JsonParserClass *pars = new JsonParserClass(parent, turing);
    JsonParserClass(parent, turing).saveData();
}

void ProjectFileClass::updateTuringData()
{
    turing->alphabet.clear();
    turing->alphabet.append(empty_element);
    turing->alphabet += alphabet_whitout_empty;

    turing->states.clear();
    turing->states = states;
}


