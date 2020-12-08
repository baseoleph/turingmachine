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

private:
    Ui::ManagerProjectForm *ui;
    ProjectFileClass *proj;
};

#endif // MANAGERPROJECTFORM_H
