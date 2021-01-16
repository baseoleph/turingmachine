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

#include "jsonparserclass.h"

JsonParserClass::JsonParserClass(QWidget *parent, TuringClass *turing)
    : QWidget(parent)
{
    this->turing = turing;
}

JsonParserClass::~JsonParserClass()
{
}

void JsonParserClass::findOutFileToPath()
{
    QString temp_file_name =  QFileDialog::getSaveFileName(this->parentWidget(),
                                                            QObject::tr("Введите имя файла"),
                                                            turing->project_name,
                                                            QObject::tr("*.turing"));

    if (temp_file_name != "")
    {
        path_to_project = temp_file_name;
    }
}

QString JsonParserClass::getFileToPath(QString file_to_path)
{
    return file_to_path;
}

void JsonParserClass::saveAsData()
{
    findOutFileToPath();
    writeData();
}

void JsonParserClass::saveData(QString file_to_path)
{
    if (file_to_path == "")
    {
        findOutFileToPath();
    }
    else
    {
        path_to_project = file_to_path;
    }
    writeData();
}

void JsonParserClass::writeData()
{
    if (path_to_project != "")
    {
        QJsonObject jsonproj = generateJsonObj();

        // Узнаем директорию для сохранения файла
        QFileInfo fileInfo(path_to_project);
        // Делаем ее текущей
        QDir::setCurrent(fileInfo.path());

        QFile jsonFile(path_to_project);
        if (!jsonFile.open(QIODevice::WriteOnly))
        {
            return;
        }

        // Записываем текущий объект Json в файл
        jsonFile.write(QJsonDocument(jsonproj).toJson(QJsonDocument::Indented));
        jsonFile.close();

        emitProjectSavedSignal(this);
    }
    else
    {
        emitProjectNOTSavedSignal(this);
    }
}

void JsonParserClass::loadData()
{
    // Выбираем файл
    path_to_project = QFileDialog::getOpenFileName(this->parentWidget(),
                                                   QObject::tr("Выберите файл"),
                                                   "",
                                                   QObject::tr("*.turing"));

    if (path_to_project != "")
    {
        QFile jsonFile(path_to_project);
        if (!jsonFile.open(QIODevice::ReadOnly))
        {
            return;
        }

        // Считываем весь файл
        QByteArray saveData = jsonFile.readAll();
        jsonFile.close();
        // Создаём QJsonDocument
        QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
        // Из которого выделяем объект в текущий рабочий QJsonObject
        QJsonObject json = jsonDocument.object();
        parseData(json);

        emitProjectOpenedSignal(this);
    }
    else
    {
        emitProjectNOTOpenedSignal(this);
    }
}

void JsonParserClass::parseData(QJsonObject json)
{
    QList<QString> alphabet = {};
    QList<QString> named_states = {};
    QList<QString> unnamed_states = {};

    QJsonArray js_alphabet = json.value(s_alphabet).toArray();
    foreach (auto e, js_alphabet)
    {
        alphabet.append(e.toString());
    }

    QJsonArray js_named_states = json.value(s_named_states).toArray();
    foreach (auto e, js_named_states)
    {
        named_states.append(e.toString());
    }

    QJsonArray js_unnamed_states = json.value(s_unnamed_states).toArray();
    foreach (auto e, js_unnamed_states)
    {
        unnamed_states.append(e.toString());
    }

    turing->is_signature_fixed = json.value(s_is_signature_fixed).toBool();

    turing->alphabet = alphabet;
    turing->named_states = named_states;
    turing->unnamed_states = unnamed_states;
    turing->states = named_states;
    turing->states += unnamed_states;
    turing->generateTableOfActions();

    QJsonArray js_table1 = json.value(s_table).toArray();
    for (int i = 0; i < js_table1.size(); ++i)
    {
        QJsonArray js_table2 = js_table1[i].toArray();
        for (int j = 0; j < js_table2.size(); ++j)
        {
            QJsonArray js_table3 = js_table2[j].toArray();
            turing->table_of_actions[i][j].a = js_table3[0].toInt();
            turing->table_of_actions[i][j].q = js_table3[1].toInt();
            turing->table_of_actions[i][j].d = js_table3[2].toInt();
        }
    }

    turing->words.clear();
    QJsonArray words = json.value(s_words).toArray();
    for (int i = 0; i < words.size(); ++i)
    {
        QJsonArray word = words[i].toArray();
        QVector<int> tem_word;
        for (int j = 0; j < word.size(); ++j)
        {
            tem_word.append(word[j].toInt());
        }
        turing->words.append(tem_word);
    }
}

QJsonObject JsonParserClass::generateJsonObj()
{
    QJsonObject jsonproj;
    QJsonArray js_alphabet;
    foreach (auto e, turing->alphabet)
    {
        js_alphabet.append(e);
    }
    jsonproj[s_alphabet] = js_alphabet;

    QJsonArray js_named_states;
    foreach (auto e, turing->named_states)
    {
        js_named_states.append(e);
    }
    jsonproj[s_named_states] = js_named_states;

    QJsonArray js_unnamed_states;
    foreach (auto e, turing->unnamed_states)
    {
        js_unnamed_states.append(e);
    }
    jsonproj[s_unnamed_states] = js_unnamed_states;

    jsonproj[s_is_signature_fixed] = turing->is_signature_fixed;

    QJsonArray table1;
    for (int i = 0; i < turing->states.size(); ++i)
    {
        QJsonArray table2;
        for (int j = 0; j < turing->alphabet.size(); ++j)
        {
            QJsonArray table3;
            table3.append(turing->table_of_actions[i][j].a);
            table3.append(turing->table_of_actions[i][j].q);
            table3.append(turing->table_of_actions[i][j].d);
            table2.append(table3);
        }
        table1.append(table2);
    }

    jsonproj[s_table] = table1;

    QJsonArray words;
    for (int i = 0; i < turing->words.size(); ++i)
    {
        QJsonArray word;
        for (int j = 0; j < turing->words[i].size(); ++j)
        {
            word.append(turing->words[i][j]);
        }
        words.append(word);
    }

    jsonproj[s_words] = words;
    return jsonproj;
}
