#include "workingmachineform.h"
#include "ui_workingmachineform.h"

WorkingMachineForm::WorkingMachineForm(QWidget *parent, TuringClass *turing) :
    QWidget(parent),
    ui(new Ui::WorkingMachineForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->turing = turing;

    tm = new QTimer();
    connect(tm, &QTimer::timeout, this, &WorkingMachineForm::setUpScene);
    tm->start(100);
}

WorkingMachineForm::~WorkingMachineForm()
{
    delete tm;
    delete scene;
    delete ui;
}

void WorkingMachineForm::on_pushButton_step_clicked()
{
    turing->takeStep();
    scene->showState();
}

void WorkingMachineForm::setUpScene()
{
    tm->stop();

    scene = new Scene(ui->graphicsView->width(), ui->graphicsView->height(), turing);

    ui->graphicsView->setScene(scene);
}
