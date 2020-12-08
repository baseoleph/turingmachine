#include "createprojectform.h"
#include "ui_createprojectform.h"

CreateProjectForm::CreateProjectForm(QWidget *parent, ProjectFileClass *project) :
    QWidget(parent),
    ui(new Ui::CreateProjectForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->proj = project;

    ui->pushButton_change_tables->hide();
    ui->pushButton_fix_tables->hide();
    ui->widget_scene->hide();
    fillForms();

//    tm = new QTimer();
//    connect(tm, &QTimer::timeout, this, &CreateProjectForm::setUpScene);
//    tm->start(100);
}

CreateProjectForm::~CreateProjectForm()
{
    emitCloseSignal(this);
    if (scene != nullptr) delete scene;
    delete ui;
}

void CreateProjectForm::on_lineEdit_alphabet_textEdited(const QString &arg1)
{
    proj->setAlphabet(arg1);
}

void CreateProjectForm::on_lineEdit_count_of_states_textEdited(const QString &arg1)
{
    int len_of_states = arg1.toInt();
    proj->setStates(ui->lineEdit_states->text(), len_of_states);

    if (len_of_states > 0)
    {
        ui->pushButton_fix_signature->setEnabled(true);
    }
    else
    {
        ui->pushButton_fix_signature->setEnabled(false);
    }
}

void CreateProjectForm::on_lineEdit_states_textEdited(const QString &arg1)
{
    proj->setStates(arg1, ui->lineEdit_count_of_states->text().toInt());
}

void CreateProjectForm::fillForms()
{
    if (proj->isSignatureFixed())
    {
        ui->widget_set_signature->hide();
        ui->widget_tables_words->show();

        ui->pushButton_fix_signature->hide();
        ui->pushButton_signature_change->show();
        ui->label_alphabet_text->setText(proj->getAlphabetText());
        ui->label_states_text->setText(proj->getStatesText());


        ui->scrollArea_3->show();
        generateTable();
        updateComboWords();
        updateTable();
        ui->pushButton_fix_tables->show();
    }
    else
    {
//        ui->pushButton_signature_change->click();
        ui->widget_scene->hide();
        ui->widget_tables_words->hide();
        ui->widget_set_signature->show();

        ui->lineEdit_count_of_states->setText(QString::number(proj->getLenOfStates()));
        ui->lineEdit_alphabet->setText(proj->getAlphabetForChange());
        ui->lineEdit_states->setText(proj->getStatesForChange());
        if (ui->lineEdit_count_of_states->text().toInt() > 0)
        {
            ui->pushButton_fix_signature->setEnabled(true);
        }
        else
        {
            ui->pushButton_fix_signature->setEnabled(false);
        }

        ui->label_alphabet_text->clear();
        ui->label_states_text->clear();
        ui->pushButton_fix_signature->show();
        ui->pushButton_signature_change->hide();

        ui->scrollArea_3->hide();
        clearTable();
        clearComboBoxes();
        ui->lineEdit_len_of_word->clear();
    }
}

void CreateProjectForm::closeEvent(QCloseEvent *event)
{
    emitCloseEventSignal(event);
}

void CreateProjectForm::setInstructions()
{
    for (int i = 0; i < states.size(); ++i)
    {
        QVector<CellForm *> tmp;
        for (int j = 0; j < alphabet.size(); ++j)
        {
            tmp.append(new CellForm(this, alphabet, states, &(*proj->table_of_actions)[i][j]));
        }
        table_instructions.append(tmp);
    }
}

void CreateProjectForm::setTableFrames()
{
    for (int i = 0; i < states.size()+1; ++i)
    {
        QVector<QFrame *> tmp;
        for (int j = 0; j < alphabet.size()+1; ++j)
        {
            QFrame *frame = new QFrame();
            frame->setLayout(new QHBoxLayout);
            frame->setMaximumSize(2000, 50);
            frame->setStyleSheet("QFrame{border: 1px solid black;}");
            tmp.append(frame);

            if (i != 0 && j != 0)
            {
                tmp[j]->layout()->addWidget(table_instructions[i-1][j-1]);
            }
            else if (j != 0)
            {
                tmp[j]->layout()->addWidget(new QLabel(alphabet[j-1]));
            }
            else if (i != 0)
            {
                tmp[0]->layout()->addWidget(new QLabel(states[i-1]));
            }
        }
        table_frame.append(tmp);
    }
}

void CreateProjectForm::generateTable()
{
    alphabet.clear();
    alphabet = proj->getAlphabet();
    states.clear();
    states = proj->getStates();

    setInstructions();
    setTableFrames();
    ui->gridLayout->setSpacing(0);
    for (int i = 0; i < table_frame.size(); ++i)
    {
        for (int j = 0; j < table_frame[i].size(); ++j)
        {
            ui->gridLayout->addWidget(table_frame[i][j], i, j);
        }
    }

    ui->widget_table->setMinimumSize(0, table_frame.size()*table_frame[0][0]->height()+15);
}

