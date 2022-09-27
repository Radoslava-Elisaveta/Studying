#include "user.h"
#include <QDebug>
User::User()
{
}

User::~User()
{
    Login.clear();
    Name.clear();
    IsLogined = false;
    School.clear();
    Id = 0;
    Password.clear();
    qDebug()<<"User is empty\n";
}
