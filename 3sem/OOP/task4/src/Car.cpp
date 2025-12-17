#include "raylib.h"
#include "raymath.h"
#include "resources.h"

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

class Car {
    private:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;

        Rectangle texture;
        Rectangle damagedTexture;

        Texture2D atlas;
        float width = CAR_WIDTH;
        float height = CAR_HEIGHT;

        bool damaged = false;

        float collisionTime = 0;  
        float invincibilityTime = 0;

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

        float getInvincibilityTime();
        void setInvincibilityTime(float time);

        void setCollisionTime(float time);
        float getCollisionTime();
};

Car::Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle texture, Rectangle damagedTexture, Texture2D atlas) {
    this-> position = position;
    this-> velocity = velocity;
    this->acceleration = acceleration;
    this->texture = texture;
    this->damagedTexture = damagedTexture;
    this->atlas = atlas;
}

Car::Car(Vector2 position, Vector2 velocity, Rectangle texture, Rectangle damagedTexture, Texture2D atlas) {
    this-> position = position;
    this-> velocity = velocity;
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
    if (collisionTime > 0) {
        if (currentTime - collisionTime < PAUSE_DURATION) {
            return; 
        }
        collisionTime = 0;
        damaged = false;
    }
    if (invincibilityTime > 0 && currentTime - invincibilityTime < 3) {
        invincibilityTime = 0;
    } 

    if (damaged && invincibilityTime == 0) {
        return;
    }
    float dt = GetFrameTime() * 60;
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
    return this->damaged;
}

void Car::damage() {
    collisionTime = GetTime();
    damaged = true;
}

void Car::repair() {
    collisionTime = 0;
    damaged = false;
}

float Car::getInvincibilityTime() {
    return invincibilityTime;
}

void Car::setInvincibilityTime(float time) {
    invincibilityTime = time;
}

void Car::setCollisionTime(float time) {
    collisionTime = time;
}

float Car::getCollisionTime() {
    return collisionTime;
}

Vector2 Car::getAcceleration() {
    return acceleration;
}

void Car::setAcceleration(Vector2 acceleration) {
    this->acceleration = acceleration;
}
