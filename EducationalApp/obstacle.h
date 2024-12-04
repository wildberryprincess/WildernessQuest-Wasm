#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPoint>
#include <QImage>

class Obstacle
{
public:
    Obstacle(const QPoint& position);
    QPoint position;

    QRect getBoundingRect();
    QImage getImage();
    QPoint getPosition();
    bool operator==(const Obstacle& other) const;

private:
    QRect boundingRect;
    QImage image;
};

#endif // OBSTACLE_H
