#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <QPoint>
#include <QImage>

class Platforms
{
public:
    Platforms(const QPoint& position);

    // gets the boundary of platform which is helpful for collisions
    QRect getBoundingRect();
    QImage getImage();

private:
    QRect boundingRect;
    QImage image;
};

#endif // PLATFORMS_H
