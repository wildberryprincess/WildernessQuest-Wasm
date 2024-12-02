#ifndef TENT_H
#define TENT_H

#include <QPoint>
#include <QImage>

class Tent
{
public:
    Tent();
    QPoint position;

    QRect getBoundingRect();
    QImage getImage();

private:
    QRect boundingRect;
    QImage image;
};

#endif // TENT_H
