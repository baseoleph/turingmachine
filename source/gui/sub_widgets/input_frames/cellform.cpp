#include "cellform.h"
#include "ui_cellform.h"

CellForm::CellForm(QWidget *parent, QList<QString> a, QList<QString> q) :
    QWidget(parent),
    ui(new Ui::CellForm)
{
    ui->setupUi(this);

    ui->comboBox_a->addItem("");
    ui->comboBox_q->addItem("");
    foreach (auto e, a)
    {
        ui->comboBox_a->addItem(e);
    }
    foreach (auto e, q)
    {
        ui->comboBox_q->addItem(e);
    }

    ui->comboBox_d->addItem("");
    ui->comboBox_d->addItem("L");
    ui->comboBox_d->addItem("R");


    ui->comboBox_a->setCurrentIndex(0);
    ui->comboBox_q->setCurrentIndex(0);
    ui->comboBox_d->setCurrentIndex(0);
}

CellForm::~CellForm()
{
    delete ui;
}

void CellForm::on_comboBox_q_activated(int index)
{
    q_state = index;
}

void CellForm::on_comboBox_a_activated(int index)
{
    a_state = index;
}

void CellForm::on_comboBox_d_activated(int index)
{
    d_state = index;
}
