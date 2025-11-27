#include "raylib.h"
#include "raymath.h"

class Car {
    private:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        Rectangle source;
        Texture2D atlas;
        float width = 120;
        float height = 85;
    public:
        Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle source, Texture2D atlas);
        Car(Vector2 position, Vector2 velocity, Rectangle source, Texture2D atlas);
        
        void setPosition(Vector2 position);
        Vector2 getPosition();
        
        void setVelocity(Vector2 velocity);
        Vector2 getVelocity();

        void setSource(Rectangle source);
        
        void update();
        void draw();
};

Car::Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle source, Texture2D atlas) {
    this-> position = position;
    this-> velocity = velocity;
    this->acceleration = acceleration;
    this->source = source;
    this->atlas = atlas;
}

Car::Car(Vector2 position, Vector2 velocity, Rectangle source, Texture2D atlas) {
    this-> position = position;
    this-> velocity = velocity;
    this->acceleration = Vector2{0.0, 0.0};
    this->source = source;
    this->atlas = atlas;
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

void Car::setSource(Rectangle source){
    this->source = source;
}

void Car::update() {
    position = Vector2Add(position, velocity);
    velocity = Vector2Add(velocity, acceleration);
}

void Car::draw(){
    DrawTexturePro(atlas, source, Rectangle{position.x, position.y, width, height}, Vector2{0, 0}, 0, WHITE);
}
