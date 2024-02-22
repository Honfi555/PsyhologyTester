#include "jsoncontroller.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>


JsonTestController::JsonTestController(const QString& path) : path_(path), data_(Test({Question()})) {}

[[nodiscard]] QJsonObject JsonTestController::getDataFromJson() const
{
    QFile file(this->path_);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        return jsonDocument.object();
    }
    return QJsonObject();
}

void JsonTestController::setFilePath(const QString& path)
{
    this->path_ = path;
}

Test JsonTestController::getData()
{
    this->updateData();
    return this->data_;
}

void JsonTestController::updateData()
{
    QJsonObject test_object = this->getDataFromJson();
    std::vector<Question> questions;

    this->data_.setTestType(test_object["test_type"].toString());
    this->data_.setTestName(test_object["test_name"].toString());

    for (const QJsonValue& question : test_object["questions"].toArray()) {
        QJsonObject object = question.toObject();
        questions.push_back(Question(object));
    }

    this->data_.setTestQuestions(questions);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JsonMainFileController::JsonMainFileController(const QString &path) : path_(path)
{
    // check data file's on existance
    if  (!QDir("C:/Tests_Psychology").exists()) {
        QDir().mkdir("C:/Tests_Psychology");
    }
    if (!QFile(this->path_).exists()) {
        QFile file( this->path_ );
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
    }
    if (!QDir("C:/Tests_Psychology/Reports").exists()) {
        QDir().mkdir("C:/Tests_Psychology/Reports");
    }

    this->paths_ = this->getPaths();
}

void JsonMainFileController::setFilePath(const QString &path)
{
    this->path_ = path;
}

void JsonMainFileController::addToJson(const QString &new_path)
{
    QJsonArray jsonArray = this->getDataFromJson();
    jsonArray.append(QJsonValue(new_path));

    QJsonDocument updatedJsonDocument(jsonArray);
    QFile file(this->path_);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(updatedJsonDocument.toJson());
        file.close();
    }
}

void JsonMainFileController::removePathFromJson(const QString& path)
{
    this->paths_ = this->getPaths();

    if (this->paths_.contains(path)) {
        for (int i = 0; i < this->paths_.size(); i++) {
            if (this->paths_.at(i) == path) {
                this->paths_.erase(this->paths_.begin() + i);
                break;
            }
        }

        this->writeToJson(this->paths_);
    }
}

QStringList JsonMainFileController::getPaths() const
{
    QStringList result;
    for (const auto& i : this->getDataFromJson()) {
        result.append(i.toString());
    }
    return result;
}

QJsonArray JsonMainFileController::getDataFromJson() const
{
    QFile file(this->path_);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        return jsonDocument.array();
    }
    return QJsonArray();
}

void JsonMainFileController::writeToJson(const QStringList &paths) const
{
    QJsonArray jsonArrayPaths;
    for (const QString& path : paths) {
        jsonArrayPaths.append(QJsonValue(path));
    }

    QJsonDocument updatedJsonDocument(jsonArrayPaths);
    QFile file(this->path_);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(updatedJsonDocument.toJson());
        file.close();
    }
}
