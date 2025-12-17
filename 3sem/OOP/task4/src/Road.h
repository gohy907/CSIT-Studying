#pragma once
#include "raylib.h"
#include "Car.h"
#include "raylib.h"
#include <vector>

class Road {
private:
    Rectangle top;
    Rectangle bottom;
    Rectangle left;
    Rectangle right;

    Rectangle leftBounds;
    Rectangle rightBounds;

    Color backgroundColor;
    Color borderColor;
    Color boundsColor;

    bool isRandomMovementActive;

    std::vector<Car> cars;
public:
    Road(float x, float y, float width, float height, 
         float thickness, Color backgroundColor, Color borderColor, Color boundsColor);

    void setCarList(std::vector<Car> cars);
    void addCar(Car car);

    void update();
    void draw();
    
    void startRandomMovement();
    void endRandomMovement();
};
