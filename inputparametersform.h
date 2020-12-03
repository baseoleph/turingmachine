#ifndef INPUTPARAMETERSFORM_H
#define INPUTPARAMETERSFORM_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include <QComboBox>

#include "cellform.h"

namespace Ui {
class InputParametersForm;
}

class InputParametersForm : public QWidget
{
    Q_OBJECT

public:
    explicit InputParametersForm(QWidget *parent = nullptr, QList<QString> alphabet = {}, QList<QString> states = {});
    ~InputParametersForm();

private:
    Ui::InputParametersForm *ui;
    QList<QString> alphabet;
    QList<QString> states;

    QVector<QVector<QFrame *>> table_frame;
    QVector<QVector<CellForm *>> table_instructions;

    void setInstructions();
    void setTableFrames();
};

#endif // INPUTPARAMETERSFORM_H
