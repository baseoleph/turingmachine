#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_form = new CreateProjectForm(this);
    vbox = new QVBoxLayout(ui->centralwidget);
    vbox->addWidget(create_form);


    connect(create_form, &CreateProjectForm::setAlphabetStatesSignal, this, &MainWindow::setAlphabetStates);
}

MainWindow::~MainWindow()
{
    delete vbox;
    delete create_form;
    delete ui;
}

void MainWindow::setAlphabetStates(QList<QString> alphabet, QList<QString> states)
{
    turing.setAlphabetStates(alphabet, states);
//    vbox->removeWidget(create_form);
    create_form->close();
}
