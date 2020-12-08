#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMainWindow>
#include "core/turingclass.h"
#include "project/projectfileclass.h"

#include "sub_widgets/managerprojectform.h"
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
    void createProjectSlot();
    void openProjectSlot();

    void on_action_open_triggered();

    void on_action_save_triggered();

    void on_action_save_as_triggered();
    void showProjectNameAnditsState(QString project_name);

    void on_action_create_triggered();

    void openFailedSlot();
    void openSuccesSlot();

private:
    Ui::MainWindow *ui;
    ProjectFileClass *project = nullptr;
    TuringClass turing;

    ManagerProjectForm *manager_form = nullptr;
    CreateProjectForm *create_form = nullptr;
    InputParametersForm *input_form = nullptr;
    WorkingMachineForm *working_form = nullptr;
    QWidget *current_form = nullptr;

    QVBoxLayout *vbox;

    void openFormManager(ManagerProjectForm *form);
    void openFormCreate(CreateProjectForm *form);
    void openFormInput(InputParametersForm *form);
    void openFormWorking(WorkingMachineForm *form);

    void closeFormManager(ManagerProjectForm *form);
    void closeFormCreate(CreateProjectForm *form);
    void closeFormInput(InputParametersForm *form);
    void closeFormWorking(WorkingMachineForm *form);

    bool closePoject();
    const QString programName = "Turing Machine";

    void myCloseEvent(QCloseEvent *event);
    void closeEvent(QCloseEvent *event);
    int tryToUnsavedClose();
};
#endif // MAINWINDOW_H
