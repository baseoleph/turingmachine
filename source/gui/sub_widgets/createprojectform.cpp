#include "createprojectform.h"
#include "ui_createprojectform.h"

CreateProjectForm::CreateProjectForm(QWidget *parent, ProjectFileClass *project) :
    QWidget(parent),
    ui(new Ui::CreateProjectForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->proj = project;

    ui->lineEdit_count_of_states->setText(QString::number(proj->states.size()));
    ui->lineEdit_alphabet->setText(proj->alphabet_whitout_empty.join(" "));
    ui->lineEdit_states->setText(proj->named_states.join(" "));
}

CreateProjectForm::~CreateProjectForm()
{
    delete ui;
}

void CreateProjectForm::on_lineEdit_alphabet_textChanged(const QString &arg1)
{
    proj->alphabet_whitout_empty = arg1.split(" ", Qt::SkipEmptyParts);
}

void CreateProjectForm::on_lineEdit_count_of_states_textChanged(const QString &arg1)
{
    proj->len_of_states = arg1.toInt();
    ui->lineEdit_states->textChanged(ui->lineEdit_states->text());
    if (proj->len_of_states > 0)
    {
        ui->pushButton_next->setEnabled(true);
    }
    else
    {
        ui->pushButton_next->setEnabled(false);
    }
}

void CreateProjectForm::on_lineEdit_states_textChanged(const QString &arg1)
{
    proj->createStates(arg1);
}

void CreateProjectForm::on_pushButton_next_clicked()
{
}
