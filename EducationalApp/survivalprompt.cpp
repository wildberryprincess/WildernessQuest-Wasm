#include "survivalprompt.h"
#include <QDebug>


SurvivalPrompt::SurvivalPrompt(QString filename) {
    deserializePrompts(filename);

}




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
    deserializeHelper(levelThreeJsonPrompts, levelFourPrompts);
}


void SurvivalPrompt:: deserializeHelper(QJsonArray promptArray, vector<Prompt>& levelPromptsArray){
    for(const QJsonValue& promptJsonInfo: promptArray){
        QJsonObject promptInfo = promptJsonInfo.toObject();
        Prompt newPrompt;
        newPrompt.question = promptInfo["question"].toString();
        qDebug() << newPrompt.question;

        newPrompt.optionA = promptInfo["optionA"].toString();
        qDebug() << newPrompt.optionA;
        newPrompt.optionB = promptInfo["optionB"].toString();
        qDebug() << newPrompt.optionB;

        newPrompt.optionC = promptInfo["optionC"].toString();
        qDebug() << newPrompt.optionC;

        newPrompt.optionD = promptInfo["optionD"].toString();
        qDebug() << newPrompt.optionD;


        newPrompt.correctAnswer = promptInfo["correctAnswer"].toString();

        levelPromptsArray.push_back(newPrompt);
    }
}

