#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    ~User();
    int Id;
    QString Login;
    QString Password;
    QString Name;
    QString School;
    bool IsLogined = false;
};

#endif // USER_H
