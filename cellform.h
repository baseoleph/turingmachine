#ifndef CELLFORM_H
#define CELLFORM_H

#include <QWidget>

namespace Ui {
class CellForm;
}

class CellForm : public QWidget
{
    Q_OBJECT

public:
    explicit CellForm(QWidget *parent = nullptr, QList<QString> a = {}, QList<QString> q = {});
    ~CellForm();

    int a_state;
    int q_state;
    int d_state;

private slots:
    void on_comboBox_q_activated(int index);

    void on_comboBox_a_activated(int index);

    void on_comboBox_d_activated(int index);

private:
    Ui::CellForm *ui;
};

#endif // CELLFORM_H
