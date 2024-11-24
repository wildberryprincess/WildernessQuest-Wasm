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
    levelOnePrompts = deserializeHelper(levelOneJsonPrompts);

    QJsonArray levelTwoJsonPrompts = allPrompts["levelTwo"].toArray();
    levelOnePrompts = deserializeHelper(levelTwoJsonPrompts);

    QJsonArray levelThreeJsonPrompts = allPrompts["levelThree"].toArray();
    levelOnePrompts = deserializeHelper(levelThreeJsonPrompts);

    // int indexCount= 0;

    // for(const QJsonValue& promptJsonInfo: levelOneJsonPrompts){
    //     QJsonObject promptInfo = promptJsonInfo.toObject();
    //     Prompt newPrompt;
    //     newPrompt.question = promptInfo["question"].toString();
    //     qDebug() << newPrompt.question;

    //     newPrompt.optionA = promptInfo["optionA"].toString();
    //     qDebug() << newPrompt.optionA;
    //     newPrompt.optionB = promptInfo["optionB"].toString();
    //     qDebug() << newPrompt.optionB;

    //     newPrompt.optionC = promptInfo["optionC"].toString();
    //     qDebug() << newPrompt.optionC;

    //     newPrompt.optionD = promptInfo["optionD"].toString();
    //     qDebug() << newPrompt.optionD;


    //     newPrompt.correctAnswer = promptInfo["correctAnswer"].toString();

    //     levelOnePrompts[indexCount] = newPrompt;
    //     indexCount++;
    // }
}


SurvivalPrompt::Prompt* SurvivalPrompt:: deserializeHelper(QJsonArray promptArray){
    Prompt promptInfoArray[10];
    int indexCount= 0;

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

        promptInfoArray[indexCount] = newPrompt;
        indexCount++;
    }
    //TODO:: problem here is that 'promptInfoArray' gets destructed once this method is done so nothing gets saved
    return promptInfoArray;
}

