#include "inputparametersform.h"
#include "ui_inputparametersform.h"

InputParametersForm::InputParametersForm(QWidget *parent, QList<QString> alphabet, QList<QString> states) :
    QWidget(parent),
    ui(new Ui::InputParametersForm)
{
    ui->setupUi(this);
    this->alphabet = alphabet;
    this->states = states;


    QComboBox *alph = new QComboBox(this);
    QComboBox *stat = new QComboBox;
    for (int i = 0; i < states.size(); ++i)
    {
        QLabel *tmp = new QLabel(states[i]);
        stat->addItem(states[i]);
//        tmp->setGeometry(0, 0, 10, 10);
//        tmp->setMaximumSize(30, 30);
//        tmp->setStyleSheet("QFrame{border: 1px solid black;}");
        label_states.append(tmp);

//        table_frame[i+1][0]->layout()->addWidget(tmp);
    }
    for (int i = 0; i < alphabet.size(); ++i)
    {
        QLabel *tmp = new QLabel(alphabet[i]);
        alph->addItem(alphabet[i]);
//        tmp->setMaximumSize(30, 30);
//        tmp->setStyleSheet("QFrame{border: 1px solid black;}");
        label_alphabet.append(tmp);

//        table_frame[0][i+1]->layout()->addWidget(tmp);
    }

    for (int i = 0; i < states.size()+1; ++i)
    {
        QVector<QFrame *> tmp;
        for (int j = 0; j < alphabet.size()+1; ++j)
        {
            QFrame *frame = new QFrame();
//            frame->setMaximumSize(80, 40);
            frame->setLayout(new QHBoxLayout);
            frame->setStyleSheet("QFrame{border: 1px solid black;}");
            tmp.append(frame);
            if (i != 0 && j != 0)
            {
                tmp[j]->layout()->addWidget(alph);
                tmp[j]->layout()->addWidget(stat);
            }
            else if (j != 0)
            {
                tmp[j]->layout()->addWidget(label_alphabet[j-1]);
            }
            else if (i != 0)
            {
                tmp[0]->layout()->addWidget(label_states[i-1]);
            }
        }
        table_frame.append(tmp);
    }
    for (int i = 0; i < table_frame.size(); ++i)
    {
        for (int j = 0; j < table_frame[i].size(); ++j)
        {
            ui->gridLayout->addWidget(table_frame[i][j], i, j);
        }
    }
//    for (int i = 0; i < states.size(); ++i)
//    {
//        ui->gridLayout->addWidget(label_states[i], i+1, 0, 1, 1);
//        for (int j = 0; j < alphabet.size(); ++j)
//        {
//            if (i == 0)
//            {
//                ui->gridLayout->addWidget(label_alphabet[j], 0, j+1, 1, 1);
//            }
//            else
//            {
//                QFrame *frame = new QFrame();
//                frame->setLayout(new QHBoxLayout);
//                frame->setStyleSheet("QFrame{border: 1px solid black;}");
//                frame->layout()->addWidget(new QComboBox(this));
//                frame->layout()->addWidget(new QComboBox(this));
//                frame->layout()->addWidget(new QComboBox(this));
//                ui->gridLayout->addWidget(frame, i+1, j+1, 1, 1);
//            }
//        }
//    }



//    ui->gridLayout->setHorizontalSpacing(200);


//    ui->widget->setLayout(new QVBoxLayout);
//    QScrollArea *area = new QScrollArea(this);
//    area->setWidgetResizable(true);
//    area->setWidget(new QWidget);
//    QGridLayout *grid = new QGridLayout;
//    area->widget()->setLayout(grid);
//    ui->widget->layout()->addWidget(area);

//    for(int row = 0; row < states.size(); row++)
//    {
//        for(int column = 0; column < alphabet.size(); column++)
//        {
//            QFrame *container = new QFrame; // this is your widget.. you can also subclass QWidget to make a custom widget.. might be better design
//            container->setStyleSheet("QFrame{border: 1px solid black;}"); // just to see the shapes better.. you don't need this
//            container->setLayout(new QVBoxLayout); // a layout for your widget.. again, if you subclass QWidget do this in its constructor
//            container->layout()->addWidget(new QLabel("TOP")); // the top label.. in your case where you show the icon
//            container->layout()->addWidget(new QLabel("BOTTOM")); // the bottom label.. in your case where you show the tag
//            grid->addWidget(container, row, column); // add the widget to the grid
//        }
//    }
}

InputParametersForm::~InputParametersForm()
{
    delete ui;
}
