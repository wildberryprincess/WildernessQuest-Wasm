#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

class SceneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SceneWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;

protected:
    // void keyPressEvent(QKeyEvent *event) override;
    // void keyReleaseEvent(QKeyEvent *event) override;


signals:

public slots:
    void updateWorld();

private:
    void createHero();
    void createPlatform(float x, float y, float width, float height);

    b2World world;
    b2Body* heroBody;
    QTimer timer;
    QImage image;

    std::vector<b2Body *> m_platforms;

    bool m_leftMove = false;
    bool m_rightMove = false;
    bool m_jump = false;

    const float TIME_STEP = 1.0f / 60.0f; // 60 FPS
    const int VELOCITY_ITERATIONS = 6;
    const int POSITION_ITERATIONS = 2;
};

#endif // SCENEWIDGET_H
