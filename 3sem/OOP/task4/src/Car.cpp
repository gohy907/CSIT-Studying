#include "raylib.h"
#include <iostream>
#include "raymath.h"
#include "constants.h"

enum typeOfDamage {
    front,
    rear,
    None
};

class Car {
    private:
        Vector2 position;
        Vector2 velocity;
        Vector2 velocity2;
        Vector2 targetVelocity;
        Vector2 acceleration;

        Rectangle texture;
        Rectangle damagedTexture;

        Texture2D atlas;
        float width = CAR_WIDTH;
        float height = CAR_HEIGHT;

        bool damaged = false;
        typeOfDamage damageType = typeOfDamage::None;

        float collisionStartTime = 0;  
        float slowdownStartTime = 0;

        bool isSlowing = false;
        bool isAccelerating = false;

    public:
        Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle texture, Rectangle damagedTexture, Texture2D atlas);
        Car(Vector2 position, Vector2 velocity, Rectangle texture, Rectangle damagedTexture, Texture2D atlas);

        float getWidth();
        float getHeight();

        void setPosition(Vector2 position);
        Vector2 getPosition();
        
        void setVelocity(Vector2 velocity);
        Vector2 getVelocity();
        
        void setAcceleration(Vector2 acceleration);
        Vector2 getAcceleration();

        void update();
        void draw(bool isDamaged);

        bool isDamaged();
        void damage();
        void repair();

        enum typeOfDamage getDamageType();
        void setDamageType(enum typeOfDamage type);

        Vector2 getTargetVelocity();
        void setTargetVelocity(Vector2 velocity);

        void slow();
};

Car::Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle texture, Rectangle damagedTexture, Texture2D atlas) {
    this-> position = position;
    this-> velocity = velocity;
    this->targetVelocity = velocity;
    this->acceleration = acceleration;
    this->texture = texture;
    this->damagedTexture = damagedTexture;
    this->atlas = atlas;
}

Car::Car(Vector2 position, Vector2 velocity, Rectangle texture, Rectangle damagedTexture, Texture2D atlas) {
    this-> position = position;
    this-> velocity = velocity;
    this->targetVelocity = velocity;
    this->acceleration = Vector2{0.0, 0.0};
    this->texture = texture;
    this->damagedTexture = damagedTexture;
    this->atlas = atlas;
}

float Car::getWidth() {
    return width;
}

float Car::getHeight() {
    return height;
}

void Car::setPosition(Vector2 position) {
    this->position = position;
}

Vector2 Car::getPosition() {
    return this->position;
}

void Car::setVelocity(Vector2 velocity){
    this->velocity = velocity;
}

Vector2 Car::getVelocity(){
    return this->velocity;
}

void Car::update() {
    float currentTime = GetTime();
    float dt = GetFrameTime() * 60;


    if (damageType == typeOfDamage::rear && currentTime - collisionStartTime >= PAUSE_DURATION) {
        this->repair();
        damageType = typeOfDamage::None;
    }

    if (slowdownStartTime > 0) {
        float elapsed = currentTime - slowdownStartTime;

        float duration;
        if (isSlowing && !isAccelerating) {
            duration = SLOW_DURATION;
        }
        else {
            duration = ACCELERATION_DURATION;
        }
        if (elapsed < duration) {
            // Линейная интерполяция скорости
            float t = elapsed / duration;  // 0.0 → 1.0
            velocity = Vector2Lerp(velocity2, targetVelocity, t);
            std::cout << velocity.x << std::endl;
        }
        else {
            slowdownStartTime = 0;
            velocity = targetVelocity;
            isAccelerating = false;
        }
    }
    
    if (damaged) {
        return;
    } 
    position = Vector2Add(position, Vector2Scale(velocity, dt));
    velocity = Vector2Add(velocity, Vector2Scale(acceleration, dt));
}

void Car::draw(bool isDamaged){
    Rectangle* texturePointer;
    if (!isDamaged) {
        texturePointer = &texture;
    } else {
        texturePointer = &damagedTexture;
    }

    DrawTexturePro(atlas, *texturePointer, Rectangle{position.x, position.y, width, height}, Vector2{0, 0}, 0, WHITE);
}

bool Car::isDamaged() {
    return damaged;
}

void Car::damage() {
    if (damageType == typeOfDamage::rear) {
        collisionStartTime = GetTime();
    }
    velocity = Vector2(0, 0);
    // velocity2 = velocity;
    velocity2 = Vector2(0, 0);
    isSlowing = false;
    damaged = true;
}

void Car::repair() {
    damageType = typeOfDamage::None;
    slowdownStartTime = GetTime();
    damaged = false;
    isAccelerating = true;
}

Vector2 Car::getAcceleration() {
    return acceleration;
}

void Car::setAcceleration(Vector2 acceleration) {
    this->acceleration = acceleration;
}

enum typeOfDamage Car::getDamageType() {
    return damageType;
}

void Car::setDamageType(enum typeOfDamage type) {
    this->damageType = type;
}

Vector2 Car::getTargetVelocity() {
    return targetVelocity;
}

void Car::setTargetVelocity(Vector2 velocity) {
    targetVelocity = velocity;
}

void Car::slow(){
    velocity2 = velocity;
    slowdownStartTime = GetTime();
    isSlowing = true;
}
