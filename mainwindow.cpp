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

    ////
    turing.alphabet = {"a", "s", "b", "*"};
    turing.states = {"q0", "q1", "q2", "q43", "qqqq"};
//    turing.alphabet = {"a"};
//    turing.states = {"ad"};
    vbox->removeWidget(create_form);
    create_form->close();

    input_form = new InputParametersForm(this, turing.alphabet, turing.states);
    vbox->addWidget(input_form);

    ////
    connect(create_form, &CreateProjectForm::setAlphabetStatesSignal, this, &MainWindow::setAlphabetStates);
    connect(input_form, &InputParametersForm::tableWordSignal, this, &MainWindow::tableWordSlot);
}

MainWindow::~MainWindow()
{
    delete vbox;
    delete create_form;
    if (input_form != nullptr) delete input_form;
    delete ui;
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
