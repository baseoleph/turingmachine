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
