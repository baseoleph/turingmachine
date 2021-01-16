// Turing Machine
// Copyright (C) 2020 baseoleph@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

    bool is_signature_fixed = false;
};

class ProjectFileClass : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectFileClass(QWidget *parent = nullptr);
    ~ProjectFileClass();

    bool takeStep();
    bool stepPossible();
    void toStart();
    int getSteps();

    void checkEdges();
    TuringClass *getTuring();
    void setAlphabet(QString arg1);
    QString getAlphabetForChange();

    void setStates(QString named_states, int len);
    void createAutomaticStates(int len);
    void overwriteNamedStates(QString arg1);
    QString getStatesForChange();
    int getLenOfStates();

    QString getAlphabetText();
    QString getStatesText();
    QList<QString> getAlphabet();
    QList<QString> getStates();

    void setSignatureState(bool is_fixed);
    bool isSignatureFixed();

    void clearWordsAndTable();

    void addWord(QVector<int> w);
    void setCurrentWord(int i);
    void deleteCurrentWord(int i);
    QString getWord();
    QString getNewWord();
    QVector<QVector<int>> getWords();

    const QString empty_element = "\\0";

    void openProject();
    void saveAsProject();
    void saveProject();
    void setProjectName(QString project_name);
    TuringClass *turing = nullptr;
    bool isSavedCopyShows();

    QVector<QVector<Action>> *table_of_actions = nullptr;
    QVector<QVector<Action>> getTable();
signals:
    void emitProjectNameSignal(QString project_name);
    void emitOpenFailedSignal();
    void emitOpenSucces();
    void emitCloseEventSignal(QCloseEvent *event);

private slots:
    void projectSavedSlot(JsonParserClass *json);
    void projectNOTSavedSlot(JsonParserClass *json);
    void projectOpenedSlot(JsonParserClass *json);
    void projectNOTOpenedSlot(JsonParserClass *json);

private:
    void setCurrentProjectAndPath(JsonParserClass *json);
    void projectChangedSaved(bool is_saved);
    void updateTuringSavedData();

    JsonParserClass *createJson();
    void deleteJson(JsonParserClass *json);

    QString current_filetopath = "";
    QString current_project = "";
    turing_data turing_saved;

    void closeEvent(QCloseEvent *event);
};

#endif // PROJECTFILECLASS_H
