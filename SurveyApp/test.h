#ifndef TEST_H
#define TEST_H
#include <QString>


class Test
{
public:
    Test(QString question, QString answer, int grade );
    QString Question;
    QString Answer;
    int Grade;
};

#endif // TEST_H
