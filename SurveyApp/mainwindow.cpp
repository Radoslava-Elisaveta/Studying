#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMessageBox>
#include "Random.h"
#include <QDebug>
#include <QElapsedTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    userGrade =0;

    //connecting database
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL SERVER};SERVER=WIN-98Q00G2SBAK;DATABASE=SurveyApp;UID=User;PWD=;Trusted_Connection=Yes");
    if(!db.open())
    {
        QMessageBox::critical(this,"ERROR",db.lastError().text());
    }

    //statusbar
    ui->statusbar->addPermanentWidget(ui->userLoginLabel,1);

    //objects default visibility
    ui->loginButton->setVisible(false);
    ui->logoutButton->setVisible(false);
    ui->categoryLabel->setVisible(false);
    ui->mathRadioButton->setVisible(false);
    ui->languageRadioButton->setVisible(false);
    ui->curiosityRadioButton->setVisible(false);
    ui->randomRadioButton->setVisible(false);
    ui->showGradesButton->setVisible(false);
    ui->startTestButton->setVisible(false);
    ui->userInfoLabel->setVisible(false);
    ui->goToTestButton->setVisible(false);
    ui->gradesTableView->setVisible(false);
    ui->messageLabel->setVisible(false);
    ui->testScrollArea->setVisible(false);
    ui->endTestButton->setVisible(false);
    ui->goBackButton->setVisible(false);
    ui->resultLabel->setVisible(false);
    ui->resultScrollArea->setVisible(false);
    ui->greetingLabel->setVisible(false);

    //showing category choice widgets and login button
    QTimer::singleShot(3000,ui->loginButton,&QLabel::show);
    QTimer::singleShot(3000,ui->categoryLabel,&QLabel::show);
    QTimer::singleShot(3000,ui->mathRadioButton,&QLabel::show);
    QTimer::singleShot(3000,ui->languageRadioButton,&QLabel::show);
    QTimer::singleShot(3000,ui->curiosityRadioButton,&QLabel::show);
    QTimer::singleShot(3000,ui->randomRadioButton,&QLabel::show);
    QTimer::singleShot(3000,ui->startTestButton,&QLabel::show);

    //Progtram name effect
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    ui->startLabel->setGraphicsEffect(effect);
    QPropertyAnimation *anim = new QPropertyAnimation(effect,"opacity");
    anim->setDuration(3000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    hide();
    registerWindow = new RegisterWindow(this);
    registerWindow->SetDataBase(db);
    connect(registerWindow,&RegisterWindow::SendMessage,this,&MainWindow::ReceiveMessage);
    registerWindow->show();
}

void MainWindow::ReceiveMessage(QString msg)
{
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT id,name_,login_,password_,school FROM User_ where id= :id");
    query.bindValue(":id",msg.toInt());
    if(query.exec())
    {
        int count = 0;
        while(query.next())
        {
            count++;
            currentUser.Id = query.value(0).toInt();
            currentUser.Name = query.value(1).toString();
            currentUser.Login = query.value(2).toString();
            currentUser.Password = query.value(3).toString();
            currentUser.School = query.value(4).toString();
            currentUser.IsLogined = true;
        }
        if(count > 1)
        {
            QMessageBox::information(this,"Warning","Duplicate name and password");
        }
    }
    else
    {
        QMessageBox::critical(this,"ERROR",query.lastError().text());
    }
    ui->userLoginLabel->setText(currentUser.Login);
    ui->loginButton->setVisible(false);
    ui->logoutButton->setVisible(true);
    ui->showGradesButton->setVisible(true);
}

