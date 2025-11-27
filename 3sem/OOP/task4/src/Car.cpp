#include "raylib.h"

class Car {
    private:
        float x;
        float y;
        float velocity;
        Rectangle source;
        Texture2D atlas;
        float width = 120;
        float height = 85;
    public:
        Car(float x, float y, float velocity, Rectangle source, Texture2D atlas);
        
        void setX(float x);
        float getX();

        void setY(float y);
        float getY();

        void setVelocity(float velocity);
        float getVelocity();

        void setSource(Rectangle source);
        
        void draw();
};

Car::Car(float x, float y, float velocity, Rectangle source, Texture2D atlas) {
    this->x = x;
    this->y = x;
    this->velocity = velocity;
    this->source = source;
    this->atlas = atlas;
}

void Car::setX(float x){
    this->x = x;
}

float Car::getX(){
    return x;
}

void Car::setY(float y){
    this->y = y;
}

float Car::getY(){
    return y;
}
    
void Car::setVelocity(float velocity){
    this->velocity = velocity;
}

float Car::getVelocity(){
    return velocity;
}

void Car::setSource(Rectangle source){
    this->source = source;
}

void Car::draw(){
    x += velocity;
    DrawTexturePro(atlas, source, Rectangle{x, y, width, height}, Vector2{0, 0}, 0, WHITE);
}
