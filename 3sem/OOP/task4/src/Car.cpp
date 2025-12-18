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
};

Car::Car(Vector2 position, Vector2 velocity, Vector2 acceleration,
         Rectangle texture, Rectangle damagedTexture, Texture2D* atlas)
    : position(position),
      velocity(velocity),
      velocity2(Vector2{0, 0}),
      targetVelocity(velocity),
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
        }
        else {
            slowdownStartTime = 0;
            velocity = targetVelocity;
            isAccelerating = false;
        }
    }
    if (isSlowingUnnatural && !damaged) {
        float elapsed = currentTime - slowUnnaturalStartTime;
        std::cout << elapsed << std::endl;
        if (elapsed < DURATION_OF_UNNATURAL_SLOWDOWN) {
            float t = elapsed / DURATION_OF_UNNATURAL_SLOWDOWN;  // 0.0 → 1.0
            velocity = Vector2Lerp(velocity2, targetVelocity, t);
        } else if (checkOnce && elapsed < DURATION_OF_UNNATURAL_SLOWDOWN + ELAPSE_OF_UNNATURAL_SLOWDOWN) {
            checkOnce = false;
            velocity = targetVelocity;
            targetVelocity = velocity2;
            velocity2 = velocity;
        } else if (elapsed < 2 * DURATION_OF_UNNATURAL_SLOWDOWN + ELAPSE_OF_UNNATURAL_SLOWDOWN) {
            float t = elapsed / DURATION_OF_UNNATURAL_SLOWDOWN - 1;  // 0.0 → 1.0
            velocity = Vector2Lerp(velocity2, targetVelocity, t);
        } else {
            velocity = targetVelocity;
            isSlowingUnnatural = false;
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

    DrawTexturePro(*atlas, *texturePointer, Rectangle{position.x, position.y, width, height}, Vector2{0, 0}, 0, WHITE);
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

void Car::slowUnnatural() {
    if (isSlowingUnnatural && isAccelerating) {
        return;
    }
    std::cout << "Начало: " << velocity.x << std::endl;
    checkOnce = true;
    velocity2 = velocity;
    slowUnnaturalStartTime = GetTime();
    isSlowingUnnatural = true;
    targetVelocity = Vector2(2, 0);
}

bool Car::isUnnaturalSlowing() {
    return isSlowingUnnatural;
}
