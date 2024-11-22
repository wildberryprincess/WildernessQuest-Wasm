#include "survivalprompt.h"

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
    //Access the JSON data
    QJsonObject promptsData = promptDoc.object();
}
