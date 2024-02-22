#ifndef TESTREPORT_H
#define TESTREPORT_H

#include "file_data.h"


class TestReport
{
public:
    TestReport(const ClientData& client_data, const QString& path);

    void createReport();
private:
    ClientData client_data_;
    QString path_;
};

#endif // TESTREPORT_H
