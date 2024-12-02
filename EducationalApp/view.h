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
    explicit View(StartPage& startscreen, GameModel& gameModel, QWidget *parent = nullptr);

    void setUpInitialGameModel();
    ~View();

signals:
    void setUpModel(int level);
    void updateCharacter(int characterTupe);

private:
    Ui::View *ui; // Ensure this is declared
    StartPage* startScreen;
    // Ui::StartPage *startScreenUI;
    GameWorld *gameWorld;  // Single instance

public slots:
    void displayGame(int characterType);

};

#endif // VIEW_H
