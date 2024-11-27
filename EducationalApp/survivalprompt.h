#ifndef SURVIVALPROMPT_H
#define SURVIVALPROMPT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

using std:: vector;

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


    vector<Prompt> levelOnePrompts;
    vector<Prompt> levelTwoPrompts;
    vector<Prompt> levelThreePrompts;
    vector<Prompt> levelFourPrompts;

    void deserializePrompts(QString filename);



private:
    void deserializeHelper(QJsonArray promptArray, vector<Prompt>& levelPromptsArray);

};

#endif // SURVIVALPROMPT_H
