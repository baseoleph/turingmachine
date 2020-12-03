#include "createprojectform.h"
#include "ui_createprojectform.h"

CreateProjectForm::CreateProjectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateProjectForm)
{
    ui->setupUi(this);
}

CreateProjectForm::~CreateProjectForm()
{
    delete ui;
}

void CreateProjectForm::on_lineEdit_alphabet_textChanged(const QString &arg1)
{
    alphabet.clear();
    alphabet = arg1.split(" ", Qt::SkipEmptyParts);
}

void CreateProjectForm::on_lineEdit_count_of_states_textChanged(const QString &arg1)
{
    len_of_states = arg1.toInt();
    if (len_of_states > 0)
    {
        createAutomaticStates();
        ui->pushButton_next->setEnabled(true);
    }
    else
    {
        ui->pushButton_next->setEnabled(false);
    }
}

void CreateProjectForm::on_lineEdit_states_textChanged(const QString &arg1)
{
    createAutomaticStates();
    QList<QString> temp_states = arg1.split(" ", Qt::SkipEmptyParts);
    for (int i = 0; i < states.size() && i < temp_states.size(); ++i)
    {
        states[i] = temp_states[i];
    }

    qDebug() << states;
}

void CreateProjectForm::createAutomaticStates()
{
    states.clear();
    for (int i = 0; i < len_of_states; ++i)
    {
        states.append("q" + QString::number(i));
    }
}

void CreateProjectForm::on_pushButton_next_clicked()
{
    setAlphabetStatesSignal(alphabet, states);
}
