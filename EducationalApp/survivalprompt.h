/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Emilie Parra (.cpp &.h)

The SurvivalPrompt class creates an object that holds all the questions we want to ask in our game.
This class is tasked with organizing the prompts based on level from the json file that this class
will be able to read and deserialize
*/
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


    /**
     * @brief levelOnePrompts holds the prompts available for display for level one
     */
    QVector<Prompt> levelOnePrompts;
    /**
     * @brief levelTwoPrompts holds the prompts available for display for level two
     */
    QVector<Prompt> levelTwoPrompts;
    /**
     * @brief levelThreePrompts holds the prompts available for display for level three
     */
    QVector<Prompt> levelThreePrompts;
    /**
     * @brief levelFourPrompts holds the prompts available for display for level four
     */
    QVector<Prompt> levelFourPrompts;

    /**
     * @brief deserializePrompts : Will take the json filename and deserialize all the prompts saved in it.
     * @param filename : The json file to be read and deserialized
     */
    void deserializePrompts(QString filename);



private:
    /**
     * @brief deserializeHelper : Helper method for the deserializePrompts method that saves json prompt information
     * into saved vectors to access throughout the code
     * @param promptArray : The json array that holds the question, the choices, and the correct answer
     * @param levelPromptsArray : The instance vector that saves 'Prompt' objects
     */
    void deserializeHelper(QJsonArray promptArray, QVector<Prompt>& levelPromptsArray);

};

#endif // SURVIVALPROMPT_H
