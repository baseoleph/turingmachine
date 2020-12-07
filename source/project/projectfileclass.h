#ifndef PROJECTFILECLASS_H
#define PROJECTFILECLASS_H

#include <QWidget>
#include <QtGlobal>
#include <QObject>
#include "core/turingclass.h"
#include "jsonparserclass.h"

struct turing_data
{
    QString project_name = "";
    // alphabet
    QList<QString> alphabet = {};
    // machine's state
    QList<QString> states = {};
};

class ProjectFileClass : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectFileClass(QWidget *parent = nullptr);
    ~ProjectFileClass();

    void setAlphabet(QString arg1);
    QString getAlphabet();

    void setStates(QString named_states, int len);
    void createAutomaticStates(int len);
    void overwriteNamedStates(QString arg1);
    QString getStates();
    int getLenOfStates();

    const QString empty_element = " ";

    void saveAsProject();
    void saveProject();
    void setProjectName(QString project_name);
    TuringClass *turing = nullptr;

signals:
    void emitProjectNameSignal(QString project_name);

private slots:
    void projectSavedSlot(JsonParserClass *json);
    void projectNOTSavedSlot(JsonParserClass *json);

private:
    void setCurrentProjectAndPath(JsonParserClass *json);
    void projectChangedSaved(bool is_saved);
    void updateTuringSavedData();
    bool isSavedCopyShows();

    JsonParserClass *createJson();
    void deleteJson(JsonParserClass *json);

    QString current_filetopath = "";
    QString current_project = "";
    turing_data turing_saved;
};

#endif // PROJECTFILECLASS_H
