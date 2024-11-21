// #ifndef GAMESCENE_H
// #define GAMESCENE_H
// #include <QGraphicsScene>
// #include <QTimer>
// #include <Box2D/Box2D.h>

// class GameScene : public QGraphicsScene {
//     Q_OBJECT

// public:
//     GameScene(QObject *parent = nullptr);
//     ~GameScene();


// protected:
//     void keyPressEvent(QKeyEvent *event) override;
//     void keyReleaseEvent(QKeyEvent *event) override;

// private slots:
//     void update();

// private:
//     void createHero();
//     void createPlatform(float x, float y, float width, float height);

//     QTimer *m_timer;
//     b2World *m_world;
//     b2Body *m_heroBody;


//     std::vector<b2Body *> m_platforms;

//     bool m_leftMove = false;
//     bool m_rightMove = false;
//     bool m_jump = false;

//     const float TIME_STEP = 1.0f / 60.0f; // 60 FPS
//     const int VELOCITY_ITERATIONS = 6;
//     const int POSITION_ITERATIONS = 2;
// };

// #endif // GAMESCENE_H
