#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <QPoint>
#include <QImage>

    class Platform
{
public:
    Platform(const QPoint& position);

    // gets the boundary of platform which is helpful for collisions
    QRect getBoundingRect();
    void changeImageDimensions(int newWidth, int newHeight);
    QImage getImage();

private:
    QRect boundingRect;
    QImage image;
};

#endif // PLATFORMS_H
