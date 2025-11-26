#include "raylib.h"
#include "raygui.h"
#include "Road.h"


int main()
{
    InitWindow(1920, 1080, "raylib [core] example - basic window");

    Rectangle car = Rectangle{90.0, 125.0, 100.0, 100.0};
    Road mainRoad = Road(100.0, 100.0, 1720.0, 150.0, 5.0, BLACK, BLACK, RAYWHITE);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawRectangleRec(car, RED);
            mainRoad.draw();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
