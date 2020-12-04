#ifndef INPUTPARAMETERSFORM_H
#define INPUTPARAMETERSFORM_H

#define SIZE_FOR_ALLOC 10

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include <QComboBox>

#include "cellform.h"
#include "letterform.h"

#ifndef TURINGCLASS_H
struct Action
{
    // new letter under machine
    int a = -1;
    // new machine's state
    int q = -1;
    // direct
    int d = 0;
};
#endif

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
    void on_lineEdit_len_of_word_textChanged(const QString &arg1);

    void on_pushButton_set_visible_word_clicked();

    void on_pushButton_add_word_clicked();

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

    int len_of_word;

    void setInstructions();
    void setTableFrames();
    void setWordFrames(int len);
    void allocWordFrames(int size = SIZE_FOR_ALLOC);
    void clearWordFrames();
};

#endif // INPUTPARAMETERSFORM_H
