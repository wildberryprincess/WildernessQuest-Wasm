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
    explicit View(StartPage& startscreen, QWidget *parent = nullptr);

    void setUpInitialGameModel();
    ~View();

signals:
    void setUpModel(int level);

private:
    Ui::View *ui; // Ensure this is declared
    Ui::StartPage *startScreenUI;
    GameWorld *gameWorld;  // Single instance

};

#endif // VIEW_H
