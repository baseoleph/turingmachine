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

#ifndef JSONPARSERCLASS_H
#define JSONPARSERCLASS_H

#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "core/turingclass.h"

class JsonParserClass : public QWidget
{
    Q_OBJECT
public:
    JsonParserClass(QWidget *parent = nullptr, TuringClass *turing = nullptr);
    ~JsonParserClass();

    void findOutFileToPath();
    QString getFileToPath(QString file_to_path);
    void saveAsData();
    void saveData(QString file_to_path = "");
    void writeData();
    QJsonObject generateJsonObj();


    void loadData();
    void parseData(QJsonObject json);

    QString path_to_project = "";
signals:
    void emitProjectSavedSignal(JsonParserClass *json);
    void emitProjectNOTSavedSignal(JsonParserClass *json);
    void emitProjectOpenedSignal(JsonParserClass *json);
    void emitProjectNOTOpenedSignal(JsonParserClass *json);

private:
    QJsonObject json_main;
    TuringClass *turing;

    QString s_title = "title";
    QString s_alphabet = "alphabet";
    QString s_states = "states";
    QString s_named_states = "named states";
    QString s_unnamed_states = "unnamed states";
    QString s_is_signature_fixed = "is_signature_fixed";
    QString s_table = "table";
    QString s_words = "words";
};

#endif // JSONPARSERCLASS_H
