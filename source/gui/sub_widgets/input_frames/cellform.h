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

#ifndef CELLFORM_H
#define CELLFORM_H

#include <QWidget>
#include <QDebug>
#include <QSpinBox>
#include "core/Action.h"

namespace Ui {
class CellForm;
}

class CellForm : public QWidget
{
    Q_OBJECT

public:
    explicit CellForm(QWidget *parent = nullptr, QList<QString> a = {}, QList<QString> q = {}, Action *act = nullptr);
    ~CellForm();

    int a_state = 0;
    int q_state = 0;
    int d_state = 0;
    Action *act;
    void updateComboBoxes();

private slots:
    void on_comboBox_q_activated(int index);

    void on_comboBox_a_activated(int index);

    void on_comboBox_d_activated(int index);

private:
    Ui::CellForm *ui;

};

#endif // CELLFORM_H
