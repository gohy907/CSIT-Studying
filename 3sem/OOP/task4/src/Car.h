#pragma once
#include "raylib.h"

const float CAR_WIDTH = 120;
const float CAR_HEIGHT = 85;


const Rectangle RED_CAR_SPRITE = Rectangle{0, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle GREEN_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1), 0, CAR_WIDTH, CAR_HEIGHT}; 
const Rectangle YELLOW_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 2, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle BLUE_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 3, 0, CAR_WIDTH, CAR_HEIGHT};

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
