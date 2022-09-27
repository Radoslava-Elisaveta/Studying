#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QList>
#include "registerwindow.h"
#include "question.h"
#include "answer.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void ReceiveMessage(QString msg);
     void SetTestFields();
     Answer FindAnswerByText(QString text);
     int FindQuestionGradeByID(int questionID);
     void FillUserAnswers();
     void AddWidgetsToScrollArea();
     QString FindRightAnswer(int questionID);
     QSqlDatabase db;

private slots:
    void on_loginButton_clicked();


    void on_logoutButton_clicked();

    void on_showGradesButton_clicked();

    void on_startTestButton_clicked();

    void on_goToTestButton_clicked();

    void on_goBackButton_clicked();

    void on_endTestButton_clicked();

private:
    Ui::MainWindow *ui;
    RegisterWindow *registerWindow;
    User currentUser;
    QList<Question> questions;
    QList<Answer> answers;
    QList<Answer> userAnswers;
    int userGrade;
    QString category;
    QWidget* container;
    QSqlQueryModel *model;

};
#endif // MAINWINDOW_H
