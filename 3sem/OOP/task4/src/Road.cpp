#include "raylib.h"
#include <vector>
#include <iostream>
#include "Car.h"
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

Road:: Road(float x, float y, float width, float height, 
            float thickness, Color backgroundColor, Color borderColor, Color boundsColor) {
    this->top = Rectangle{x, y, width, thickness};
    this->bottom = Rectangle{x, y + height - thickness, width, thickness};
    this->left = Rectangle{x, y, thickness, height};
    this->right = Rectangle{x + width - thickness, y, thickness, height};

    this->leftBounds = Rectangle{0.0, y, x, height};
    this->rightBounds = Rectangle{x + width, y, width, height};

    this->borderColor = borderColor;
    this->boundsColor = boundsColor;
}

void Road::setCarList(std::vector<Car> cars) {
    this->cars = cars;
}

void Road::addCar(Car car) {
    this->cars.push_back(car);
}

void Road::update() {
    for (size_t i = 0; i < cars.size(); ++i) {
        Car &car = cars[i];
        if (car.getPosition().x  > top.x + top.width) {
            cars.erase(cars.begin() + i);
        } else {
            car.update();
        }
    }
}
void Road::draw() {
    for (size_t i = 0; i < cars.size(); ++i) {
        cars[i].draw();
    }

    DrawRectangleRec(this->top, this->borderColor);
    DrawRectangleRec(this->bottom, this->borderColor);
    DrawRectangleRec(this->left, this->borderColor);
    DrawRectangleRec(this->right, this->borderColor);

    DrawRectangleRec(this->leftBounds, this->boundsColor);
    DrawRectangleRec(this->rightBounds, this->boundsColor);
}


