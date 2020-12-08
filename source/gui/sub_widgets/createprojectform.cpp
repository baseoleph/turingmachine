#include "createprojectform.h"
#include "ui_createprojectform.h"

CreateProjectForm::CreateProjectForm(QWidget *parent, ProjectFileClass *project) :
    QWidget(parent),
    ui(new Ui::CreateProjectForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->proj = project;

    fillForms();
}

CreateProjectForm::~CreateProjectForm()
{
    emitCloseSignal(this);
    delete ui;
}

void CreateProjectForm::on_lineEdit_alphabet_textEdited(const QString &arg1)
{
    proj->setAlphabet(arg1);
}

void CreateProjectForm::on_lineEdit_count_of_states_textEdited(const QString &arg1)
{
    int len_of_states = arg1.toInt();
    proj->setStates(ui->lineEdit_states->text(), len_of_states);

    if (len_of_states > 0)
    {
        ui->pushButton_next->setEnabled(true);
    }
    else
    {
        ui->pushButton_next->setEnabled(false);
    }
}

void CreateProjectForm::on_lineEdit_states_textEdited(const QString &arg1)
{
    proj->setStates(arg1, ui->lineEdit_count_of_states->text().toInt());
}

void CreateProjectForm::on_pushButton_next_clicked()
{
}

void CreateProjectForm::fillForms()
{
    ui->lineEdit_count_of_states->setText(QString::number(proj->getLenOfStates()));
    ui->lineEdit_alphabet->setText(proj->getAlphabet());
    ui->lineEdit_states->setText(proj->getStates());
}

void CreateProjectForm::closeEvent(QCloseEvent *event)
{
    emitCloseEventSignal(event);
}
