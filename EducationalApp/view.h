/*
Authors: Andry Joseph (andry-joseph), Emilie Parra (emilie-parra), Eliza Kitchens (wildberryprincess) & Alexis Brown (alexb000)
Assignment #9: Educational Game
Reviewer: Eliza Kitchens (.cpp &.h)

This view class facilitates connections between the model, gameModel, and view, gameWorld.
*/
#ifndef VIEW_H
#define VIEW_H
#include "gamemodel.h"
#include "gameworld.h"
#include "startpage.h"
#include <QMainWindow>

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief View: the game main window
     * @param startscreen: the start screen window
     * @param gameModel: the game model object
     * @param parent: Inherits from QWidget
     */
    explicit View(StartPage& startscreen, GameModel& gameModel, QWidget *parent = nullptr);

    /**
     * @brief setUpInitialGameModel: sends a signal to set up the gameModel
     */
    void setUpInitialGameModel();
    ~View();

private:

    Ui::View *ui;
    StartPage* startScreen;
    GameWorld *gameWorld;

signals:

    /**
     * @brief setUpModel: signal sent to gameWorld display the gameWorld according to the level
     * @param level: game level
     */
    void setUpModel(int level);

    /**
     * @brief updateCharacter: signal sent to gameWorld to display the player's character choice
     * @param characterType: boy scout, non-binary scout, or girl scout
     */
    void updateCharacter(int characterType);

    /**
     * @brief showWinScreen: signal sent to gameWorld to display the game over win screen
     */
    void showWinScreen();

    /**
     * @brief showLoseScreen: signal sent to gameWorld to display the game over lose screen
     */
    void showLoseScreen();


public slots:

    /**
     * @brief displayGame: show game view
     * @param characterType: boy scout, non-binary scout, or girl scout
     */
    void displayGame(int characterType);

    /**
     * @brief displayEndScreen: displays game over screen
     * @param win: win or lose
     */
    void displayEndScreen(bool win);
};
#endif // VIEW_H
