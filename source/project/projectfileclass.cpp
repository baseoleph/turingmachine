#include "projectfileclass.h"

ProjectFileClass::ProjectFileClass(QWidget *parent)
    : QWidget(parent)
{
    turing = new TuringClass;
    current_project = turing->project_name;
    turing->alphabet.clear();
    turing->alphabet.append(empty_element);
    updateTuringSavedData();
}

ProjectFileClass::~ProjectFileClass()
{
    delete turing;
}

void ProjectFileClass::setAlphabet(QString arg1)
{
    turing->alphabet.clear();
    turing->alphabet.append(empty_element);
    turing->alphabet += arg1.split(" ", Qt::SkipEmptyParts);

    projectChangedSaved(isSavedCopyShows());
}

QString ProjectFileClass::getAlphabet()
{
    QList<QString> temp = turing->alphabet;
    temp.pop_front();
    return temp.join(" ");
}

void ProjectFileClass::setStates(QString named_states, int len)
{
    createAutomaticStates(len);
    overwriteNamedStates(named_states);

    projectChangedSaved(isSavedCopyShows());
}

QString ProjectFileClass::getStates()
{
    return turing->named_states.join(" ");
}

int ProjectFileClass::getLenOfStates()
{
    return turing->states.size();
}

void ProjectFileClass::openProject()
{
    JsonParserClass *json = createJson();
    json->loadData();
}

void ProjectFileClass::createAutomaticStates(int len)
{
    turing->states.clear();
    for (int i = 0; i < len; ++i)
    {
        turing->states.append("q" + QString::number(i));
    }
}

void ProjectFileClass::overwriteNamedStates(QString arg1)
{
    QList<QString> temp_states = arg1.split(" ", Qt::SkipEmptyParts);
    turing->named_states.clear();
    for (int i = 0; i < turing->states.size() && i < temp_states.size(); ++i)
    {
        turing->states[i] = temp_states[i];
        turing->named_states.append(temp_states[i]);
    }

    turing->unnamed_states.clear();
    for (int i = qMin(turing->states.size(), temp_states.size()); i < turing->states.size(); ++i)
    {
        turing->unnamed_states.append(turing->states[i]);
    }
}

void ProjectFileClass::saveAsProject()
{
    JsonParserClass *json = createJson();
    json->saveAsData();
}

void ProjectFileClass::saveProject()
{
    JsonParserClass *json = createJson();
    json->saveData(current_filetopath);
}

void ProjectFileClass::setProjectName(QString project_name)
{
    turing->project_name = project_name;
}

void ProjectFileClass::projectSavedSlot(JsonParserClass *json)
{
    setCurrentProjectAndPath(json);
    updateTuringSavedData();
    emitProjectNameSignal(current_project);

    deleteJson(json);
}

void ProjectFileClass::projectNOTSavedSlot(JsonParserClass *json)
{
    if (not isSavedCopyShows()) projectChangedSaved(false);

    deleteJson(json);
}

void ProjectFileClass::projectOpenedSlot(JsonParserClass *json)
{
    setCurrentProjectAndPath(json);
    updateTuringSavedData();
    emitProjectNameSignal(current_project);
    emitOpenSucces();

    deleteJson(json);
}

void ProjectFileClass::projectNOTOpenedSlot(JsonParserClass *json)
{
    deleteJson(json);
    emitOpenFailedSignal();
}

void ProjectFileClass::setCurrentProjectAndPath(JsonParserClass *json)
{
    if (json->path_to_project != "")
    {
        current_filetopath = json->path_to_project;
    }
    current_project = current_filetopath.split("/").last().split(".").first();
    turing->project_name = current_project;
}

void ProjectFileClass::projectChangedSaved(bool is_saved)
{
    QString title_status = current_project;
    if (not is_saved)
    {
        title_status += "*";
    }
    emitProjectNameSignal(title_status);
}

void ProjectFileClass::updateTuringSavedData()
{
    turing_saved.alphabet = turing->alphabet;
    turing_saved.states = turing->states;
    turing_saved.project_name = turing->project_name;
}

bool ProjectFileClass::isSavedCopyShows()
{
    bool check_state = turing_saved.alphabet == turing->alphabet &&
                       turing_saved.states == turing->states &&
                       turing_saved.project_name == turing->project_name;
    return check_state;
}

JsonParserClass *ProjectFileClass::createJson()
{
    JsonParserClass *json = new JsonParserClass(this, turing);
    connect(json, &JsonParserClass::emitProjectSavedSignal, this, &ProjectFileClass::projectSavedSlot);
    connect(json, &JsonParserClass::emitProjectNOTSavedSignal, this, &ProjectFileClass::projectNOTSavedSlot);
    connect(json, &JsonParserClass::emitProjectOpenedSignal, this, &ProjectFileClass::projectOpenedSlot);
    connect(json, &JsonParserClass::emitProjectNOTOpenedSignal, this, &ProjectFileClass::projectNOTOpenedSlot);

    return json;
}

void ProjectFileClass::deleteJson(JsonParserClass *json)
{
    disconnect(json, &JsonParserClass::emitProjectSavedSignal, this, &ProjectFileClass::projectSavedSlot);
    disconnect(json, &JsonParserClass::emitProjectNOTSavedSignal, this, &ProjectFileClass::projectNOTSavedSlot);
    disconnect(json, &JsonParserClass::emitProjectOpenedSignal, this, &ProjectFileClass::projectOpenedSlot);
    disconnect(json, &JsonParserClass::emitProjectNOTOpenedSignal, this, &ProjectFileClass::projectNOTOpenedSlot);

    delete json;
}


