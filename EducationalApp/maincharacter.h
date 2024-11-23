#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include <QPoint>
#include <QImage>
#include <QString>
#include <Box2D/Box2D.h>
#include <QKeyEvent>
class mainCharacter
{
public:
    mainCharacter(const QPoint& position, b2World* world);

    // gets the boundary of the character which is helpful for collisions
    QRect getBoundingRect();
    QImage getImage();

    void update();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void jump();

private:
    QRect boundingRect;
    QImage image;

    // Flags for key states
    bool moveLeft = false;
    bool moveRight = false;
    bool isJumping = false;

    const float moveSpeed = 5.0f; // Adjust as needed
    b2Body* body;


signals:
    void updateMainCharacterPosition(QString direction,  int position);


};
#endif // MAINCHARACTER_H
