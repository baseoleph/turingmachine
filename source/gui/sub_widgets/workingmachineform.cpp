#include "workingmachineform.h"
#include "ui_workingmachineform.h"

WorkingMachineForm::WorkingMachineForm(QWidget *parent, TuringClass *turing) :
    QWidget(parent),
    ui(new Ui::WorkingMachineForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->turing = turing;

//    connect(tm, &QTimer::timeout, this, &WorkingMachineForm::setUpScene);
//    tm->start(100);
}

WorkingMachineForm::~WorkingMachineForm()
{
}




