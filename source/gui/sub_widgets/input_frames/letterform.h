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

#ifndef LETTERFORM_H
#define LETTERFORM_H

#include <QWidget>

namespace Ui {
class LetterForm;
}

class LetterForm : public QWidget
{
    Q_OBJECT

public:
    explicit LetterForm(QWidget *parent = nullptr, QList<QString> a = {});
    ~LetterForm();

    int letter_state = 0;

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::LetterForm *ui;
};

#endif // LETTERFORM_H
