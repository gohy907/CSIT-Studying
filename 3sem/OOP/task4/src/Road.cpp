#include "raylib.h"
#include <vector>
#include "Car.h"

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
        cars[i].update();
    }
}
void Road::draw() {
    DrawRectangleRec(this->top, this->borderColor);
    DrawRectangleRec(this->bottom, this->borderColor);
    DrawRectangleRec(this->left, this->borderColor);
    DrawRectangleRec(this->right, this->borderColor);

    for (size_t i = 0; i < cars.size(); ++i) {
        cars[i].draw();
    }

    DrawRectangleRec(this->leftBounds, this->boundsColor);
    DrawRectangleRec(this->rightBounds, this->boundsColor);
}


