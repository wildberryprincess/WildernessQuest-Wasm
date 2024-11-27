#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QWidget>
#include "platform.h"
#include "maincharacter.h"

class GameWorld : public QWidget {
    Q_OBJECT

public:
    explicit GameWorld(QWidget *parent = nullptr);
};
#endif // GAMEMODEL_H
