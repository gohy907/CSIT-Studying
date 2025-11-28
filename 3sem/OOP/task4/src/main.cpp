#include "raylib.h"
#include "Car.h"
#include "raygui.h"
#include "Road.h"

const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

const float CAR_WIDTH = 120;
const float CAR_HEIGHT = 85;

const Rectangle RED_CAR_SPRITE = Rectangle{0, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle GREEN_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1), 0, CAR_WIDTH, CAR_HEIGHT}; 
const Rectangle YELLOW_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 2, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle BLUE_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 3, 0, CAR_WIDTH, CAR_HEIGHT};

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    Road mainRoad = Road(150, 100.0, 1600.0, 150.0, 5.0, BLACK, BLACK, RAYWHITE);
    Texture2D atlas = LoadTexture("./cars.png");
    Car car = Car(Vector2{0, 130}, Vector2{10, 0},  BLUE_CAR_SPRITE, atlas);
    SetTargetFPS(60);
    mainRoad.addCar(car);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            mainRoad.draw();
            mainRoad.update();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
