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

void MainWindow::createProjectSlot()
{
    project = new ProjectFileClass(this);
    connect(project, &ProjectFileClass::emitProjectNameSignal, this, &MainWindow::showProjectNameAnditsState);

    manager_form = nullptr;
    openFormCreate(create_form);
}

void MainWindow::setAlphabetStates(QList<QString> alphabet, QList<QString> states)
{
    turing.setAlphabetStates(alphabet, states);
    vbox->removeWidget(create_form);
    create_form->close();

    input_form = new InputParametersForm(this, alphabet, states);
    vbox->addWidget(input_form);
}

void MainWindow::tableWordSlot(QVector<QVector<Action> > table, QVector<int> word)
{
    turing.table_of_actions = table;
    turing.word = word;

    vbox->removeWidget(input_form);
    input_form->close();
    qDebug() << turing.word;
}

void MainWindow::openFormManager(ManagerProjectForm *form)
{
    form = new ManagerProjectForm(this, project);
    vbox->addWidget(form);
    connect(form, &ManagerProjectForm::emitCreateProjectSignal, this, &MainWindow::createProjectSlot);
}

void MainWindow::openFormCreate(CreateProjectForm *form)
{
    form = new CreateProjectForm(this, project);
    vbox->addWidget(form);
}

void MainWindow::on_action_open_triggered()
{
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
    QString window_title = programName + " - " + project_name;
    this->setWindowTitle(window_title);
}
