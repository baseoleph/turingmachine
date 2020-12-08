#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vbox = new QVBoxLayout(ui->centralwidget);
    openFormManager(manager_form);
}

MainWindow::~MainWindow()
{
    delete vbox;
    if (manager_form != nullptr) delete create_form;
    if (create_form != nullptr) delete create_form;
    if (input_form != nullptr) delete input_form;
    if (working_form != nullptr) delete working_form;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    myCloseEvent(event);
}

void MainWindow::createProjectSlot()
{
    project = new ProjectFileClass(this);
    connect(project, &ProjectFileClass::emitProjectNameSignal, this, &MainWindow::showProjectNameAnditsState);
    connect(project, &ProjectFileClass::emitOpenFailedSignal, this, &MainWindow::openFailedSlot);
    connect(project, &ProjectFileClass::emitOpenSucces, this, &MainWindow::openSuccesSlot);

    openFormCreate(create_form);
}

void MainWindow::openProjectSlot()
{
    project = new ProjectFileClass(this);
    connect(project, &ProjectFileClass::emitProjectNameSignal, this, &MainWindow::showProjectNameAnditsState);
    connect(project, &ProjectFileClass::emitOpenFailedSignal, this, &MainWindow::openFailedSlot);
    connect(project, &ProjectFileClass::emitOpenSucces, this, &MainWindow::openSuccesSlot);
    project->openProject();
}

void MainWindow::openFormManager(ManagerProjectForm *form)
{
    form = new ManagerProjectForm(this, project);
    connect(form, &ManagerProjectForm::emitCreateProjectSignal, this, &MainWindow::createProjectSlot);
    connect(form, &ManagerProjectForm::emitOpenProjectSignal, this, &MainWindow::openProjectSlot);
    connect(form, &ManagerProjectForm::emitCloseSignal, this, &MainWindow::closeFormManager);
    vbox->addWidget(form);
    current_form = qobject_cast<QWidget *>(vbox->itemAt(vbox->count()-1)->widget());
}

void MainWindow::openFormCreate(CreateProjectForm *form)
{
    form = new CreateProjectForm(this, project);
    connect(form, &CreateProjectForm::emitCloseEventSignal, this, &MainWindow::myCloseEvent);
    connect(form, &CreateProjectForm::emitCloseSignal, this, &MainWindow::closeFormCreate);
    vbox->addWidget(form);
    current_form = qobject_cast<QWidget *>(vbox->itemAt(vbox->count()-1)->widget());
}

void MainWindow::closeFormManager(ManagerProjectForm *form)
{
    disconnect(form, &ManagerProjectForm::emitCreateProjectSignal, this, &MainWindow::createProjectSlot);
    disconnect(form, &ManagerProjectForm::emitOpenProjectSignal, this, &MainWindow::openProjectSlot);
    disconnect(form, &ManagerProjectForm::emitCloseSignal, this, &MainWindow::closeFormManager);
}

void MainWindow::closeFormCreate(CreateProjectForm *form)
{
    disconnect(form, &CreateProjectForm::emitCloseEventSignal, this, &MainWindow::myCloseEvent);
    disconnect(form, &CreateProjectForm::emitCloseSignal, this, &MainWindow::closeFormCreate);
}

void MainWindow::closeFormInput(InputParametersForm *form)
{
   Q_UNUSED(form)
}

void MainWindow::closeFormWorking(WorkingMachineForm *form)
{
    Q_UNUSED(form)
}

bool MainWindow::closePoject()
{
    if (project == nullptr)
    {
        return true;
    }
    else if (project->isSavedCopyShows())
    {
        disconnect(project, &ProjectFileClass::emitProjectNameSignal, this, &MainWindow::showProjectNameAnditsState);
        disconnect(project, &ProjectFileClass::emitOpenFailedSignal, this, &MainWindow::openFailedSlot);
        disconnect(project, &ProjectFileClass::emitOpenSucces, this, &MainWindow::openSuccesSlot);
        delete project;
        project = nullptr;
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::myCloseEvent(QCloseEvent *event)
{
    if (closePoject())
    {
        event->accept();
    }
    else
    {
        int message_box_state = tryToUnsavedClose();
        if (message_box_state == QMessageBox::Save)
        {
            on_action_save_triggered();
            event->accept();
        }
        else if (message_box_state == QMessageBox::Discard)
        {
            event->accept();
        }
        else if (message_box_state == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
}

void MainWindow::on_action_open_triggered()
{
    if (current_form->close())
        openProjectSlot();
}

void MainWindow::on_action_save_triggered()
{
    if (project != nullptr) project->saveProject();
}

void MainWindow::on_action_save_as_triggered()
{
    if (project != nullptr) project->saveAsProject();
}

void MainWindow::showProjectNameAnditsState(QString project_name)
{
//    QString window_title = programName + " - " + project_name;
//    QString window_title = programName;
//    this->setWindowTitle(window_title);
}

int MainWindow::tryToUnsavedClose()
{
    QMessageBox msgBox;
    msgBox.setText("Проект был изменен.");
    msgBox.setInformativeText("Вы хотите его сохранить?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}





void MainWindow::on_action_create_triggered()
{
    if (current_form->close())
        createProjectSlot();
}

void MainWindow::openFailedSlot()
{
    current_form->close();
    openFormManager(manager_form);
}

void MainWindow::openSuccesSlot()
{
    openFormCreate(create_form);
}
