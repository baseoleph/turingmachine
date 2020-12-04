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