void CreateProjectForm::updateTable()
{
    for (int i = 0; i < table_instructions.size(); ++i)
    {
        for (int j = 0; j < table_instructions[i].size(); ++j)
        {
            table_instructions[i][j]->a_state = proj->getTable()[i][j].a;
            table_instructions[i][j]->q_state = proj->getTable()[i][j].q;
            table_instructions[i][j]->d_state = proj->getTable()[i][j].d;
            table_instructions[i][j]->updateComboBoxes();
        }
    }
}

void CreateProjectForm::clearTable()
{
    foreach (auto e1, table_instructions)
    {
        foreach (auto e2, e1)
        {
            delete e2;
        }
    }

    table_instructions.clear();
    foreach (auto e1, table_frame)
    {
        foreach (auto e2, e1)
        {
            delete e2;
        }
    }
    table_frame.clear();
}

void CreateProjectForm::clearComboBoxes()
{
    foreach (auto e1, vector_word)
    {
        delete e1;
    }
    vector_word.clear();
    visible_letters.clear();
}

void CreateProjectForm::setWordFrames(int len)
{
    foreach (auto e, vector_word)
    {
        delete e;
    }
    vector_word.clear();

    for (int i = 0; i < len; ++i)
    {
        vector_word.append(new LetterForm(this, alphabet));
        ui->scrollAreaWidgetContents_word->layout()->addWidget(vector_word[i]);
    }
}

void CreateProjectForm::allocWordFrames(int size)
{
    for (int i = 0; i < size; ++i)
    {
        vector_word.append(new LetterForm(this, alphabet));
        ui->scrollAreaWidgetContents_word->layout()->addWidget(vector_word[i]);
    }
}

void CreateProjectForm::clearWordFrames()
{
    foreach (auto e, vector_word)
    {
        delete e;
    }
    vector_word.clear();
}

void CreateProjectForm::updateComboWords()
{
    QVector<QVector<int>> combo_words = proj->getWords();
    QList<QString> alph = proj->getAlphabet();
    ui->comboBox_words->clear();
    foreach (auto e, combo_words)
    {
        QString word_to_combobox;
        foreach (auto e1, e)
        {
            word_to_combobox += alph[e1] + " ";
        }
        ui->comboBox_words->addItem(word_to_combobox);
    }
    ui->comboBox_words->setCurrentIndex(combo_words.size()-1);
}

void CreateProjectForm::on_pushButton_fix_signature_clicked()
{
    proj->setSignatureState(true);
    fillForms();
}

void CreateProjectForm::on_pushButton_signature_change_clicked()
{
    proj->setSignatureState(false);
    fillForms();
}

void CreateProjectForm::on_lineEdit_len_of_word_textChanged(const QString &arg1)
{
    len_of_word = arg1.toInt();
}

void CreateProjectForm::on_pushButton_set_visible_word_clicked()
{
    setWordFrames(len_of_word);
}

void CreateProjectForm::on_pushButton_add_word_clicked()
{
    QVector<int> t;
    foreach (auto e, vector_word)
    {
        t.append(e->letter_state);
    }

    proj->addWord(t);
    updateComboWords();
}

void CreateProjectForm::on_pushButton_delete_current_word_clicked()
{
    if (ui->comboBox_words->count() != 0)
    {
        proj->deleteCurrentWord(ui->comboBox_words->currentIndex());
        updateComboWords();
    }
}

void CreateProjectForm::on_comboBox_words_activated(int index)
{
    proj->setCurrentWord(index);
}

void CreateProjectForm::on_pushButton_fix_tables_clicked()
{
    proj->setCurrentWord(ui->comboBox_words->currentIndex());
    ui->pushButton_fix_tables->hide();
    ui->pushButton_change_tables->show();
    ui->widget_words->hide();
    ui->widget_table->setEnabled(false);
    ui->label_word->setText(proj->getWord());

    ui->widget_scene->show();
    proj->toStart();
    proj->checkEdges();
    if (proj->stepPossible()) ui->pushButton_step->setEnabled(true);
    setUpScene();
}

void CreateProjectForm::on_pushButton_step_clicked()
{
    if (not proj->takeStep())
    {
        ui->pushButton_step->setEnabled(false);
    }
    scene->showState();
}

void CreateProjectForm::setUpScene()
{
    scene = new Scene(ui->graphicsView->width()-10, ui->graphicsView->height()-10, proj->getTuring());

    ui->graphicsView->setScene(scene);
}

void CreateProjectForm::on_pushButton_change_tables_clicked()
{
    proj->toStart();
    ui->pushButton_fix_tables->show();
    ui->pushButton_change_tables->hide();
    ui->widget_words->show();
    ui->widget_scene->hide();
    ui->widget_table->setEnabled(true);
    ui->label_word->clear();

    if (scene != nullptr) delete scene;
}

void CreateProjectForm::on_pushButton_2_clicked()
{
    proj->toStart();
    proj->checkEdges();
    if (proj->stepPossible())
    {
        scene->showState();
        ui->pushButton_step->setEnabled(true);
    }
}
