#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>


RegisterWindow::RegisterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->registerGroupBox->setVisible(false);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::SetDataBase(QSqlDatabase parentDB)
{
    db = parentDB;
}

void RegisterWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Реєстрація",
                                             tr("Ви впевнені?\n"),
                                             QMessageBox::No | QMessageBox::Yes,
                                             QMessageBox::Yes);

        if (resBtn != QMessageBox::Yes)
        {
            //event ignored
            event->ignore();
        }
        else
        {
            ShowParentWindow();
        }
}

void RegisterWindow::on_loginButton_clicked()
{
    if(ui->loginLineEdit->text().isEmpty()||ui->loginpasswordLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","Заповніть, будь ласка, усі поля для входу в систему");
    }
    else
    {
        QSqlQuery query(QSqlDatabase::database());
        if(query.exec("SELECT id FROM User_ where login_='"+ui->loginLineEdit->text()+"' and password_ = '"+ui->loginpasswordLineEdit->text()+"'"))
        {
            int id;
            int count = 0;
            while(query.next())
            {
                count++;
                id = query.value(0).toInt();
            }
            if(count == 1)
            {
                QMessageBox::information(this,"Вхід в систему","Ви успішно зайшли в систему!");
                SendMessage(QString::number(id));
                ShowParentWindow();
            }
            if(count > 1)
            {
                QMessageBox::information(this,"Warning","Duplicate name and password");
            }
            if(count < 1)
            {
                QMessageBox::information(this,"Помилка","Логін чи пароль не правильні");
            }
        }
        else
        {
            QMessageBox::critical(this,"Дурня якась",query.lastError().text());
        }
    }
}


void RegisterWindow::on_startRegisterButton_clicked()
{
    ui->registerGroupBox->setVisible(true);
    ui->label_7->setVisible(false);
    ui->startRegisterButton->setVisible(false);
}


void RegisterWindow::on_registerButton_clicked()
{
    if(ui->regLoginLineEdit->text().isEmpty()||ui->regNameLineEdit->text().isEmpty()
            ||ui->regPasswordLineEdit->text().isEmpty()||ui->regUniverLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","Заповніть, будь ласка, усі поля реєстрації");
    }
    else
    {
        QSqlQuery query(QSqlDatabase::database());
        if(query.exec("SELECT id,name_,login_,password_,school FROM User_ where login_='"+ui->regLoginLineEdit->text()+"'"))
        {
            int count = 0;
            while(query.next())
            {
                count++;
            }
            if(count >= 1)
            {
                QMessageBox::warning(this,"Помилка","Користувач із таким логін вже існує");
            }
            if(count < 1)
            {
                query.prepare("INSERT INTO User_(name_,login_,password_,school) VALUES (:name,:login,:password,:school)");
                query.bindValue(":name",ui->regNameLineEdit->text());
                query.bindValue(":login",ui->regLoginLineEdit->text());
                query.bindValue(":password",ui->regPasswordLineEdit->text());
                query.bindValue(":school",ui->regUniverLineEdit->text());
                if(!query.exec())
                {
                    QMessageBox::critical(this,"ERROR",query.lastError().text());
                }
                else
                {
                    QMessageBox::information(this,"Реєстрація","Вітаємо, вас зареєстровано.Увійдіть у свій акаунт");
                    ui->registerGroupBox->setVisible(false);
                }
            }
        }
        else
        {
            QMessageBox::critical(this,"ERROR",query.lastError().text());
        }
    }
}

void RegisterWindow::ShowParentWindow()
{
    QObject *p = this;
    do
    {
       p = p->parent();
    } while (p->parent() != NULL);

    QMainWindow *mw = qobject_cast<QMainWindow *>(p);
    if (!mw)
    {
       QMessageBox::critical(this, "ERROR","Can`t find parent window");
    }
    else
    {
       mw->show();
       hide();
    }
    db.~QSqlDatabase();
}
