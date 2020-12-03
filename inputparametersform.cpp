#include "inputparametersform.h"
#include "ui_inputparametersform.h"

InputParametersForm::InputParametersForm(QWidget *parent, QList<QString> alphabet, QList<QString> states) :
    QWidget(parent),
    ui(new Ui::InputParametersForm)
{
    ui->setupUi(this);
    this->alphabet = alphabet;
    this->states = states;

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


    ui->horizontalLayout_word->addWidget(new QComboBox);
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

    delete ui;
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
