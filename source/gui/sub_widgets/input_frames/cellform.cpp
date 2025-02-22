// Turing Machine
// Copyright (C) 2020 baseoleph@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

void CellForm::updateComboBoxes()
{
    ui->comboBox_a->setCurrentIndex(a_state+1);
    ui->comboBox_q->setCurrentIndex(q_state+1);
    ui->comboBox_d->setCurrentIndex(d_state);
}

void CellForm::on_comboBox_q_activated(int index)
{
    q_state = index-1;
    act->q = q_state;
}

void CellForm::on_comboBox_a_activated(int index)
{
    a_state = index-1;
    act->a = a_state;
}

void CellForm::on_comboBox_d_activated(int index)
{
    d_state = index;
    act->d = index;
}


