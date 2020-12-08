#include "managerprojectform.h"
#include "ui_managerprojectform.h"

ManagerProjectForm::ManagerProjectForm(QWidget *parent, ProjectFileClass *project) :
    QWidget(parent),
    ui(new Ui::ManagerProjectForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->proj = project;
}

ManagerProjectForm::~ManagerProjectForm()
{
    emitCloseSignal(this);
    delete ui;
}

void ManagerProjectForm::on_pushButton_create_clicked()
{
    emitCreateProjectSignal();
    this->close();
}

void ManagerProjectForm::on_pushButton_open_clicked()
{
    emitOpenProjectSignal();
    this->close();
}
