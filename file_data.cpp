#include "file_data.h"

#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QDir>
#include <vector>
#include <QFile>
#include <QMessageBox>
#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>


QJsonObject Question::getDataJson() const
{
    QJsonObject dataJson;
    QJsonArray answers;
    dataJson["question"] = this->question_;

    int i = 0;
    QJsonObject answerJson;
    for (const QString& answer : this->answers_) {
        answerJson[answer + QString::number(i)] = answer;
        answers.append(answerJson);
        i++;
    }

    dataJson["answers"] = answers;

    return dataJson;
}

void Question::operator =(const Question &other)
{
    this->question_ = other.question_;
    this->answers_ = other.answers_;
}

Question::Question(QString qu, QStringList answers) : question_(qu), answers_(answers) {}

Question::Question(const QJsonObject &question)
{
    this->question_ = question["question"].toString();
    for (const QJsonValue& answer : question["answers"].toArray()) {
        this->answers_.append(answer.toString());
    }
}

QString Question::getQu() const
{
    return this->question_;
}

QStringList Question::getAnswers() const
{
    return this->answers_;
}

QString Test::getTestName() const
{
    return this->test_name_;
}

void Test::pushBack_question(const Question &question)
{
    this->questions_.push_back(question);
}

int Question::answersNumber() const
{
    return this->getAnswers().count();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Test::Test(const std::vector<Question> &questions) : questions_(questions) {}

Test::Test(const QJsonObject &test)
{
    this->test_name_ = test["test_name"].toString();
    this->test_type_ = test["test_type"].toString();

    this->questions_.clear();
    for (const auto& question : test["questions"].toArray()) {
        this->questions_.push_back(Question(question.toObject()));
    }
}

std::vector<Question> Test::getQuestions() const
{
    return this->questions_;
}

QString Test::getTestType() const
{
    return this->test_type_;
}

void Test::setTestType(const QString& test_type) {
    this->test_type_ = test_type;
}

void Test::setTestName(const QString& test_name)
{
    this->test_name_ = test_name;
}

void Test::setTestQuestions(const std::vector<Question> &test_questions)
{
    this->questions_.clear();
    for (const auto& question : test_questions) {
        this->questions_.push_back(question);
    }
}

void Test::clear()
{
    this->test_name_.clear();
    this->test_type_.clear();
    this->questions_.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ClientData::ClientData(const std::vector<Question> &questions, const QString &name, const QString &surname, const QString &group) :
    Test::Test(questions), client_name_(name), client_surname_(surname), client_group_(group) {}

QString ClientData::getClientName() const
{
    return this->client_name_;
}

QString ClientData::getClientSurname() const
{
    return this->client_surname_;
}

QString ClientData::getClientGroup() const
{
    return this->client_group_;
}

void ClientData::setClientName(const QString &name)
{
    this->client_name_ = name;
}

void ClientData::setClientSurname(const QString &surname)
{
    this->client_surname_ = surname;
}

void ClientData::setClientGroup(const QString &group)
{
    this->client_group_ = group;
}

void ClientData::clear()
{
    Test::clear();

    this->client_name_.clear();
    this->client_surname_.clear();
    this->client_group_.clear();
}
