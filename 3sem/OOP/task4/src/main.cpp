#include "raylib.h"
#include "Car.h"
#include "raygui.h"
#include "Road.h"
#include "resources.h"

const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

const float FONT_SIZE = 30;

const Rectangle RED_CAR_SPRITE = Rectangle{0, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle GREEN_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1), 0, CAR_WIDTH, CAR_HEIGHT}; 
const Rectangle YELLOW_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 2, 0, CAR_WIDTH, CAR_HEIGHT};
const Rectangle BLUE_CAR_SPRITE = Rectangle{(CAR_WIDTH + 1) * 3, 0, CAR_WIDTH, CAR_HEIGHT};

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
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);
    Font font = LoadRussianFontStatic(FONT_SIZE);
    GuiSetFont(font);
    Road mainRoad = Road(ROAD_X, ROAD_Y, ROAD_WIDTH, ROAD_HEIGHT, ROAD_BORDER_WIDTH, BLACK, BLACK, RAYWHITE);
    Car car = Car(Vector2{CAR_SPAWN_X,CAR_SPAWN_Y}, Vector2{10, 0},  BLUE_CAR_SPRITE);
    SetTargetFPS(60);
    mainRoad.addCar(car);
    int defaultSpeed = 10;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            GuiValueBox(SPEED_SLIDER, "Скорость ", &defaultSpeed, 0, 40, true);
            if (GuiButton(CAR_SPAWN_BUTTON, "Создать новую машину")) {
                mainRoad.addCar(car);
            }
            car.setVelocity(Vector2{(float)defaultSpeed, 0});
            GuiButton(Rectangle{500, 500, 30, 30}, "<");
            mainRoad.draw();
            mainRoad.update();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
