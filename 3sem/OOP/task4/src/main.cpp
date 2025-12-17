#include "raylib.h"
#include "Car.h"
#include "raygui.h"
#include "Road.h"
#include "resources.h"
#include "resourcesControl.h"

const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

const float FONT_SIZE = 30;

const Rectangle SPEED_SLIDER = Rectangle{150, 300, 340, 70};

const Rectangle CAR_SPAWN_BUTTON = Rectangle{500, 300, 340, 70};

// В FontUtils.cpp или main.cpp

Font LoadRussianFontStatic(int fontSize) {
    int charsCount = 0;
    int* chars = LoadCodepoints(
        "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"
        "0123456789"
        ".,!?-+()[]{}:;/\\\"'`~@#$%^&*=_|<> "
        "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", 
        &charsCount
    );

    Font font = LoadFontFromMemory(
        ".ttf",         
        HYWENHEI_data, 
        HYWENHEI_size,
        fontSize,        
        chars,          
        charsCount     
    );

    UnloadCodepoints(chars);
    return font;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
    InitResources();
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);
    Font font = LoadRussianFontStatic(FONT_SIZE);
    GuiSetFont(font);
    Road mainRoad = Road(ROAD_X, ROAD_Y, ROAD_WIDTH, ROAD_HEIGHT, ROAD_BORDER_WIDTH, BLACK, BLACK, RAYWHITE);
    Car car = Car(Vector2{CAR_SPAWN_X,CAR_SPAWN_Y}, Vector2{10, 0},  BLUE_CAR_SPRITE, BLUE_DAMAGED_CAR_SPRITE, GetCarsAtlas());
    SetTargetFPS(60);
    mainRoad.addCar(car);
    int defaultSpeed = 10;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            GuiValueBox(SPEED_SLIDER, "Скорость ", &defaultSpeed, 0, 40, true);
            if (GuiButton(CAR_SPAWN_BUTTON, "Создать новую машину")) {
                Car newCar = Car(Vector2{CAR_SPAWN_X, CAR_SPAWN_Y}, 
                                 Vector2{(float)defaultSpeed, 0},
                                 BLUE_CAR_SPRITE, BLUE_DAMAGED_CAR_SPRITE, GetCarsAtlas());
                mainRoad.addCar(newCar);
            }
            GuiButton(Rectangle{500, 500, 30, 30}, "<");
            mainRoad.draw();
            mainRoad.update();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }
    
    UnloadResources();
    CloseWindow();

    return 0;
}
