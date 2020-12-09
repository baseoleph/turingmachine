#include "projectfileclass.h"

ProjectFileClass::ProjectFileClass(QWidget *parent)
    : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    turing = new TuringClass;
    current_project = turing->project_name;
    turing->alphabet.clear();
    turing->alphabet.append(empty_element);
    turing->generateTableOfActions();
    table_of_actions = &turing->table_of_actions;
    updateTuringSavedData();
}

ProjectFileClass::~ProjectFileClass()
{
    delete turing;
}

bool ProjectFileClass::takeStep()
{
    turing->takeStep();

    return turing->isStepPossible();
}

bool ProjectFileClass::stepPossible()
{
    return turing->isStepPossible();
}

void ProjectFileClass::toStart()
{
    turing->setStart();
}

int ProjectFileClass::getSteps()
{
    return turing->step;
}

void ProjectFileClass::checkEdges()
{
    turing->checkEdges();
}

TuringClass *ProjectFileClass::getTuring()
{
    return turing;
}

void ProjectFileClass::setAlphabet(QString arg1)
{
    turing->alphabet.clear();
    turing->alphabet.append(empty_element);
    turing->alphabet += arg1.split(" ", Qt::SkipEmptyParts);

    projectChangedSaved(isSavedCopyShows());
}

QString ProjectFileClass::getAlphabetForChange()
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

QString ProjectFileClass::getStatesForChange()
{
    return turing->named_states.join(" ");
}

int ProjectFileClass::getLenOfStates()
{
    return turing->states.size();
}

QString ProjectFileClass::getAlphabetText()
{
    QString alphabet_text = "Алфавит = {";
    alphabet_text += turing->alphabet.join(", ");
    alphabet_text += "}";
    return alphabet_text;
}

QString ProjectFileClass::getStatesText()
{
    QString states_text = "Состояния = {";
    states_text += turing->states.join(", ");
    states_text += "}";
    return states_text;
}

QList<QString> ProjectFileClass::getAlphabet()
{
    return turing->alphabet;
}

QList<QString> ProjectFileClass::getStates()
{
    return turing->states;
}

void ProjectFileClass::setSignatureState(bool is_fixed)
{
    turing->is_signature_fixed = is_fixed;
    if (is_fixed)
    {
        turing->generateTableOfActions();
        table_of_actions = &turing->table_of_actions;
        turing->words.clear();
    }

    projectChangedSaved(isSavedCopyShows());
}

bool ProjectFileClass::isSignatureFixed()
{
    return turing->is_signature_fixed;
}

void ProjectFileClass::clearWordsAndTable()
{
    turing->table_of_actions.clear();
}

void ProjectFileClass::addWord(QVector<int> w)
{
    turing->words.append(w);
    setCurrentWord(turing->words.size()-1);
}

void ProjectFileClass::setCurrentWord(int i)
{
    turing->word = turing->words[i];
}

void ProjectFileClass::deleteCurrentWord(int i)
{
    turing->words.remove(i);
}

QString ProjectFileClass::getWord()
{
    QString word_t = "Слово = { ";
    foreach (auto e, turing->word)
    {
        word_t += turing->alphabet[e] + " ";
    }
    word_t.remove(word_t.size()-1);
    word_t += "}";
    return word_t;
}

QString ProjectFileClass::getNewWord()
{
    QString word_t = "";
    foreach (auto e, turing->word_copy)
    {
        word_t += turing->alphabet[e] + " ";
    }
    word_t.remove(word_t.size()-1);
    return word_t;
}

QVector<QVector<int> > ProjectFileClass::getWords()
{
    return turing->words;
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

    table_of_actions = &turing->table_of_actions;

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
    turing_saved.is_signature_fixed = turing->is_signature_fixed;
}

bool ProjectFileClass::isSavedCopyShows()
{
    bool check_state = turing_saved.alphabet == turing->alphabet &&
                       turing_saved.states == turing->states &&
                       turing_saved.project_name == turing->project_name &&
                       turing_saved.is_signature_fixed == turing->is_signature_fixed;
    return check_state;
}

QVector<QVector<Action> > ProjectFileClass::getTable()
{
    return turing->table_of_actions;
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

void ProjectFileClass::closeEvent(QCloseEvent *event)
{
    emitCloseEventSignal(event);
}


