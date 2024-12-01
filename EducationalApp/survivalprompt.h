#ifndef SURVIVALPROMPT_H
#define SURVIVALPROMPT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QVector>



class SurvivalPrompt
{
public:
    SurvivalPrompt();

    /**
     * @brief The Prompt struct holds a single question and its options along with the correct answer
     */
    struct Prompt {
        QString question;

        QString optionA;
        QString optionB;
        QString optionC;
        QString optionD;

        QString correctAnswer;
    };


    QVector<Prompt> levelOnePrompts;
    QVector<Prompt> levelTwoPrompts;
    QVector<Prompt> levelThreePrompts;
    QVector<Prompt> levelFourPrompts;

    void deserializePrompts(QString filename);



private:
    void deserializeHelper(QJsonArray promptArray, QVector<Prompt>& levelPromptsArray);

};

#endif // SURVIVALPROMPT_H
