#ifndef PROJECTFILECLASS_H
#define PROJECTFILECLASS_H

#include <QWidget>
#include "core/turingclass.h"
#include "jsonparserclass.h"

class ProjectFileClass
{
public:
    ProjectFileClass(QWidget *parent = nullptr, bool is_new_project = true);
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
    void saveAsProject();
    TuringClass *turing = nullptr;

private:
    QWidget *parent;
    void updateTuringData();

};

#endif // PROJECTFILECLASS_H
