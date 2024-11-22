#ifndef SURVIVALPROMPT_H
#define SURVIVALPROMPT_H

#include <QObject>
#include <map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

using std:: map;

class SurvivalPrompt
{
public:
    SurvivalPrompt(QString filename);

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


    map<QString, QString[4]> levelOnePrompts;
    map<QString, QString[4]> levelTwoPrompts;
    map<QString, QString[4]> levelThreePrompts;

private:
    void deserializePrompts(QString filename);

};

#endif // SURVIVALPROMPT_H
