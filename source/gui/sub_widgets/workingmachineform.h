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

#ifndef WORKINGMACHINEFORM_H
#define WORKINGMACHINEFORM_H

#include <QWidget>

#include "scene.h"
#include "core/turingclass.h"

namespace Ui {
class WorkingMachineForm;
}

class WorkingMachineForm : public QWidget
{
    Q_OBJECT

public:
    explicit WorkingMachineForm(QWidget *parent = nullptr, TuringClass *turing = nullptr);
    ~WorkingMachineForm();

private slots:

private:
    Ui::WorkingMachineForm *ui;
    Scene *scene;
    TuringClass *turing;

    QTimer *tm;
};

#endif // WORKINGMACHINEFORM_H
