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
