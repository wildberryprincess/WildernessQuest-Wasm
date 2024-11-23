#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include <QPoint>
#include <QImage>

class Character
{
public:
    Character(const QPoint& position);

    // gets the boundary of the character which is helpful for collisions
    QRect getBoundingRect();
    QImage getImage();

private:
    QRect boundingRect;
    QImage image;
};
#endif // MAINCHARACTER_H
