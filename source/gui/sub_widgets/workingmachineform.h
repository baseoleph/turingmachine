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
    void on_pushButton_step_clicked();
    void setUpScene();

private:
    Ui::WorkingMachineForm *ui;
    Scene *scene;
    TuringClass *turing;

    QTimer *tm;
};

#endif // WORKINGMACHINEFORM_H
