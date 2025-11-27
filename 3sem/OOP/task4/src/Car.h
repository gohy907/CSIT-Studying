#pragma once
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
