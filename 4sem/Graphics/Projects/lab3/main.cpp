#include "figure.hpp"
#include "hare.hpp"
#include "matrix.hpp"
#include "transform.hpp"
#include <cstdlib>
#include <raylib.h>

const char *const LETTERS =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
    "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

#include <iostream>

int main() {
    // abort();

    std::cout << "ABOBA";
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 720, "aboba");

    std::cout << "ABOBA";

    SetTargetFPS(60);
    const ssu::Figure &defaultFigure = ssu::figure::HARE;
    const ssu::Figure &figure = ssu::figure::SLOW;
    ssu::Figure currentFigure = figure;

    bool setDefaultFigure = false;
    bool keepAspect = true;
    Mat3 T = Mat3(1.f);
    Mat3 initT;

    std::cout << "ABASPODP{AD:"
                 "LASJLKDJASLKDJASLKDJASLKJDLKASJDLKASJDLKJASKLDJ}";
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

        initT = translate(0, Ty) * scale(Sx, -Sy);
        Mat3 M = T * initT;

        std::cout << "ABOBA";
        for (size_t i = 0; i < currentFigure.vertices.size(); i += 4) {
            std::cout << "ABOBA";
            Vec3 A = Vec3(currentFigure.vertices[i], figure.vertices[i + 1], 1);
            Vec3 B =
                Vec3(currentFigure.vertices[i + 2], figure.vertices[i + 3], 1);
            Vec2 a = normalize(M * A);
            Vec2 b = normalize(M * B);
            DrawLineEx({a.x, a.y}, {b.x, b.y}, 2, BLACK);
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
