#ifndef CELLFORM_H
#define CELLFORM_H

#include <QWidget>
#include <QDebug>
#include <QSpinBox>
#include "core/Action.h"

namespace Ui {
class CellForm;
}

class CellForm : public QWidget
{
    Q_OBJECT

public:
    explicit CellForm(QWidget *parent = nullptr, QList<QString> a = {}, QList<QString> q = {}, Action *act = nullptr);
    ~CellForm();

    int a_state = 0;
    int q_state = 0;
    int d_state = 0;

private slots:
    void on_comboBox_q_activated(int index);

    void on_comboBox_a_activated(int index);

    void on_comboBox_d_activated(int index);

private:
    Ui::CellForm *ui;
    Action *act;

};

#endif // CELLFORM_H
