#include "raylib.h"
#include "raymath.h"

const float CAR_WIDTH = 120;
const float CAR_HEIGHT = 85;

const float DAMAGED_CAR_WIDTH = 130;
const float DAMAGED_CAR_HEIGHT = 95;

const Rectangle RED_CAR_SPRITE = Rectangle{0, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle GREEN_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1), 0, CAR_WIDTH, CAR_HEIGHT}; 
const Rectangle YELLOW_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 2, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle BLUE_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 3, 0, CAR_WIDTH, CAR_HEIGHT};

const Rectangle COLORS[4]{RED_CAR_SPRITE, GREEN_CAR_SPRITE, YELLOW_CAR_SPRITE, BLUE_CAR_SPRITE};

const Rectangle RED_DAMAGED_CAR_SPRITE = Rectangle{0, 0, DAMAGED_CAR_WIDTH, DAMAGED_CAR_HEIGHT};
const Rectangle GREEN_DAMAGED_CAR_SPRITE = Rectangle{(DAMAGED_CAR_WIDTH + 1), (CAR_HEIGHT + 1), DAMAGED_CAR_WIDTH, DAMAGED_CAR_HEIGHT};
const Rectangle YELLOW_DAMAGED_CAR_SPRITE = Rectangle{(DAMAGED_CAR_WIDTH + 1) * 2, (CAR_HEIGHT + 1), DAMAGED_CAR_WIDTH, DAMAGED_CAR_HEIGHT};
const Rectangle BLUE_DAMAGED_CAR_SPRITE = Rectangle{(DAMAGED_CAR_WIDTH + 1) * 3, (CAR_HEIGHT + 1), DAMAGED_CAR_WIDTH, DAMAGED_CAR_HEIGHT};

const Rectangle DAMAGED_COLORS[4]{RED_DAMAGED_CAR_SPRITE, GREEN_DAMAGED_CAR_SPRITE, YELLOW_DAMAGED_CAR_SPRITE, BLUE_DAMAGED_CAR_SPRITE};

const float PAUSE_DURATION = 3;
const float ACCELERATION_DURATION = 3;

enum typeOfDamage {
    front,
    rear,
    None
};

class Car {
    private:
        Vector2 position;
        Vector2 velocity;
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

        if (elapsed < ACCELERATION_DURATION) {
            // Линейная интерполяция скорости
            float t = elapsed / ACCELERATION_DURATION;  // 0.0 → 1.0
            velocity = Vector2Lerp({0, 0}, targetVelocity, t);
        }
        else {
        slowdownStartTime = 0;
        velocity = targetVelocity;
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
    damaged = true;
}

void Car::repair() {
    damageType = typeOfDamage::None;
    slowdownStartTime = GetTime();
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

Vector2 Car::getTargetVelocity() {
    return targetVelocity;
}

void Car::setTargetVelocity(Vector2 velocity) {
    targetVelocity = velocity;
}
