#ifndef HEART_H
#define HEART_H
#include <QPoint>
#include <QImage>

class Heart
{
public:
    Heart(QPoint position);
    QImage getImage();
    QPoint getPosition();

private:
    QImage image;
     QPoint position;
};
#endif // HEART_H
