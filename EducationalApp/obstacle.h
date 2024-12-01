#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPoint>
#include <QImage>

class Obstacle
{
public:
    Obstacle(const QPoint& position);
    QPoint position;
    QPoint imageSize;

    QRect getBoundingRect();
    QImage getImage();

private:
    QRect boundingRect;
    QImage image;
};

#endif // OBSTACLE_H
