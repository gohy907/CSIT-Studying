#pragma once
#include "raylib.h"
#include "Car.h"
#include "raylib.h"
#include <vector>

const float ROAD_X = 50;
const float ROAD_Y = 100;
const float ROAD_WIDTH = 1820;
const float ROAD_HEIGHT = 150;
const float ROAD_BORDER_WIDTH = 5;

const float CAR_SPAWN_X = ROAD_X + ROAD_BORDER_WIDTH - CAR_WIDTH;
const float CAR_SPAWN_Y = (ROAD_Y + ROAD_Y + ROAD_HEIGHT)/2 - CAR_HEIGHT/2;

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

    std::vector<Car> cars;
public:
    Road(float x, float y, float width, float height, 
         float thickness, Color backgroundColor, Color borderColor, Color boundsColor);

    void setCarList(std::vector<Car> cars);
    void addCar(Car car);

    void update();
    void draw();

};
