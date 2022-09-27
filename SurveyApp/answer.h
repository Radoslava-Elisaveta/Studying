#ifndef ANSWER_H
#define ANSWER_H

#include <QString>



class Answer
{
public:
    Answer(int id, int questionID, QString text, bool isRight);
    int Id;
    int QuestionID;
    QString Text;
    bool IsRight;
};

#endif // ANSWER_H
