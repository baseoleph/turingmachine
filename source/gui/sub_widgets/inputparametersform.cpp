#include "inputparametersform.h"
#include "ui_inputparametersform.h"

InputParametersForm::InputParametersForm(QWidget *parent, QList<QString> alphabet, QList<QString> states) :
    QWidget(parent),
    ui(new Ui::InputParametersForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->alphabet = alphabet;
    this->states = states;

    setInstructions();
    setTableFrames();
    setWordFrames(1);
    ui->gridLayout->setSpacing(0);
    for (int i = 0; i < table_frame.size(); ++i)
    {
        for (int j = 0; j < table_frame[i].size(); ++j)
        {
            ui->gridLayout->addWidget(table_frame[i][j], i, j);
        }
    }
}

InputParametersForm::~InputParametersForm()
{
    foreach (auto e1, table_instructions)
    {
        foreach (auto e2, e1)
        {
            delete e2;
        }
    }

    foreach (auto e1, table_frame)
    {
        foreach (auto e2, e1)
        {
            delete e2;
        }
    }

    clearWordFrames();
    delete ui;
}

void InputParametersForm::clearWordFrames()
{
    foreach (auto e, vector_word)
    {
        delete e;
    }
    vector_word.clear();
}

void InputParametersForm::setInstructions()
{
    for (int i = 0; i < states.size(); ++i)
    {
        QVector<CellForm *> tmp;
        for (int j = 0; j < alphabet.size(); ++j)
        {
            tmp.append(new CellForm(this, alphabet, states));
        }
        table_instructions.append(tmp);
    }
}

void InputParametersForm::setTableFrames()
{
    for (int i = 0; i < states.size()+1; ++i)
    {
        QVector<QFrame *> tmp;
        for (int j = 0; j < alphabet.size()+1; ++j)
        {
            QFrame *frame = new QFrame();
            frame->setLayout(new QHBoxLayout);
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

void InputParametersForm::setWordFrames(int len)
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

void InputParametersForm::allocWordFrames(int size)
{
    for (int i = 0; i < size; ++i)
    {
        vector_word.append(new LetterForm(this, alphabet));
        ui->scrollAreaWidgetContents_word->layout()->addWidget(vector_word[i]);
    }
}


void InputParametersForm::on_lineEdit_len_of_word_textChanged(const QString &arg1)
{
    len_of_word = arg1.toInt();
}

void InputParametersForm::on_pushButton_set_visible_word_clicked()
{
    setWordFrames(len_of_word);
}

void InputParametersForm::on_pushButton_add_word_clicked()
{
    QVector<int> t;
    foreach (auto e, vector_word)
    {
        t.append(e->letter_state);
    }
    words.append(t);
    QString word_to_combobox = "";
    foreach (auto e, words.last())
    {
        word_to_combobox += alphabet[e];
    }
    ui->comboBox_words->addItem(word_to_combobox);
}
void InputParametersForm::on_pushButton_next_clicked()
{
    table_of_actions.clear();
    for (int i = 0; i < table_instructions.size(); ++i)
    {
        QVector<Action> tmp;
        for (int j = 0; j < table_instructions[i].size(); ++j)
        {
            Action act;
            act.a = table_instructions[i][j]->a_state;
            act.q = table_instructions[i][j]->q_state;
            act.d = table_instructions[i][j]->d_state;
            tmp.append(act);
        }
        table_of_actions.append(tmp);
    }

    tableWordSignal(table_of_actions, words[ui->comboBox_words->currentIndex()]);
}
