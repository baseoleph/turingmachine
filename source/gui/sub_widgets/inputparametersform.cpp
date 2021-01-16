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

#include "inputparametersform.h"
#include "ui_inputparametersform.h"

InputParametersForm::InputParametersForm(QWidget *parent, QList<QString> alphabet, QList<QString> states) :
    QWidget(parent),
    ui(new Ui::InputParametersForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->alphabet = alphabet;
    this->states = states;


}

InputParametersForm::~InputParametersForm()
{

    delete ui;
}

















void InputParametersForm::on_pushButton_next_clicked()
{
    table_of_actions.clear();
    for (int i = 0; i < table_instructions.size(); ++i)
    {
        QVector<Action> tmp;
        for (int j = 0; j < table_instructions[i].size(); ++j)
        {
            Action act;
            act.a = table_instructions[i][j]->a_state;
            act.q = table_instructions[i][j]->q_state;
            act.d = table_instructions[i][j]->d_state;
            tmp.append(act);
        }
        table_of_actions.append(tmp);
    }

    tableWordSignal(table_of_actions, words[ui->comboBox_words->currentIndex()]);
}


