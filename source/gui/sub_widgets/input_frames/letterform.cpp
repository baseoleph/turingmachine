#include "letterform.h"
#include "ui_letterform.h"

LetterForm::LetterForm(QWidget *parent, QList<QString> a) :
    QWidget(parent),
    ui(new Ui::LetterForm)
{
    ui->setupUi(this);
    foreach (auto e, a)
    {
        ui->comboBox->addItem(e);
    }
}

LetterForm::~LetterForm()
{
    delete ui;
}

void LetterForm::on_comboBox_activated(int index)
{
    letter_state = index;
}
