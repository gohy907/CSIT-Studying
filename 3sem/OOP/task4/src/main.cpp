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

Font InitRussianFont(const char *fontPath, int fontSize) {
    int charsCount = 0;
    int* chars = LoadCodepoints(
        "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"
        "0123456789"
        ".,!?-+()[]{}:;/\\\"'`~@#$%^&*=_|<> "
        "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", 
        &charsCount
    );

    Font font = LoadFontEx(fontPath, fontSize, chars, charsCount);
    UnloadCodepoints(chars);
    return font;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    Font font = InitRussianFont("static/HYWenHei.ttf", 50);
    Road mainRoad = Road(150, 100.0, 1600.0, 150.0, 5.0, BLACK, BLACK, RAYWHITE);
    Texture2D atlas = LoadTexture("static/cars.png");
    Car car = Car(Vector2{0, 130}, Vector2{10, 0},  BLUE_CAR_SPRITE, atlas);
    SetTargetFPS(60);
    mainRoad.addCar(car);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawTextEx(font, "aboba", Vector2{100.0, 300.0}, 50, 0, BLACK);
            mainRoad.draw();
            mainRoad.update();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
