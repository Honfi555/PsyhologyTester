#include "menuwindow.h"
#include "ui_menuwindow.h"

#include "jsoncontroller.h"
#include "testreport.h"

#include <QDebug>
#include <QFileDialog>
#include <QWidget>
#include <vector>
#include <QString>
#include <QMessageBox>
#include <QIcon>
#include <QStyleOption>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , questionnaire_widget(new QQuestionWidget())
    , complete_widget(new QQuestionWidget())
    , report_widget(new ReportWidget())
    , test_data_(Test({ Question() }))
    , mainFilePath_("C:/Tests_Psychology/tests_path.json")
    , number_of_question_(0)
{   
    // setup window
    ui->setupUi(this);
    this->setWindowTitle("Тестировщик");
    this->setWindowIcon(QIcon(":/app.ico"));

    // connect buttons
    connect(ui->btn_page1_2, SIGNAL(clicked()), this, SLOT(on_btn_page1_clicked()));
    connect(ui->btn_page1_4, SIGNAL(clicked()), this, SLOT(on_btn_page1_clicked()));
    connect(ui->btn_exit_2, SIGNAL(clicked()), this, SLOT(on_btn_exit_clicked()));

    connect(questionnaire_widget, SIGNAL(btnExitClicked()), this, SLOT(on_btn_page6_clicked()));
    connect(questionnaire_widget, SIGNAL(btnAnswerClicked()), this, SLOT(update_question_questionnaire()));

    connect(complete_widget, SIGNAL(btnExitClicked()), this, SLOT(on_btn_page6_clicked()));
    connect(complete_widget, SIGNAL(btnAnswerClicked()), this, SLOT(update_question_complete()));

    // edit window widgets
    ui->statusbar->hide();
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->page_3->layout()->addWidget(questionnaire_widget);
    ui->page_5->layout()->addWidget(complete_widget);
    ui->formLayout_2->addWidget(report_widget);
    update_listWidget();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_question_questionnaire()
{
    if (number_of_question_ < this->test_data_.getQuestions().size()) {
        this->questionnaire_widget->setTestType(QTestType::Questionnaire);
        this->questionnaire_widget->setQuestion(this->test_data_.getQuestions().at(this->number_of_question_).getQu());
        this->questionnaire_widget->setAnswers(this->test_data_.getQuestions().at(this->number_of_question_).getAnswers());

        if (this->number_of_question_ != 0)
            this->client_answers_.pushBack_question(Question(this->test_data_.getQuestions().at(this->number_of_question_ - 1).getQu(),
                                                             {questionnaire_widget->getCurrentAsnwer()}));
        this->number_of_question_++;
    }
    else {
        this->client_answers_.pushBack_question(Question(this->test_data_.getQuestions().at(this->number_of_question_ - 1).getQu(),
                                                         {questionnaire_widget->getCurrentAsnwer()}));

        this->on_btn_page6_clicked();
    }
}


void MainWindow::update_question_complete()
{
    if (number_of_question_ < this->test_data_.getQuestions().size()) {
        this->complete_widget->setTestType(QTestType::Complete_sentence);
        this->complete_widget->setQuestion(this->test_data_.getQuestions().at(this->number_of_question_).getQu());

        if (this->number_of_question_ != 0)
            this->client_answers_.pushBack_question(Question(this->test_data_.getQuestions().at(this->number_of_question_ - 1).getQu(),
                                                    {complete_widget->getCurrentAsnwer()}));
        this->number_of_question_++;
    }
    else {
        this->client_answers_.pushBack_question(Question(this->test_data_.getQuestions().at(this->number_of_question_ - 1).getQu(),
                                                         {complete_widget->getCurrentAsnwer()}));

        this->on_btn_page6_clicked();
    }
}


void MainWindow::update_listWidget()
{
    ui->listWidget->clear();
    this->tests_paths_.clear();

    QStringList tests_path = JsonMainFileController(this->mainFilePath_).getPaths();

    for (const QString& path : tests_path){
        QString name = JsonTestController(path).getData().getTestName();
        ui->listWidget->addItem(name);
        this->tests_paths_.insert({name, path});
    }
}


void MainWindow::on_btn_page1_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void MainWindow::on_btn_page2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void MainWindow::on_btn_page3_clicked()
{
    this->test_data_ = JsonTestController(this->tests_paths_.at(ui->listWidget->currentItem()->text())).getData();
    this->client_answers_.clear();

    this->client_answers_.setTestName(this->test_data_.getTestName());
    this->client_answers_.setTestType(this->test_data_.getTestType());

    if (test_data_.getTestType() == "Опросник") {
        this->update_question_questionnaire();

        ui->stackedWidget->setCurrentWidget(ui->page_3);
    } else if (test_data_.getTestType() == "Закончи предложение") {
        this->update_question_complete();

        ui->stackedWidget->setCurrentWidget(ui->page_5);
    }
}


void MainWindow::on_btn_addTest_clicked()
{
    const QString FILE_PATH = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C://",
        "Text Files (*.json) ;;All Files (*.*)"
    );

    const QString TEST_NAME = JsonTestController(FILE_PATH).getData().getTestName();
    if (TEST_NAME != "") {
        JsonMainFileController(this->mainFilePath_).addToJson(FILE_PATH);
        this->update_listWidget();
    }
}


void MainWindow::on_btn_deleteTest_clicked()
{
    ui->listWidget->currentIndex().row();
    QString name = ui->listWidget->currentItem()->text();
    JsonMainFileController(this->mainFilePath_).removePathFromJson(this->tests_paths_.at(name));
    update_listWidget();
}


void MainWindow::on_btn_report_clicked()
{

    this->client_answers_.setClientName(this->report_widget->getName());
    this->client_answers_.setClientSurname(this->report_widget->getSurname());
    this->client_answers_.setClientGroup(this->report_widget->getGroup());

    TestReport report(this->client_answers_, "C:\\Tests_Psychology\\Reports");
    if (!report.createReport()) {
        qDebug() << "Отчет не создан";
    }

    ui->stackedWidget->setCurrentWidget(ui->page);
}


void MainWindow::on_btn_exit_clicked()
{
    this->close();
}


void MainWindow::on_btn_page6_clicked()
{
    this->number_of_question_ = 0;
    ui->stackedWidget->setCurrentWidget(ui->page_6);
}


//void MainWindow::set_question_length(QString str) {

//    if (str.length() > 75) {
//        int counter = 0;
//        QString firstText, secondText;
//        for (QChar i : str) {
//            if (i == ' ') {
//                counter++;
//            }
//            if (counter >= 7) {
//                secondText += i;
//            }
//            else {
//                firstText += i;
//            }
//        }
//        ui->label_qw->setText(firstText + "\n" + secondText);
//    }
//    else {
//        ui->label_qw->setText(str);
//    }
//}
