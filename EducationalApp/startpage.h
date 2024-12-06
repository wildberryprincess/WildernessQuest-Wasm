/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Andry Joseph (.cpp &.h)


This file is the setup of the start screen UI. This is where all the buttons to choose a scout character, read the instructions
and start the game. This UI also acts as the end screen that is dispalyed when either the player wins of loses the game.
*/

#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();

protected:
    /**
     * @brief paintEvent: Handles custom drawing of the background on the screen.
     * @param event: The paint event
     */
    void paintEvent(QPaintEvent *event) override;

signals:
    /**
     * @brief updateCharacterInfo: The signal that sends the info of which scout the player has chosen to play with
     * @param characterType: 0 is girl scout, 1 is boy scout, 2 is non-binary scout
     */
    void updateCharacterInfo(int characterType);

public slots:

    /**
     * @brief on_startButton_clicked: The slot that is called when the start button is clicked to start the game.
     */
    void on_startButton_clicked();

    /**
     * @brief on_girlScoutButton_clicked: The slot that is called when the girl scout button is clicked setting the
     *        character to girl scout.
     */
    void on_girlScoutButton_clicked();

    /**
     * @brief on_boyScoutButton_clicked: The slot that is called when the boy scout button is clicked setting the
     *        character to boy scout.
     */
    void on_boyScoutButton_clicked();

    /**
     * @brief on_instructionsButton_clicked: The slot that is called when the instructions button is clicked displaying
     *        the instructions of the game.
     */
    void on_instructionsButton_clicked();

    /**
     * @brief on_nonBinaryScoutButton_clicked: The slot that is called when the non-binary scout button is clicked setting
     *        the character to non-binary scout.
     */
    void on_nonBinaryScoutButton_clicked();

    /**
     * @brief updateWinScreen: The slot that is called when the player wins the game to display the win screen.
     */
    void updateWinScreen();

    /**
     * @brief updateLoseScreen: The slot that is called when the player loses the game to display the lose screen.
     */
    void updateLoseScreen();

private:
    Ui::StartPage *ui;

    QLabel* instructionsLabel;
    QPixmap uiBackground;
    QLabel* boyScoutLabel;
    QLabel* girlScoutLabel;
    QLabel* nonBinaryScoutLabel;

    /**
     * @brief setBackground: This method sets the background of the start screen and end screen.
     * @param imagePath: The image path
     */
    void setBackground(const QString &imagePath);
};

#endif // STARTPAGE_H
