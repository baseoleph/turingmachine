#ifndef CREATEPROJECTFORM_H
#define CREATEPROJECTFORM_H

#include <QWidget>
#include <QDebug>

#include "project/projectfileclass.h"

namespace Ui {
class CreateProjectForm;
}

class CreateProjectForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateProjectForm(QWidget *parent = nullptr, ProjectFileClass *project = nullptr);
    ~CreateProjectForm();

signals:
    void setAlphabetStatesSignal(QList<QString> alphabet, QList<QString> states);

private slots:
    void on_lineEdit_alphabet_textChanged(const QString &arg1);
    void on_lineEdit_count_of_states_textChanged(const QString &arg1);
    void on_lineEdit_states_textChanged(const QString &arg1);
    void on_pushButton_next_clicked();

private:
    Ui::CreateProjectForm *ui;
    ProjectFileClass *proj;
};

#endif // CREATEPROJECTFORM_H
