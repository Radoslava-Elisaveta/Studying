#ifndef QUESTION_H
#define QUESTION_H
#include <QString>


class Question
{
public:
    Question(int id, QString text, int grade);
    int Id;
    QString Text;
    int Grade;
};

#endif // QUESTION_H
