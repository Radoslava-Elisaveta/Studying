#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QCloseEvent>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();
    void SetDataBase(QSqlDatabase parentDB);


signals:
    void SendMessage(QString msg);

private slots:
    void on_loginButton_clicked();

    void on_startRegisterButton_clicked();

    void on_registerButton_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::RegisterWindow *ui;
    QSqlDatabase db;
    void ShowParentWindow();

};

#endif // REGISTERWINDOW_H
