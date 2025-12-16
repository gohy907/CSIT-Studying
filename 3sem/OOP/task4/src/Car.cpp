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
const Rectangle GREEN_DAMAGED_CAR_SPRITE = Rectangle{(DAMAGED_CAR_WIDTH + 1), 0, DAMAGED_CAR_WIDTH, DAMAGED_CAR_HEIGHT};
const Rectangle YELLOW_DAMAGED_CAR_SPRITE = Rectangle{(DAMAGED_CAR_WIDTH + 1) * 2, 0, DAMAGED_CAR_WIDTH, DAMAGED_CAR_HEIGHT};
const Rectangle BLUE_DAMAGED_CAR_SPRITE = Rectangle{(DAMAGED_CAR_WIDTH + 1) * 3, 0, DAMAGED_CAR_WIDTH, DAMAGED_CAR_HEIGHT};

const Rectangle DAMAGED_COLORS[4]{RED_DAMAGED_CAR_SPRITE, GREEN_DAMAGED_CAR_SPRITE, YELLOW_DAMAGED_CAR_SPRITE, BLUE_DAMAGED_CAR_SPRITE};

Texture2D LoadCarTextureStatic() {
    Image img = LoadImageFromMemory(".png", CARS_data, CARS_size);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

class Car {
    private:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        Rectangle source;
        Texture2D atlas;
        float width = CAR_WIDTH;
        float height = CAR_HEIGHT;
    public:
        Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle source, Texture2D atlas);
        Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle source);
        Car(Vector2 position, Vector2 velocity, Rectangle source, Texture2D atlas);
        Car(Vector2 position, Vector2 velocity, Rectangle source);

        float getWidth();
        float getHeight();

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

void Car::setSource(Rectangle source){
    this->source = source;
}

void Car::update() {
    float dt = GetFrameTime() * 60;
    position = Vector2Add(position, Vector2Scale(velocity, dt));
    velocity = Vector2Add(velocity, Vector2Scale(acceleration, dt));
}

void Car::draw(){
    DrawTexturePro(atlas, source, Rectangle{position.x, position.y, width, height}, Vector2{0, 0}, 0, WHITE);
}
