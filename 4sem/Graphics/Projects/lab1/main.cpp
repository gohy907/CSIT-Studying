#include <raylib.h>

const char *const LETTERS =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
    "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 480, "aboba");
    SetTargetFPS(60);

    int cnt = 0;
    int *codepoints = LoadCodepoints(LETTERS, &cnt);
    Font f =
        LoadFontEx("Assets/Fonts/BwSurco-Regular.ttf", 26, codepoints, cnt);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        const float Wx = static_cast<float>(GetScreenWidth());
        const float Wy = static_cast<float>(GetScreenHeight());

        const Vector2 point1{0, Wy * 1 / 3};
        const Vector2 point2{Wx * 2 / 3, 0};
        const Vector2 point3{Wx, Wy * 2 / 3};
        const Vector2 point4{Wx * 1 / 3, Wy};

        DrawLineEx(point1, point2, 5, LIME);
        DrawLineEx(point2, point3, 5, LIME);
        DrawLineEx(point3, point4, 5, LIME);
        DrawLineEx(point4, point1, 5, LIME);

        DrawLineEx({0, 0}, {Wx, Wy}, 6, RED);
        DrawLineEx({90, 50}, {Wx, 80}, 10, BLUE);
        DrawTextEx(f, "Всем привет", {40, 380}, 26, 0, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
