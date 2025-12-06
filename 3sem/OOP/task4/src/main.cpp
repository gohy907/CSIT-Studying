#include "raylib.h"
#include "Car.h"
#include "raygui.h"
#include "Road.h"

const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

const float ROAD_X = 50;
const float ROAD_Y = 100;
const float ROAD_WIDTH = 1820;
const float ROAD_HEIGHT = 150;
const float ROAD_BORDER_WIDTH = 5;

const float CAR_WIDTH = 120;
const float CAR_HEIGHT = 85;
const float CAR_SPAWN_X = ROAD_X + ROAD_BORDER_WIDTH - CAR_WIDTH;
const float CAR_SPAWN_Y = (ROAD_Y + ROAD_Y + ROAD_HEIGHT)/2 - CAR_HEIGHT/2;

const float FONT_SIZE = 30;

const Rectangle RED_CAR_SPRITE = Rectangle{0, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle GREEN_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1), 0, CAR_WIDTH, CAR_HEIGHT}; 
const Rectangle YELLOW_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 2, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle BLUE_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 3, 0, CAR_WIDTH, CAR_HEIGHT};

const Rectangle SPEED_SLIDER = Rectangle{150, 300, 340, 70};

const Rectangle CAR_SPAWN_BUTTON = Rectangle{500, 300, 340, 70};

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
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);
    Font font = InitRussianFont("static/HYWenHei.ttf", FONT_SIZE);
    GuiSetFont(font);
    Road mainRoad = Road(ROAD_X, ROAD_Y, ROAD_WIDTH, ROAD_HEIGHT, ROAD_BORDER_WIDTH, BLACK, BLACK, RAYWHITE);
    Texture2D atlas = LoadTexture("static/cars.png");
    Car car = Car(Vector2{CAR_SPAWN_X,CAR_SPAWN_Y}, Vector2{10, 0},  BLUE_CAR_SPRITE, atlas);
    SetTargetFPS(60);
    mainRoad.addCar(car);
    int defaultSpeed = 10;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            GuiValueBox(SPEED_SLIDER, "Скорость ", &defaultSpeed, 0, 40, true);
            bool spawnNewCar = GuiButton(CAR_SPAWN_BUTTON, "Создать новую машину");
            if (spawnNewCar) {
                mainRoad.addCar(car);
            }
            mainRoad.draw();
            mainRoad.update();
            Color color = WHITE;
            car.setVelocity(Vector2{(float)defaultSpeed, 0});
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
