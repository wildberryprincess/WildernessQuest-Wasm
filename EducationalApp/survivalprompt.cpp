#include "survivalprompt.h"
#include <QDebug>


SurvivalPrompt::SurvivalPrompt() {}


void SurvivalPrompt:: deserializePrompts(QString filename){
    QFile file(filename);
    QJsonDocument promptDoc;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = file.readAll();
        file.close();
        promptDoc = QJsonDocument::fromJson(jsonData);
    } else {
        qWarning("Error opening file: %s", qPrintable(filename));
    }
    //TODO: Get rid of this to clean up
    qDebug() << "sucessfully opened file!";

    //Access the JSON data
    QJsonObject allPrompts = promptDoc.object();


    QJsonArray levelOneJsonPrompts = allPrompts["levelOne"].toArray();
    deserializeHelper(levelOneJsonPrompts, levelOnePrompts);

    QJsonArray levelTwoJsonPrompts = allPrompts["levelTwo"].toArray();
    deserializeHelper(levelTwoJsonPrompts, levelTwoPrompts);

    QJsonArray levelThreeJsonPrompts = allPrompts["levelThree"].toArray();
    deserializeHelper(levelThreeJsonPrompts, levelThreePrompts);

    QJsonArray levelFourJsonPrompts = allPrompts["levelFour"].toArray();
    deserializeHelper(levelFourJsonPrompts, levelFourPrompts);
}


void SurvivalPrompt:: deserializeHelper(QJsonArray promptArray, vector<Prompt>& levelPromptsArray){
    for(const QJsonValue& promptJsonInfo: promptArray){
        QJsonObject promptInfo = promptJsonInfo.toObject();
        Prompt newPrompt;
        newPrompt.question = promptInfo["question"].toString();

        newPrompt.optionA = promptInfo["optionA"].toString();
        newPrompt.optionB = promptInfo["optionB"].toString();
        newPrompt.optionC = promptInfo["optionC"].toString();
        newPrompt.optionD = promptInfo["optionD"].toString();

        newPrompt.correctAnswer = promptInfo["correctAnswer"].toString();

        levelPromptsArray.push_back(newPrompt);
    }
}

