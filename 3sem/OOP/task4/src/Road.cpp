// Road.cpp
#include "raylib.h"
#include "raygui.h"      
#include "Car.h"
#include "resourcesControl.h"
#include "constants.h"
#include "raymath.h"
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>

std::random_device rd; 
std::mt19937 gen(rd());
std::uniform_int_distribution<int> chanceDistribution(1, 30); 
std::uniform_int_distribution<int> speedDistribution(5, 40);
std::uniform_int_distribution<int> colorDistribution(0, 3);

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

Road::Road(float x, float y, float width, float height, 
            float thickness, Color backgroundColor, Color borderColor, Color boundsColor) {
    this->top = Rectangle{x, y, width, thickness};
    this->bottom = Rectangle{x, y + height - thickness, width, thickness};
    this->left = Rectangle{x, y, thickness, height};
    this->right = Rectangle{x + width - thickness, y, thickness, height};

    this->leftBounds = Rectangle{0.0, y, x, height};
    this->rightBounds = Rectangle{x + width, y, width, height};

    this->borderColor = borderColor;
    this->boundsColor = boundsColor;

    this->isRandomMovementActive = false;
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
        car.update();
    }

    // Пу пу пу
    cars.erase(
        std::remove_if(cars.begin(), cars.end(),
        [this](Car &car) {
            return car.getPosition().x > top.x + top.width;
        }),
        cars.end()
    );

    for (size_t i = 0; cars.size() > i + 1; ++i) {
        float currentTime = GetTime();
        Car &firstCar = cars[i];
        Car &secondCar = cars[i + 1];

        if (!secondCar.isDamaged() && 
            firstCar.getPosition().x - secondCar.getPosition().x < CAR_WIDTH) {
            firstCar.setDamageType(typeOfDamage::rear);
            secondCar.setDamageType(typeOfDamage::front);
            secondCar.setTargetVelocity(firstCar.getTargetVelocity());
            firstCar.damage();
            secondCar.damage();
        }

        if (secondCar.getDamageType() == typeOfDamage::front && firstCar.getPosition().x - secondCar.getPosition().x >= CAR_WIDTH &&
            firstCar.getPosition().x) {
            secondCar.setDamageType(typeOfDamage::None);
            secondCar.repair();
        }

        if (firstCar.isDamaged() && secondCar.isDamaged()) {
            Vector2 center = Vector2Add(
                Vector2Subtract(firstCar.getPosition(), secondCar.getPosition()), Vector2(-CAR_WIDTH/2, CAR_HEIGHT)
            );
            GuiTextBox(Rectangle(center.x, center.y, CAR_WIDTH, CAR_HEIGHT), "dasd", 20, false);
        }
    }

    if (this->isRandomMovementActive) {
            int chance = chanceDistribution(gen);
            if ((cars.size() != 0 && cars[cars.size() - 1].getPosition().x > CAR_WIDTH || cars.size() == 0) && chance == 1) {
                int index = colorDistribution(gen);
                Car randomCar = Car(
                    Vector2(CAR_SPAWN_X, CAR_SPAWN_Y), 
                    Vector2(speedDistribution(gen), 0), 
                    COLORS[index],
                    DAMAGED_COLORS[index],
                    GetCarsAtlas()
                );
                this->cars.push_back(randomCar);
            }
    }
}
void Road::draw() {
    for (size_t i = 0; i < cars.size(); ++i) {
        cars[i].draw(cars[i].isDamaged());
    }

    DrawRectangleRec(this->top, this->borderColor);
    DrawRectangleRec(this->bottom, this->borderColor);
    DrawRectangleRec(this->left, this->borderColor);
    DrawRectangleRec(this->right, this->borderColor);

    DrawRectangleRec(this->leftBounds, this->boundsColor);
    DrawRectangleRec(this->rightBounds, this->boundsColor);
}

void Road::startRandomMovement() {
    this->isRandomMovementActive = true;
}

void Road::endRandomMovement() {
    this->isRandomMovementActive = false;
}
