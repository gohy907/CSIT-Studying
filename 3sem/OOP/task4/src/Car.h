#pragma once
#include "raylib.h"

const float CAR_WIDTH = 120;
const float CAR_HEIGHT = 85;

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
