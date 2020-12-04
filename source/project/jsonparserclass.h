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

class JsonParserClass
{
public:
    JsonParserClass(QWidget *parent = nullptr, TuringClass *turing = nullptr);

    void saveGeneralData();
    void saveBlocksData();
    void saveData();
    void loadGeneralData(QJsonObject general_json);
    void loadBlocksData(QJsonArray blocks_json);
    void loadData(QString proj_name);

    QWidget *parent;

private:
    QJsonObject json_main;
    TuringClass *turing;
};

#endif // JSONPARSERCLASS_H
