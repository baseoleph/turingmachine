#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>

#include <QMainWindow>
#include "core/turingclass.h"
#include "sub_widgets/createprojectform.h"
#include "sub_widgets/inputparametersform.h"
#include "sub_widgets/workingmachineform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setAlphabetStates(QList<QString> alphabet, QList<QString> states);
    void tableWordSlot(QVector<QVector<Action>> table, QVector<int> word);

private:
    Ui::MainWindow *ui;
    TuringClass turing;
    CreateProjectForm *create_form = nullptr;
    InputParametersForm *input_form = nullptr;
    WorkingMachineForm *working_form = nullptr;

    QVBoxLayout *vbox;
};
#endif // MAINWINDOW_H
