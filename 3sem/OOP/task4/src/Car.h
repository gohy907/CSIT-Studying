#pragma once
#include "raylib.h"

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

class Car {
    private:
        Vector2 position;
        Vector2 previousVelocity;
        Vector2 activeVelocity;
        Vector2 acceleration;

        Rectangle texture;
        Rectangle damagedTexture;

        Texture2D atlas;
        float width = CAR_WIDTH;
        float height = CAR_HEIGHT;

        bool damaged = false;
    public:
        Car(Vector2 position, Vector2 velocity, Vector2 acceleration, Rectangle texture, Rectangle damagedTexture, Texture2D atlas);
        Car(Vector2 position, Vector2 velocity, Rectangle texture, Rectangle damagedTexture, Texture2D atlas);

        float getWidth();
        float getHeight();

        void setPosition(Vector2 position);
        Vector2 getPosition();
        
        void setVelocity(Vector2 velocity);
        Vector2 getVelocity();
        
        void update();
        void draw(bool isDamaged);

        bool isDamaged();
        void damage();
        void repair();
};
