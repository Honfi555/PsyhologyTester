#ifndef QQUESTIONWIDGET_H
#define QQUESTIONWIDGET_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMargins>


class QQuestionWidget : public QWidget
{
    Q_OBJECT
public:
    enum QTestType {
        Questionnaire,
        Complete_sentence
    };

    explicit QQuestionWidget(QWidget *parent = nullptr,
                             const QString& question = "How old are you?",
                             const QStringList& answers = {"under 15", "from 15 to 30", "over 30"},
                             const QTestType& test_type = QTestType::Questionnaire);

    void setQuestion(const QString& question);
    void setAnswers(const QStringList& answers);
    void setTestType(const QTestType& test_type);

    void setColor(const QColor& color);
    void setMargin(const int& margin);

public slots:
    void repaint();

private:
    QString question_;
    QStringList answers_;
    QTestType test_type_;

    QColor background_color_;
    QMargins margins_;
    int margin_;

signals:
    void questionChanged();
    void answersChanged();
    void testTypeChanged();

    void colorChanged();
    void marginChanged();
};

#endif // QQUESTIONWIDGET_H
