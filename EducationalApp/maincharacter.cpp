#include "maincharacter.h"
#include "gamecontactlistener.h"
#include <QWidget>
#define SCALE 30.0f

mainCharacter::mainCharacter(const QPoint& position, b2World* world, GameContactListener* contactListener)
    : contactListener(contactListener)
{
    image = QImage(":/Images/girlScout.png");
    image = image.scaled(70, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    boundingRect = QRect(position, image.size());

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x() / SCALE, position.y() / SCALE);
    body = world->CreateBody(&bodyDef);
    body->SetUserData(this); // Set user data to identify the player for contact collision

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox((boundingRect.width()/ 2.0f) / SCALE, (boundingRect.height() / 2.0f) / SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1;
    fixtureDef.restitution = 0.0f;

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

    float verticalVelocity = velocity.y;

    if (moveLeft) {
        velocity.x = -5.0f; // Move left with a fixed speed
    } else if (moveRight) {
        velocity.x = 5.0f; // Move right with a fixed speed
    } else {
        velocity.x = 0.0f; // Stop moving horizontally
    }

    // Set the horizontal velocity, leave vertical velocity as is
    body->SetLinearVelocity(b2Vec2(velocity.x, verticalVelocity));

    // Update bounding rectangle for rendering
    b2Vec2 position = body->GetPosition();
    boundingRect.moveTo(position.x * SCALE - boundingRect.width() / 2,
                        position.y * SCALE - boundingRect.height() / 4);
}


void mainCharacter::jump() {
    if (contactListener->isGrounded) {
        b2Vec2 impulse(0.0f, -50.0f); // Adjust impulse strength as needed
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
        isJumping = true;
    }
}

b2Body* mainCharacter::getBody() {
    return body;
}





