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

#ifndef MANAGERPROJECTFORM_H
#define MANAGERPROJECTFORM_H

#include <QWidget>
#include <QDebug>
#include "project/projectfileclass.h"

namespace Ui {
class ManagerProjectForm;
}

class ManagerProjectForm : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerProjectForm(QWidget *parent = nullptr, ProjectFileClass *project = nullptr);
    ~ManagerProjectForm();

signals:
    void emitCreateProjectSignal();
    void emitOpenProjectSignal();
    void emitCloseSignal(ManagerProjectForm *form);

private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_open_clicked();

private:
    Ui::ManagerProjectForm *ui;
    ProjectFileClass *proj;
};

#endif // MANAGERPROJECTFORM_H
