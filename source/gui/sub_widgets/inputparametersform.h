#ifndef INPUTPARAMETERSFORM_H
#define INPUTPARAMETERSFORM_H


#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDebug>

#include "input_frames/cellform.h"
#include "input_frames/letterform.h"

namespace Ui {
class InputParametersForm;
}

class InputParametersForm : public QWidget
{
    Q_OBJECT

public:
    explicit InputParametersForm(QWidget *parent = nullptr, QList<QString> alphabet = {}, QList<QString> states = {});
    ~InputParametersForm();

signals:
    void tableWordSignal(QVector<QVector<Action>> table, QVector<int> word);

private slots:

    void on_pushButton_next_clicked();

private:
    Ui::InputParametersForm *ui;
    QList<QString> alphabet;
    QList<QString> states;

    QVector<QVector<QFrame *>> table_frame;
    QVector<QVector<CellForm *>> table_instructions;
    QVector<LetterForm *> vector_word;
    QVector<LetterForm *> visible_letters;
    QVector<QVector<int>> words;
    QVector<QVector<Action>> table_of_actions;


};

#endif // INPUTPARAMETERSFORM_H
