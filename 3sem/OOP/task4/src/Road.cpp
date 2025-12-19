// Road.cpp

#include "raylib.h"
#include "raygui.h"      
#include "Car.h"
#include "resourcesControl.h"
#include "constants.h"
#include "raymath.h"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

std::random_device rd; 
std::mt19937 gen(rd());
std::uniform_int_distribution<int> chanceDistribution(1, 30); 
std::uniform_int_distribution<int> speedDistribution(5 * 60, 20 * 60);
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

    this->isRandomMovementActive = true;
}

void Road::setCarList(std::vector<Car> cars) {
    this->cars = cars;
}

void Road::addCar(Car car) {
    this->cars.push_back(car);
}

void Road::update() {
    const char* text = "Авария!";
    for (size_t i = 0; i < cars.size(); ++i) {
        Car &car = cars[i];

    // std::cout << car.getVelocity().x << " " << car.getTargetVelocity().x << std::endl;
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

        // if(!firstCar.isDamaged() && !firstCar.isUnnaturalSlowing()) {
        //     firstCar.setTargetVelocity
        // }

        // std::cout << secondCar.getTargetVelocity().x << " " << secondCar.isSlowing << std::endl
        
        // if(i == 0 && !firstCar.isDamaged()) {
        //     firstCar.accelerate(ACCELERATION_DURATION, firstCar.getMaximumVelocity(), 4);
        // } 
        //
        // if (!secondCar.isDamaged() && firstCar.getPosition().x - secondCar.getPosition().x >= 3 * CAR_WIDTH && 
        //     secondCar.getVelocity().x < firstCar.getVelocity().x) {
        //     std::cout << "Зашёл в хуйню" << std::endl;
        //     if (secondCar.getMaximumVelocity().x > firstCar.getVelocity().x) {
        //         secondCar.accelerate(ACCELERATION_DURATION, firstCar.getVelocity(), 4);
        //     } else {
        //         secondCar.accelerate(ACCELERATION_DURATION, secondCar.getMaximumVelocity(), 4);
        //     }
        // }
        
        if (!secondCar.isDamaged() && firstCar.getPosition().x - secondCar.getPosition().x < 3 * CAR_WIDTH) {
            // std::cout << secondCar.getAcceleration().x << std::endl;
            secondCar.slowdown(BREAKES_DURATION, firstCar.getVelocity(), 1);
        }

        if (!secondCar.isDamaged() && 
            firstCar.getPosition().x - secondCar.getPosition().x < CAR_WIDTH) {
            firstCar.setDamageType(typeOfDamage::rear);
            secondCar.setDamageType(typeOfDamage::front);
            firstCar.damage();
            secondCar.damage();
        }

        if (secondCar.getDamageType() == typeOfDamage::front && firstCar.getPosition().x - secondCar.getPosition().x >= 1.5 * CAR_WIDTH) {
            secondCar.repair();
            std::cout << secondCar.getVelocity().x << " " << firstCar.getVelocity().x << std::endl; 
            secondCar.accelerate(ACCELERATION_DURATION, firstCar.getTargetVelocity(), 3);
        }

        if (firstCar.isDamaged() && secondCar.isDamaged() && firstCar.getPosition().x - secondCar.getPosition().x < CAR_WIDTH) {
            Vector2 center = Vector2Add(firstCar.getPosition(), secondCar.getPosition());
            center = Vector2Divide(center, Vector2(2, 2));
            Rectangle box = Rectangle(center.x, center.y - CAR_HEIGHT / 2, CAR_WIDTH, CAR_HEIGHT/2);
            DrawRectangleRec(box, RED);
            int textWidth = MeasureText(text, FONT_SIZE);
            int textX = box.x + (box.width  - textWidth)/2 + 10;
            int textY = box.y + (box.height - FONT_SIZE)/2;
            DrawTextEx(GuiGetFont(), text, Vector2(textX, textY), FONT_SIZE, 0, BLACK);
            // DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint)
        }
    }

    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        for (size_t i = 0; i < cars.size(); ++i){
            Car& car = cars[i];
            if (!car.isDamaged()) { 
                Rectangle carRect = {car.getPosition().x, car.getPosition().y, 
                    car.getWidth(), car.getHeight()};
                if (CheckCollisionPointRec(mousePos, carRect)) {
                    car.slowdown(ACCELERATION_DURATION, Vector2(60, 0), 5);

                    break;
                }
            }
        }
    }
    if (this->isRandomMovementActive) {
            int chance = chanceDistribution(gen);
            if ((cars.size() != 0 && cars[cars.size() - 1].getPosition().x > CAR_WIDTH || cars.size() == 0) && chance == 1) {
                int index = colorDistribution(gen);
                Texture2D* carsAtlas = GetCarsAtlas();
                Car randomCar = Car(
                    Vector2(CAR_SPAWN_X, CAR_SPAWN_Y), 
                    Vector2(speedDistribution(gen), 0), 
                    COLORS[index],
                    DAMAGED_COLORS[index],
                    carsAtlas
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