void MainWindow::SetTestFields()
{
    //setting questions text to labels
    ui->question_1Label->setText(questions[0].Text);
    ui->question_2Label->setText(questions[1].Text);
    ui->question_3Label->setText(questions[2].Text);
    ui->question_4Label->setText(questions[3].Text);
    ui->question_5Label->setText(questions[4].Text);
    ui->question_6Label->setText(questions[5].Text);
    ui->question_7Label->setText(questions[6].Text);

    //setting answers to comboboxes
    ui->question_1ComboBox->addItem(answers[0].Text);
    ui->question_1ComboBox->addItem(answers[1].Text);
    ui->question_1ComboBox->addItem(answers[2].Text);
    ui->question_1ComboBox->addItem(answers[3].Text);
    //secondQuestion
    ui->question_2ComboBox->addItem(answers[4].Text);
    ui->question_2ComboBox->addItem(answers[5].Text);
    ui->question_2ComboBox->addItem(answers[6].Text);
    ui->question_2ComboBox->addItem(answers[7].Text);
    //third question
    ui->question_3ComboBox->addItem(answers[8].Text);
    ui->question_3ComboBox->addItem(answers[9].Text);
    ui->question_3ComboBox->addItem(answers[10].Text);
    ui->question_3ComboBox->addItem(answers[11].Text);
    //fourth question
    ui->question_4ComboBox->addItem(answers[12].Text);
    ui->question_4ComboBox->addItem(answers[13].Text);
    ui->question_4ComboBox->addItem(answers[14].Text);
    ui->question_4ComboBox->addItem(answers[15].Text);
    //fifth question
    ui->question_5ComboBox->addItem(answers[16].Text);
    ui->question_5ComboBox->addItem(answers[17].Text);
    ui->question_5ComboBox->addItem(answers[18].Text);
    ui->question_5ComboBox->addItem(answers[19].Text);
    //sixth question
    ui->question_6ComboBox->addItem(answers[20].Text);
    ui->question_6ComboBox->addItem(answers[21].Text);
    ui->question_6ComboBox->addItem(answers[22].Text);
    ui->question_6ComboBox->addItem(answers[23].Text);
    //seveth question
    ui->question_7ComboBox->addItem(answers[24].Text);
    ui->question_7ComboBox->addItem(answers[25].Text);
    ui->question_7ComboBox->addItem(answers[26].Text);
    ui->question_7ComboBox->addItem(answers[27].Text);
}

Answer MainWindow::FindAnswerByText(QString text)
{
    for(int i =0; i<answers.size();i++)
    {
        if(answers[i].Text == text)
        {
            return answers[i];
        }
    }
    QMessageBox::critical(this,"ERROR","Can`t find answer with this text");
}

int MainWindow::FindQuestionGradeByID(int questionID)
{
    for(int i =0; i<questions.size();i++)
    {
        if(questions[i].Id==questionID)
        {
            return questions[i].Grade;
        }
    }
    QMessageBox::critical(this,"ERROR","Can`t find question with this id");
    return -1;
}

void MainWindow::FillUserAnswers()
{
    userAnswers.push_back(FindAnswerByText(ui->question_1ComboBox->currentText()));
    userAnswers.push_back(FindAnswerByText(ui->question_2ComboBox->currentText()));
    userAnswers.push_back(FindAnswerByText(ui->question_3ComboBox->currentText()));
    userAnswers.push_back(FindAnswerByText(ui->question_4ComboBox->currentText()));
    userAnswers.push_back(FindAnswerByText(ui->question_5ComboBox->currentText()));
    userAnswers.push_back(FindAnswerByText(ui->question_6ComboBox->currentText()));
    userAnswers.push_back(FindAnswerByText(ui->question_7ComboBox->currentText()));
}

void MainWindow::AddWidgetsToScrollArea()
{
//    QWidget* container = new QWidget(this);
//    QVBoxLayout *myLayout = new QVBoxLayout;


//    for(int i =0; i < 12;i++)
//    {
//        QLabel* label = new QLabel(this);
//        label->setMinimumHeight(70);
//        label->setText(QString::number(i));

//        if(i%2 == 0)
//        {
//            label->setStyleSheet("QLabel { background-color: rgb(255, 184, 160); font: 12pt Comic Sans MS}");
//        }
//        else
//        {
//            label->setStyleSheet("QLabel { background-color: rgb(207, 255, 192); font: 12pt Comic Sans MS}");
//        }
//        myLayout->addWidget(label);
//    }
//    container->setLayout(myLayout);
//    ui->scrollArea->setWidget(container);
//    ui->scrollArea->setWidgetResizable(true);
        container = new QWidget(this);
        QVBoxLayout *myLayout = new QVBoxLayout;
        for(int i =0; i <userAnswers.size();i++)
        {
            QString text = questions[i].Text+"\nВаша відповідь:\n"+userAnswers[i].Text;
            QLabel* label = new QLabel(this);
            label->setMinimumHeight(70);
            if(userAnswers[i].IsRight)
            {
                text+="\nВаша відповідь правильна";
                label->setText(text);
                label->setStyleSheet("QLabel { background-color: rgb(207, 255, 192); font: 8pt Comic Sans MS}");
            }
            else
            {
                text+="\nПравильна відповідь: "+ FindRightAnswer(questions[i].Id);
                label->setText(text);
                label->setStyleSheet("QLabel { background-color: rgb(255, 184, 160); font: 8pt Comic Sans MS}");
            }
            myLayout->addWidget(label);
        }
        container->setLayout(myLayout);
        ui->resultScrollArea->setWidget(container);
        ui->resultScrollArea->setWidgetResizable(true);
}

