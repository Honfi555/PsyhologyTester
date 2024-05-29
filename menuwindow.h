#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <qpushbutton>
#include "file_data.h"
#include "CustomWidgets/QQuestionWidget/qquestionwidget.h"
#include "CustomWidgets/ReportWidget/reportwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void update_listWidget();

private slots:
    void update_question_questionnaire();

    void update_question_complete();

    void on_btn_page1_clicked();

    void on_btn_page2_clicked();

    void on_btn_page3_clicked();

    void on_btn_page6_clicked();

    void on_btn_addTest_clicked();

    void on_btn_deleteTest_clicked();

    void on_btn_report_clicked();

    void on_btn_exit_clicked();

private:
    Ui::MainWindow *ui;
    QQuestionWidget* questionnaire_widget;
    QQuestionWidget* complete_widget;
    ReportWidget* report_widget;

    Test test_data_;
    ClientData client_answers_;
    std::map<QString, QString> tests_paths_;

    QString mainFilePath_;
    unsigned int number_of_question_;
};

#endif // MENUWINDOW_H
