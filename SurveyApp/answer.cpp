#include "answer.h"

Answer::Answer(int id, int questionID, QString text, bool isRight)
{
    Id = id;
    QuestionID = questionID;
    Text = text;
    IsRight = isRight;
}