QString MainWindow::FindRightAnswer(int questionID)
{
    for(int i =0;i<answers.size();i++)
    {
        if(answers[i].QuestionID==questionID && answers[i].IsRight)
        {
            return answers[i].Text;
        }
    }
    return "ERROR with finding right answer";
}

void MainWindow::on_logoutButton_clicked()
{
    ui->userLoginLabel->setText(" ");
    ui->logoutButton->setVisible(false);
    ui->loginButton->setVisible(true);
    ui->showGradesButton->setVisible(false);
    ui->userInfoLabel->setVisible(false);
    ui->categoryLabel->setVisible(true);
    ui->layoutWidget->setVisible(true);
    ui->mathRadioButton->setVisible(true);
    ui->languageRadioButton->setVisible(true);
    ui->curiosityRadioButton->setVisible(true);
    ui->randomRadioButton->setVisible(true);
    ui->startTestButton->setVisible(true);
    ui->goToTestButton->setVisible(false);
    ui->gradesTableView->setVisible(false);
    ui->messageLabel->setVisible(false);
    model->clear();
    currentUser.~User();
}

void MainWindow::on_showGradesButton_clicked()
{
    ui->categoryLabel->setVisible(false);
    ui->layoutWidget->setVisible(false);
    ui->showGradesButton->setVisible(false);
    ui->startTestButton->setVisible(false);
    ui->goBackButton->setVisible(false);
    ui->resultLabel->setVisible(false);
    ui->resultScrollArea->setVisible(false);
    ui->greetingLabel->setVisible(false);
    ui->userInfoLabel->setVisible(true);
    ui->goToTestButton->setVisible(true);
    ui->gradesTableView->setVisible(true);
    ui->logoutButton->setVisible(true);
    if(userGrade>0)
    {
        userGrade = 0;
    }

    QString userInfo = "Ім'я: "+currentUser.Name+"\nМісце навчання: "+currentUser.School;
    ui->userInfoLabel->setText(userInfo);
    model = new QSqlQueryModel();
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT grade,category,date_ FROM Grade WHERE userID= :id");
    query.bindValue(":id",currentUser.Id);
    if(query.exec())
    {
        int count =0;
        while(query.next())
        {
            count++;
        }

        if(count >=1)
        {
            model->setQuery(query);
            ui->gradesTableView->setModel(model);
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("Оцінка"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Категорія тесту"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Дата проходження"));
            ui->gradesTableView->horizontalHeader()->resizeSection(0,134);
            ui->gradesTableView->horizontalHeader()->resizeSection(1,250);
            ui->gradesTableView->horizontalHeader()->resizeSection(2,267);
            ui->gradesTableView->horizontalHeader()->setStyleSheet("QHeaderView {font: 12pt Comic Sans MS}");
            ui->gradesTableView->verticalHeader()->setStyleSheet("QHeaderView {font: 12pt Comic Sans MS}");
            ui->gradesTableView->show();
        }
        if(count < 1)
        {
            ui->messageLabel->setVisible(true);
        }

    }
    else
    {
        QMessageBox::critical(this,"ERROR",query.lastError().text());
    }
}


