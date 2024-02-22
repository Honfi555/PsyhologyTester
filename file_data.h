#ifndef FILEDATA_H
#define FILEDATA_H

#include <QString>
#include <QFile>


struct Question;
struct Test;
struct ClientData;


struct Question
{
    explicit Question(QString question="Когда стипендиею вернёшь?", QStringList answers={"Сегодня", "Никогда", "Когда рак на горе свиснет"});

    explicit Question(const QJsonObject& question);

    [[nodiscard]] QString getQu() const;

    [[nodiscard]] QStringList getAnswers() const;

    [[nodiscard]] int answersNumber() const;

    [[nodiscard]] QJsonObject getDataJson() const;

    void operator =(const Question& other);

private:
    QString question_;
    QStringList answers_;
};


struct Test
{
    explicit Test(const std::vector<Question>& questions={ Question() });
    explicit Test(const QJsonObject& test);

    [[nodiscard]] std::vector<Question> getQuestions() const;
    [[nodiscard]] QString getTestType() const;
    [[nodiscard]] QString getTestName() const;

    void pushBack_question(const Question& question);
    void setTestType(const QString& test_type);
    void setTestName(const QString& test_name);
    void setTestQuestions(const std::vector<Question>& test_questions);
    virtual void clear();

protected:
    QString test_name_;
    QString test_type_;
    std::vector<Question> questions_;
};

struct ClientData : Test
{
    explicit ClientData(const std::vector<Question>& questions={Question()}, const QString& name="None", const QString& surname="None", const QString& group="None");

    [[nodiscard]] QString getClientName() const;
    [[nodiscard]] QString getClientSurname() const;
    [[nodiscard]] QString getClientGroup() const;

    void setClientName(const QString& name);
    void setClientSurname(const QString& surname);
    void setClientGroup(const QString& group);

    void clear() override;

private:
    QString client_name_;
    QString client_surname_;
    QString client_group_;
};

#endif // FILEDATA_H
