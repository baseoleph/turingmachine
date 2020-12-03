#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "turingclass.h"
#include "createprojectform.h"
#include <QVBoxLayout>

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

private:
    Ui::MainWindow *ui;
    TuringClass turing;
    CreateProjectForm *create_form;

    QVBoxLayout *vbox;
};
#endif // MAINWINDOW_H
