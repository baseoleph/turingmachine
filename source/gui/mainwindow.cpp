#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    create_form = new CreateProjectForm(this);
//    working_form = new WorkingMachineForm(this, &turing);
    vbox = new QVBoxLayout(ui->centralwidget);
//    vbox->addWidget(working_form);

//    ////
//    turing.alphabet = {"a", "s", "b", "*"};
//    turing.states = {"q0", "q1", "q2", "q43", "qqqq"};
////    turing.alphabet = {"a"};
////    turing.states = {"ad"};
//    vbox->removeWidget(create_form);
//    create_form->close();

//    input_form = new InputParametersForm(this, turing.alphabet, turing.states);
//    vbox->addWidget(input_form);

    ////

    openFormManager(manager_form);

//    connect(create_form, &CreateProjectForm::setAlphabetStatesSignal, this, &MainWindow::setAlphabetStates);

//    connect(input_form, &InputParametersForm::tableWordSignal, this, &MainWindow::tableWordSlot);
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
    project = new ProjectFileClass(this, true);
    form = new CreateProjectForm(this, project);
    vbox->addWidget(form);
}

void MainWindow::on_action_open_triggered()
{
}

void MainWindow::on_action_save_triggered()
{
}

void MainWindow::on_action_save_as_triggered()
{
    if (project != nullptr) project->saveAsProject();
}
