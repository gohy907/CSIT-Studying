#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "Car.h"
#include "Road.h"
#include "resources.h"
#include "resourcesControl.h"
#include "constants.h"

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
    Texture2D* carsAtlas = GetCarsAtlas();
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);
    Font font = LoadRussianFontStatic(FONT_SIZE);
    GuiSetFont(font);
    Road mainRoad = Road(ROAD_X, ROAD_Y, ROAD_WIDTH, ROAD_HEIGHT, ROAD_BORDER_WIDTH, BLACK, BLACK, RAYWHITE);
    Car car = Car(Vector2{CAR_SPAWN_X,CAR_SPAWN_Y}, Vector2{600, 0},  BLUE_CAR_SPRITE, BLUE_DAMAGED_CAR_SPRITE, carsAtlas);
    SetTargetFPS(60);
    mainRoad.addCar(car);
    int defaultSpeed = 10;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            GuiValueBox(SPEED_SLIDER, "Скорость ", &defaultSpeed, 0, 2400, true);
            if (GuiButton(CAR_SPAWN_BUTTON, "Создать новую машину")) {
                Car newCar = Car(Vector2{CAR_SPAWN_X, CAR_SPAWN_Y}, 
                                 Vector2{(float)defaultSpeed * 60, 0},
                                 BLUE_CAR_SPRITE, BLUE_DAMAGED_CAR_SPRITE, carsAtlas);
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
