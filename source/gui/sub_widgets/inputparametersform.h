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

#ifndef INPUTPARAMETERSFORM_H
#define INPUTPARAMETERSFORM_H


#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDebug>

#include "input_frames/cellform.h"
#include "input_frames/letterform.h"

namespace Ui {
class InputParametersForm;
}

class InputParametersForm : public QWidget
{
    Q_OBJECT

public:
    explicit InputParametersForm(QWidget *parent = nullptr, QList<QString> alphabet = {}, QList<QString> states = {});
    ~InputParametersForm();

signals:
    void tableWordSignal(QVector<QVector<Action>> table, QVector<int> word);

private slots:

    void on_pushButton_next_clicked();

private:
    Ui::InputParametersForm *ui;
    QList<QString> alphabet;
    QList<QString> states;

    QVector<QVector<QFrame *>> table_frame;
    QVector<QVector<CellForm *>> table_instructions;
    QVector<LetterForm *> vector_word;
    QVector<LetterForm *> visible_letters;
    QVector<QVector<int>> words;
    QVector<QVector<Action>> table_of_actions;


};

#endif // INPUTPARAMETERSFORM_H