void MainWindow::on_startTestButton_clicked()
{
    if(!ui->mathRadioButton->isChecked() && !ui->curiosityRadioButton->isChecked() && !ui->languageRadioButton->isChecked() && !ui->randomRadioButton->isChecked())
    {
        QMessageBox::information(this, "УВАГА", "Оберіть одну з категорій для тестування");
    }
    else
    {
        category = "";
        if(!currentUser.IsLogined)
        {
            QMessageBox::information(this, "УВАГА", "Увійдіть,будь ласка, в систему для початку тестування");
        }
        else
        {
            if(ui->mathRadioButton->isChecked())
            {
                category = "математика";
            }
            else if(ui->languageRadioButton->isChecked())
            {
                category = "українська мова";
            }
            else if(ui->curiosityRadioButton->isChecked())
            {
                category = "цікавинки";
            }
            else if(ui->randomRadioButton->isChecked())
            {
                int choice =Random::get(1,3);
                switch (choice)
                {
                case 1:
                    category = "математика";
                    break;
                case 2:
                    category = "українська мова";
                case 3:
                    category = "цікавинки";
                default:
                    break;
                }
            }
            else
            {
                QMessageBox::critical(this,"ERROR","Something went wrong with radiButtons");
            }
            qDebug()<<"\ncategory: "<<category;

            //selecting from questions from database
            QSqlQuery query(QSqlDatabase::database());
            query.prepare("SELECT id, text_, grade FROM Question WHERE category = :category");
            query.bindValue(":category",category);

            if(query.exec())
            {
                int count = 0;
                while (query.next())
                {
                    count++;
                    int id = query.value(0).toInt();
                    QString text = query.value(1).toString();
                    int grade = query.value(2).toInt();
                    questions.push_back(Question(id,text,grade));

                }
                if(count <1)
                {
                    QMessageBox::critical(this,"ERROR","No question with this category");
                }

            }
            else
            {
                QMessageBox::critical(this,"ERROR",query.lastError().text());
            }
//            for(auto iter = questions.begin();iter<questions.end();iter++)
//            {
//                qDebug()<<"\nID: "<<(*iter).Id<<"\nQuestion: "<<(*iter).Text<<"\nGrade: "<<(*iter).Grade;
//            }



            //geting answers from database
            QSqlQuery queryAnswers(QSqlDatabase::database());
            queryAnswers.prepare("SELECT * FROM Answer WHERE questionID = :id");

            for(int i =0; i<questions.size();i++)
            {
                queryAnswers.bindValue(":id",questions[i].Id);

                if(queryAnswers.exec())
                {
                    int count =0;
                    while(queryAnswers.next())
                    {
                        int id = queryAnswers.value(0).toInt();
                        int questionID = queryAnswers.value(1).toInt();
                        QString text = queryAnswers.value(2).toString();
                        bool isRight = queryAnswers.value(3).toBool();
                        answers.push_back(Answer(id,questionID,text,isRight));
                        count++;
                    }
                    if(count <1)
                    {
                        QMessageBox::critical(this,"ERROR","No answer to question with this id");
                    }
                }
                else
                {
                    QMessageBox::critical(this,"ERROR", queryAnswers.lastError().text());
                }
            }
//            for(int i =0; i<answers.size();i++)
//            {

//                    qDebug()<<"\nID: "<<answers[i].Id<<"\nQuestionID: "<<answers[i].QuestionID<<"\nText: "<<answers[i].Text<<"\nisRight "<<answers[i].IsRight;

//            }


            SetTestFields();
            //set visibility
            ui->categoryLabel->setVisible(false);
            ui->mathRadioButton->setVisible(false);
            ui->languageRadioButton->setVisible(false);
            ui->curiosityRadioButton->setVisible(false);
            ui->randomRadioButton->setVisible(false);
            ui->showGradesButton->setVisible(false);
            ui->startTestButton->setVisible(false);
            ui->logoutButton->setVisible(false);
            //ui->gradesTableView->setVisible(false);
            ui->layoutWidget->setVisible(false);
            ui->endTestButton->setVisible(true);
            ui->testScrollArea->setVisible(true);
            ui->goBackButton->setVisible(true);

        }
    }
}


void MainWindow::on_goToTestButton_clicked()
{
    ui->userInfoLabel->setVisible(false);
    ui->goToTestButton->setVisible(false);
    ui->gradesTableView->setVisible(false);
    ui->messageLabel->setVisible(false);
    ui->categoryLabel->setVisible(true);
    ui->layoutWidget->setVisible(true);
    ui->startTestButton->setVisible(true);
    ui->mathRadioButton->setVisible(true);
    ui->languageRadioButton->setVisible(true);
    ui->curiosityRadioButton->setVisible(true);
    ui->randomRadioButton->setVisible(true);
    ui->showGradesButton->setVisible(true);
    if(!answers.isEmpty())
    {
        answers.clear();
    }
    if(!questions.isEmpty())
    {
        questions.clear();
    }
    if(!userAnswers.isEmpty())
    {
        userAnswers.clear();
    }
    if(ui->resultLabel->isVisible())
    {
        ui->resultLabel->setVisible(false);
        ui->resultScrollArea->setVisible(false);
        ui->greetingLabel->setVisible(false);
        container->deleteLater();
    }
    else if(ui->testScrollArea->isVisible())
    {
        ui->testScrollArea->setVisible(false);
        ui->endTestButton->setVisible(false);
        ui->goBackButton->setVisible(false);
    }
    if(userGrade>0)
    {
        userGrade = 0;
    }

}


