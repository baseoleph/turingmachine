#ifndef INPUTPARAMETERSFORM_H
#define INPUTPARAMETERSFORM_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include <QComboBox>

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

    QVector<QLabel *> label_states;
    QVector<QLabel *> label_alphabet;
    QVector<QVector<QFrame *>> table_frame;
};

#endif // INPUTPARAMETERSFORM_H
