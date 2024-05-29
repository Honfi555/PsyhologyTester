#include "qquestionwidget.h"
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>


QQuestionWidget::QQuestionWidget(QWidget *parent, const QString& question, const QStringList& answers, const QTestType& test_type)
    : QWidget{parent}, question_(question), answers_(answers), test_type_(test_type)
{
    this->margin_ = 4;
    this->background_color_ = Qt::white;

    repaint();

    connect(this, SIGNAL(questionChanged()), SLOT(repaint()));
    connect(this, SIGNAL(answersChanged()), SLOT(repaint()));
    connect(this, SIGNAL(testTypeChanged()), SLOT(repaint()));

    connect(this, SIGNAL(marginChanged()), SLOT(repaint()));
    connect(this, SIGNAL(colorChanged()), SLOT(repaint()));
}

void QQuestionWidget::setQuestion(const QString &question) {
    this->question_ = question;
    emit this->questionChanged();
}

void QQuestionWidget::setAnswers(const QStringList &answers) {
    this->answers_ = answers;
    emit this->answersChanged();
}

void QQuestionWidget::setTestType(const QTestType &test_type) {
    this->test_type_ = test_type;
    emit this->testTypeChanged();
}

void QQuestionWidget::setColor(const QColor &color) {
    this->background_color_ = color;
    emit this->colorChanged();
}

void QQuestionWidget::setMargin(const int &margin)
{
    this->margin_ = margin;
    emit this->marginChanged();
}

void QQuestionWidget::repaint()
{/*
    this->setLayout(new (nullptr));*/

    // QHBoxLayout* hLayout = new QHBoxLayout(this);
    // QLabel* label = new QLabel(this);
    // label->setText(this->question_);
    // label->setAlignment(Qt::AlignCenter);
    // label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    // label->setPixmap(QPixmap(this->size().width(), this->size().height()));
    // hLayout->addWidget(label);

    QGridLayout* grid_layout = new QGridLayout(this);
    // grid_layout->addWidget(label, 1, 3);
    // QWidget* hSpacer = new QWidget();
    // hSpacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    // grid_layout->addWidget(hSpacer, 0, 0);

    // QWidget* hSpacer_1 = new QWidget();
    // hSpacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    // grid_layout->addWidget(hSpacer_1, 0, 4);

    for (int i = 0, row = 0, column = 0; i < this->answers_.size(); i++, column += 2) {
        QPushButton* btn = new QPushButton(this);
        btn->setText(this->answers_.at(i));

        grid_layout->addWidget(btn, row, column);
        // if (i % 2 == 0 && i != 0) {
        //     column = 2;
        //     grid_layout->addWidget(btn, row, column);
        //     row++;
        // }
        // else {
        //     column = 0;
        //     grid_layout->addWidget(btn, row, column);
        // }
    }
    // this->layout()->addItem(grid_layout);
    // this->layout()->setAlignment(Qt::AlignCenter);
    // this->layout()->addItem(grid_layout);
}