void MainWindow::on_goBackButton_clicked()
{
    ui->categoryLabel->setVisible(true);
    ui->layoutWidget->setVisible(true);
    ui->mathRadioButton->setVisible(true);
    ui->languageRadioButton->setVisible(true);
    ui->curiosityRadioButton->setVisible(true);
    ui->randomRadioButton->setVisible(true);
    ui->showGradesButton->setVisible(true);
    ui->startTestButton->setVisible(true);
    ui->logoutButton->setVisible(true);
    ui->question_1ComboBox->clear();
    ui->question_2ComboBox->clear();
    ui->question_3ComboBox->clear();
    ui->question_4ComboBox->clear();
    ui->question_5ComboBox->clear();
    ui->question_6ComboBox->clear();
    ui->question_7ComboBox->clear();
    ui->question_1Label->clear();
    ui->question_2Label->clear();
    ui->question_3Label->clear();
    ui->question_4Label->clear();
    ui->question_5Label->clear();
    ui->question_6Label->clear();
    ui->question_7Label->clear();
    if(!answers.isEmpty())
    {
        answers.clear();
    }
    if(!questions.isEmpty())
    {
        questions.clear();
    }
    if(!userAnswers.isEmpty())
    {
        userAnswers.clear();
    }
    if(ui->resultLabel->isVisible())
    {
        ui->resultLabel->setVisible(false);
        ui->resultScrollArea->setVisible(false);
        ui->greetingLabel->setVisible(false);
        container->deleteLater();
    }
    else if(ui->testScrollArea->isVisible())
    {
        ui->testScrollArea->setVisible(false);
        ui->endTestButton->setVisible(false);
        ui->goBackButton->setVisible(false);
    }
    if(userGrade>0)
    {
        userGrade = 0;
    }
}


void MainWindow::on_endTestButton_clicked()
{
    QDateTime testDateTime = QDateTime::currentDateTime();
    //get user answers
    FillUserAnswers();
    for(int i =0; i<userAnswers.size();i++)
    {

        qDebug()<<"\nID: "<<userAnswers[i].Id<<"\nQuestionID: "<<userAnswers[i].QuestionID<<"\nText: "<<userAnswers[i].Text<<"\nisRight "<<userAnswers[i].IsRight;

    }

    //count user`s grade
    for(int i =0; i<userAnswers.size();i++)
    {
        if(userAnswers[i].IsRight)
        {
            userGrade+=FindQuestionGradeByID(userAnswers[i].QuestionID);
        }
    }
    qDebug()<<"\nFinal user grade: "<<userGrade;

    //write to database user`s grade
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Grade VALUES (:userID, :grade, :category, :date)");
    query.bindValue(":userID",currentUser.Id);
    query.bindValue(":grade",userGrade);
    query.bindValue(":category",category);
    query.bindValue(":date",testDateTime);
    if(!query.exec())
    {
        QMessageBox::critical(this,"ERROR",query.lastError().text());
    }

    //display user`s grade
    if(category == "математика")
    {
        QString text = QString::number(userGrade)+"/11";
        ui->greetingLabel->setText("Вітаємо!");
        ui->resultLabel->setText(text);
    }
    else if(category == "українська мова")
    {
        QString text = QString::number(userGrade)+"/17";
        ui->greetingLabel->setText("Вітаємо!");
        ui->resultLabel->setText(text);
    }
    else if(category == "цікавинки")
    {
        QString text = QString::number(userGrade)+"/14";
        ui->greetingLabel->setText("Це база!");
        ui->resultLabel->setText(text);
    }

    //display user`s answers
    AddWidgetsToScrollArea();
    //set visibility

    ui->testScrollArea->setVisible(false);
    ui->endTestButton->setVisible(false);
    ui->showGradesButton->setVisible(true);
    ui->resultLabel->setVisible(true);
    ui->greetingLabel->setVisible(true);
    ui->resultScrollArea->setVisible(true);

}

