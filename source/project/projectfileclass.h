#ifndef PROJECTFILECLASS_H
#define PROJECTFILECLASS_H

#include "core/turingclass.h"

class ProjectFileClass
{
public:
    ProjectFileClass(bool is_new_project = true);
    ~ProjectFileClass();

    bool is_new_proj;

    // alphabet
    QList<QString> alphabet_whitout_empty;

    QList<QString> named_states;
    // machine's state
    QList<QString> states;

    int len_of_states = 0;
    QString empty_element = " ";

    void createAutomaticStates(int len);
    void createStates(QString arg1);

private:
    TuringClass *turing = nullptr;


};

#endif // PROJECTFILECLASS_H
