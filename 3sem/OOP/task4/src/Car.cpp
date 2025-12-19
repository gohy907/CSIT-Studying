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
        Vector2 maxVelocity;
        Vector2 acceleration;

        float targetTime = 0;
        float targetTimeStart = 0;
        
        int reason = 0;

        Rectangle texture;
        Rectangle damagedTexture;

        Texture2D* atlas;
        float width = CAR_WIDTH;
        float height = CAR_HEIGHT;

        bool damaged = false;
        typeOfDamage damageType = typeOfDamage::None;

        float collisionStartTime = 0;  
        float slowdownStartTime = 0;

        bool isSlowing = false;
        bool isAccelerating = false;
        float slowUnnaturalStartTime = 0;
        bool isSlowingUnnatural;
        bool isStalled = false;
        bool checkOnce = true;


    public:
        Car(Vector2 position, Vector2 velocity, Vector2 acceleration,
            Rectangle texture, Rectangle damagedTexture, Texture2D* atlas);
        Car(Vector2 position, Vector2 velocity,
            Rectangle texture, Rectangle damagedTexture, Texture2D* atlas);

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
        void slowUnnatural();
        bool isUnnaturalSlowing();

        Vector2 getMaximumVelocity();

        void accelerate(float time, Vector2 targetVelocity, int reason);
        void slowdown(float time, Vector2 targetVelocity, int reason);
};

Car::Car(Vector2 position, Vector2 velocity, Vector2 acceleration,
         Rectangle texture, Rectangle damagedTexture, Texture2D* atlas)
    : position(position),
      velocity(velocity),
      maxVelocity(velocity),
      acceleration(acceleration),
      texture(texture),
      damagedTexture(damagedTexture),
      atlas(atlas), 
      damaged(false),
      damageType(typeOfDamage::None),
      collisionStartTime(0.0f),
      slowdownStartTime(0.0f),
      isSlowing(false),
      isAccelerating(false),
      slowUnnaturalStartTime(0.0f),
      isSlowingUnnatural(false)
{}

Car::Car(Vector2 position, Vector2 velocity,
         Rectangle texture, Rectangle damagedTexture, Texture2D* atlas)
    : Car(position, velocity, Vector2{0.0f, 0.0f}, texture, damagedTexture, atlas)
{}

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

const float DURATION_OF_UNNATURAL_SLOWDOWN = 1;
const float ELAPSE_OF_UNNATURAL_SLOWDOWN = 1;

void Car::update() {
    float currentTime = GetTime();
    float dt = GetFrameTime();

    if (damageType == typeOfDamage::rear && currentTime - collisionStartTime >= PAUSE_DURATION) {
        damageType = typeOfDamage::None;
        this->repair();
        this->accelerate(ACCELERATION_DURATION, maxVelocity, 2);
    }

    std::cout << "Время сейчас: " << currentTime << " Время начала: " << targetTimeStart << " TargetTime: " << targetTime << "acc: " << acceleration.x << std::endl;
    if ((currentTime - targetTimeStart) >= targetTime) {
        if (reason == 5) {
            isStalled = false;
            reason = 0;
            this->accelerate(ACCELERATION_DURATION, maxVelocity, 2);
        }
        else {
            // std::cout << acceleration.x << std::endl;
            acceleration = Vector2Zeros;
        }

    } else if (reason == 5) {
        isStalled = true;
    }

    if (damaged) {
        return;
    } 

    velocity = Vector2Add(velocity, Vector2Scale(acceleration, dt));
    position = Vector2Add(position, Vector2Scale(velocity, dt));
}

void Car::draw(bool isDamaged){
    const Rectangle* texturePointer;
    if (isDamaged) {
        texturePointer = &damagedTexture;
    } else if (isStalled){
        texturePointer = &STALLED_CAR_SPRITE;
    } else {
        texturePointer = &texture;
    }

    DrawTexturePro(*atlas, *texturePointer, Rectangle{position.x, position.y, width, height}, Vector2{0, 0}, 0, WHITE);
}

bool Car::isDamaged() {
    return damaged;
}

void Car::damage() {
    if (damageType == typeOfDamage::rear) {
        collisionStartTime = GetTime();
    }
    velocity = Vector2Zeros;
    acceleration = Vector2Zeros;
    damaged = true;
}

void Car::repair() {
    velocity = Vector2(1, 0);
    damageType = typeOfDamage::None;
    damaged = false;
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

// Vector2 Car::getTargetVelocity() {
//     return targetVelocity;
// }
//
// void Car::setTargetVelocity(Vector2 velocity) {
//     targetVelocity = velocity;
// }

void Car::slow(){
    slowdownStartTime = GetTime();
    isSlowing = true;
}

void Car::slowUnnatural() {
    if (isSlowingUnnatural && isAccelerating) {
        return;
    }
    // std::cout << "Начало: " << velocity.x << std::endl;
    checkOnce = true;
    isStalled = true;
    slowUnnaturalStartTime = GetTime();
    isSlowingUnnatural = true;
}

bool Car::isUnnaturalSlowing() {
    return isSlowingUnnatural;
}

Vector2 Car::getMaximumVelocity() {
    return maxVelocity;
}

void Car::accelerate(float time, Vector2 targetVelocity, int reason) {
    if (damaged || this->reason == reason) {
        return;
    }
    std::cout << reason << std::endl;
    this->reason = reason;

    Vector2 targetAcceleration = Vector2Subtract(targetVelocity, velocity)/time;
    std::cout << "Ускорение: " << targetAcceleration.x << std::endl;
    targetTimeStart = GetTime();
    targetTime = time;
    acceleration = targetAcceleration;
}


void Car::slowdown(float time, Vector2 targetVelocity, int reason) {
    // std::cout << this->reason;
    if (damaged || this->reason == reason) {
        return;
    }

    // std::cout << "ABOBA";
    this->reason = reason;
    Vector2 targetAcceleration = Vector2Subtract(targetVelocity, velocity)/time;
    // std::cout << "avadasdsa";
    targetTimeStart = GetTime();
    targetTime = time;
    acceleration = targetAcceleration;
}

