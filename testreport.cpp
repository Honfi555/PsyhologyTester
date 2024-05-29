#include "testreport.h"
#include <QString>


TestReport::TestReport(const ClientData &client_data, const QString &path) : client_data_(client_data), path_(path) {}

bool TestReport::createReport()
{
    this->path_ += "\\Отчёт " + this->client_data_.getClientGroup() +
                   " " + this->client_data_.getTestName() +
                   " " + this->client_data_.getClientName() +
                   " " + this->client_data_.getClientSurname() + ".html";

    QString report_text = "<h1 style=\"font-family:Comic Sans MS\"><b> Названия теста: " + this->client_data_.getTestName() + "</b></h1>" +
                              "\n<h3 style=\"font-family:Comic Sans MS\"> Группа, имя, фамилия: " + this->client_data_.getClientGroup() +
                              " " + this->client_data_.getClientName() +
                          " " + this->client_data_.getClientSurname() + "</h3>\n";

    report_text += "<body style=\"background-color:blanchedalmond\">\n<div class=\"Answers\">\n";
    for (const Question& question : this->client_data_.getQuestions()) {
        report_text += "\t<p style=\"font-family:Comic Sans MS\"><t>" + question.getQu() + " - " + question.getAnswers().at(0) + "</p>\n";
    }
    report_text += "</div>\n</body>";

    QFile file(this->path_);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(report_text.toStdString().c_str());
        file.close();

        return true;
    }

    return false;
}
