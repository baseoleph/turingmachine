#ifndef CREATEPROJECTFORM_H
#define CREATEPROJECTFORM_H

#define SIZE_FOR_ALLOC 10

#include <QWidget>
#include <QCloseEvent>
#include <QDebug>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QComboBox>

#include "project/projectfileclass.h"
#include "input_frames/cellform.h"
#include "input_frames/letterform.h"
#include "scene.h"

namespace Ui {
class CreateProjectForm;
}

class CreateProjectForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateProjectForm(QWidget *parent = nullptr, ProjectFileClass *project = nullptr);
    ~CreateProjectForm();

signals:
    void setAlphabetStatesSignal(QList<QString> alphabet, QList<QString> states);
    void emitCloseEventSignal(QCloseEvent *event);
    void emitCloseSignal(CreateProjectForm *form);

private slots:
    void on_lineEdit_alphabet_textEdited(const QString &arg1);
    void on_lineEdit_count_of_states_textEdited(const QString &arg1);
    void on_lineEdit_states_textEdited(const QString &arg1);

    void on_pushButton_fix_signature_clicked();

    void on_pushButton_signature_change_clicked();

    void on_lineEdit_len_of_word_textChanged(const QString &arg1);

    void on_pushButton_set_visible_word_clicked();

    void on_pushButton_add_word_clicked();

    void on_pushButton_delete_current_word_clicked();

    void on_comboBox_words_activated(int index);

    void on_pushButton_fix_tables_clicked();
    void on_pushButton_step_clicked();
    void setUpScene();

    void on_pushButton_change_tables_clicked();

private:
    Ui::CreateProjectForm *ui;
    ProjectFileClass *proj;
    Scene *scene = nullptr;
    QTimer *tm;

    void fillForms();
    void closeEvent(QCloseEvent *event);

    void setInstructions();
    void setTableFrames();
    void generateTable();
    void updateTable();
    void clearTable();
    void clearComboBoxes();

    QList<QString> alphabet;
    QList<QString> states;

    QVector<QVector<QFrame *>> table_frame;
    QVector<QVector<CellForm *>> table_instructions;
    QVector<LetterForm *> vector_word;
    QVector<LetterForm *> visible_letters;
    QVector<QVector<int>> words;
    QVector<QVector<Action>> table_of_actions;



    int len_of_word;
    void setWordFrames(int len);
    void allocWordFrames(int size = SIZE_FOR_ALLOC);
    void clearWordFrames();
    void updateComboWords();

};

#endif // CREATEPROJECTFORM_H
