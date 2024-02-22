#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include <QString>
#include <QStringList>
#include "file_data.h"


class JsonTestController;
class JsonMainFileController;


class JsonTestController
{
public:
    JsonTestController(const QString& path);

    void setFilePath(const QString& path);
    [[nodiscard]] Test getData();

private:
    void updateData();

    [[nodiscard]] QJsonObject getDataFromJson() const;

    QString path_;
    Test data_;
};


class JsonMainFileController
{
public:
    explicit JsonMainFileController(const QString& path);

    void setFilePath(const QString& path);

    [[nodiscard]] QStringList getPaths() const;
    void addToJson(const QString& new_path);

    void removePathFromJson(const QString& path);

private:
    [[nodiscard]] QJsonArray getDataFromJson() const;
    void writeToJson(const QStringList& paths) const;

    QString path_;
    QStringList paths_;
};

#endif // JSONCONTROLLER_H
