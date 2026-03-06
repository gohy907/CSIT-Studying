#include "figure.hpp"
#include "hare.hpp"
#include <raylib.h>

const char *const LETTERS =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
    "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

#include <iostream>

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "aboba");
    SetTargetFPS(60);
    const ssu::Figure &defaultFigure = ssu::figure::HARE;
    const ssu::Figure &figure = ssu::figure::SLOW;
    ssu::Figure currentFigure = figure;

    bool setDefaultFigure = false;
    bool keepAspect = true;
    while (!WindowShouldClose()) {
        float figureAspect = currentFigure.Vx / currentFigure.Vy;
        BeginDrawing();
        ClearBackground(SKYBLUE);
        const float Wx = static_cast<float>(GetScreenWidth());
        const float Wy = static_cast<float>(GetScreenHeight());
        const float windowAspect = Wx / Wy;
        float Sx, Sy;
        if (keepAspect) {
            Sx = Sy =
                figureAspect < windowAspect ? Wy / figure.Vy : Wx / figure.Vx;
        } else {
            Sx = Wx / currentFigure.Vx;
            Sy = Wy / currentFigure.Vy;
        }
        const float Ty = Sy * currentFigure.Vy;

        for (size_t i = 0; i < currentFigure.vertices.size(); i += 4) {
            DrawLineEx({Sx * currentFigure.vertices[i],
                        Ty - Sy * currentFigure.vertices[i + 1]},
                       {Sx * currentFigure.vertices[i + 2],
                        Ty - Sy * currentFigure.vertices[i + 3]},
                       2, BLACK);
        }
        if (IsKeyPressed(KEY_M)) {
            keepAspect = !keepAspect;
        }
        if (IsKeyPressed(KEY_N)) {
            setDefaultFigure = !setDefaultFigure;
            if (setDefaultFigure) {
                currentFigure = defaultFigure;
            } else {
                currentFigure = figure;
            }

            figureAspect = currentFigure.Vx / currentFigure.Vy;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
