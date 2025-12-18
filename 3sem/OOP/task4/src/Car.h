#pragma once
#include "raylib.h"
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

        Texture2D atlas;
        float width = CAR_WIDTH;
        float height = CAR_HEIGHT;

        bool damaged = false;
        typeOfDamage damageType;

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

        float getInvincibilityTime();
        void setInvincibilityTime(float time);

        void setCollisionTime(float time);
        float getCollisionTime();

        void makeInvincible();
        bool isInvincible();

        enum typeOfDamage getDamageType();
        void setDamageType(enum typeOfDamage type);

        Vector2 getTargetVelocity();
        void setTargetVelocity(Vector2 velocity);

        void slow();
        bool isSlowing;
};
