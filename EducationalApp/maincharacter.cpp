#include "maincharacter.h"
#include <QWidget>
#define SCALE 30.0f

mainCharacter::mainCharacter(const QPoint& position, b2World* world){
    image = QImage(":/Images/hero.png");
    boundingRect = QRect(position, image.size());

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x() / SCALE, position.y() / SCALE);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((boundingRect.width()/ 2.0f) / SCALE, (boundingRect.height() / 2.0f) / SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.1f;

    body->CreateFixture(&fixtureDef);

}

    // gets the boundary of the character which is helpful for collisions
QRect mainCharacter::getBoundingRect(){
    return boundingRect;
}
QImage mainCharacter::getImage(){
    return image;
}

void mainCharacter::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        moveLeft = true;
        break;
    case Qt::Key_Right:
        moveRight = true;
        break;
    case Qt::Key_Up:
        if (!isJumping) {
            jump();
        }
        break;
    default:
        break;
    }
}

void mainCharacter::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "Inside main character key press released event";
    switch (event->key()) {
    case Qt::Key_Left:
        moveLeft = false;
        break;
    case Qt::Key_Right:
        moveRight = false;
        break;
    case Qt::Key_Up:
        isJumping = false;
        break;
    default:
        break;
    }
}

void mainCharacter::update() {
    b2Vec2 velocity = body->GetLinearVelocity();

    if (moveLeft) {
        velocity.x = -5.0f; // Move left with a fixed speed
    } else if (moveRight) {
        velocity.x = 5.0f; // Move right with a fixed speed
    } else {
        velocity.x = 0.0f; // Stop moving horizontally
    }

    body->SetLinearVelocity(velocity);

    // Update bounding rectangle for rendering
    b2Vec2 position = body->GetPosition();
    boundingRect.moveTo(position.x * SCALE - boundingRect.width() / 2,
                        position.y * SCALE - boundingRect.height() / 2);
}

void mainCharacter::jump() {
    b2Vec2 velocity = body->GetLinearVelocity();

    // Check if the character is grounded by ensuring vertical velocity is near zero
    if (velocity.y == 0.0f) {
        // Apply an impulse at the body's center
        b2Vec2 impulse(0.0f, -40.0f); // Adjust impulse strength as needed
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

        //isJumping = true; // Set jumping flag to true
    }
}




