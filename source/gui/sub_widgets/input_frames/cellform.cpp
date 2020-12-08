#include "cellform.h"
#include "ui_cellform.h"

CellForm::CellForm(QWidget *parent, QList<QString> a, QList<QString> q, Action *act) :
    QWidget(parent),
    ui(new Ui::CellForm)
{
    ui->setupUi(this);
    this->act = act;
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

    ui->comboBox_a->setFocusPolicy(Qt::ClickFocus);
    ui->comboBox_q->setFocusPolicy(Qt::ClickFocus);
    ui->comboBox_d->setFocusPolicy(Qt::ClickFocus);

//    installEventFilter(ui->comboBox_a);
//    installEventFilter(ui->comboBox_q);
//    installEventFilter(ui->comboBox_d);
}

CellForm::~CellForm()
{
    delete ui;
}

void CellForm::on_comboBox_q_activated(int index)
{
    q_state = index-1;
    act->q = index;
}

void CellForm::on_comboBox_a_activated(int index)
{
    a_state = index-1;
    act->a = index;
}

void CellForm::on_comboBox_d_activated(int index)
{
    d_state = index;
    act->d = index;
}


