#include "raylib.h"
#include "Car.h"
#include "raygui.h"
#include "Road.h"

const float CAR_WIDTH = 120;
const float CAR_HEIGHT = 85;

int main()
{
    InitWindow(1920, 1080, "raylib [core] example - basic window");

    Road mainRoad = Road(100.0, 100.0, 1720.0, 150.0, 5.0, BLACK, BLACK, RAYWHITE);
    Texture2D atlas = LoadTexture("./cars.png");
    Car car = Car(0, 0, 5, Rectangle{0, 0, CAR_WIDTH, CAR_HEIGHT}, atlas);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            // DrawRectangleRec(car, RED);
            mainRoad.draw();
            car.draw();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
