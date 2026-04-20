#include "clip.hpp"
#include "figure.hpp"
#include "hare.hpp"
#include "matrix.hpp"
#include "transform.hpp"
#include <fstream>
#include <nfd.h>
#include <raygui.h>
#include <raylib.h>
#include <sstream>

#include <iostream>

bool isIgnorableLine(const std::string &line) {
    return line.find_first_not_of(" \t\r\n") == std::string::npos ||
           line.front() == '#';
}

ssu::Figure readFromFile(const char *fileName) {
    std::ifstream in(fileName);
    ssu::Figure figure;
    int r, g, b;
    float thickness;
    std::string line; // временная переменная, в которую считываются строки
    while (in) {
        // считываем очередную строку
        getline(in, line);
        if (isIgnorableLine(line)) {
            continue;
        }
        std::stringstream s(line);
        std::string cmd;      // переменная для имени команды
        s >> cmd;             // считываем имя команды
        if (cmd == "frame") { // размеры изображения
            s >> figure.Vx >> figure.Vy;
            std::cout << figure.Vx << ' ' << figure.Vy << std::endl;
        } else if (cmd == "color") {     // цвет линии
            s >> r >> g >> b;            // считываем три компоненты цвета
        } else if (cmd == "thickness") { // толщина линии
            s >> thickness;              // считываем значение толщины
        } else if (cmd == "path") {      // набор точек
            std::vector<Vec2> vertices;  // список точек ломаной
            int n;                       // количество точек
            s >> n;
            std::string str1; // дополнительная строка для чтения из файла
            while (n > 0) {   // пока не все точки считаны
                getline(in, str1);
                if (isIgnorableLine(str1)) {
                    continue;
                }
                float x, y;
                std::stringstream s1(str1);
                s1 >> x >> y;
                vertices.push_back(Vec2(x, y)); // добавляем точку в список
                --n;
            }
            // все точки считаны, генерируем ломаную (path) и кладем ее в список
            figure.paths.push_back(
                ssu::Path(vertices,
                          Color{static_cast<unsigned char>(r),
                                static_cast<unsigned char>(g),
                                static_cast<unsigned char>(b), 255},
                          thickness));
        }
    }
    return figure;
}

int main() {
    if (NFD_Init() != NFD_OKAY) {
        std::cerr << "NFD initialization failed!" << std::endl;
        return -1;
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    InitWindow(1080, 720, "aboba");
    SetExitKey(KEY_NULL);

    const ssu::Figure &figure = ssu::figure::HARE;
    ssu::Figure currentFigure = figure;

    Mat3 T = Mat3(1.f);
    Mat3 initT;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        float left = 30;
        float right = 100;
        float top = 20;
        float bottom = 50;

        const float Wx = static_cast<float>(GetScreenWidth());
        const float Wy = static_cast<float>(GetScreenHeight());

        float minX = left;
        float maxX = Wx - right;
        float minY = top;
        float maxY = Wy - bottom;
        float Rx = maxX - minX;
        float Ry = maxY - minY;
        float Rcx = minX;
        float Rcy = maxY;
        float rectAspect = Rx / Ry;

        const float windowAspect = Wx / Wy;

        DrawRectangleLinesEx({minX, minY, Rx, Ry}, 2, BLACK);
        for (const auto &lines : currentFigure.paths) {
            Vec2 start = normalize(T * Vec3(lines.vertices[0], 1));
            for (const auto &line : lines.vertices) {
                Vec2 end = normalize(T * Vec3(line, 1));
                Vec2 tmpEnd = end;
                if (clip(start, end, minX, minY, maxX, maxY)) {
                    DrawLineEx({start.x, start.y}, {end.x, end.y},
                               lines.thickness, lines.color);
                }
                start = tmpEnd;
            }
        }

        if (IsKeyDown(KEY_W)) {
            T = translate(0, -1) * T;
        }

        if (IsKeyDown(KEY_A)) {
            T = translate(-1, 0) * T;
        }
        if (IsKeyDown(KEY_S)) {
            T = translate(0, 1) * T;
        }
        if (IsKeyDown(KEY_D)) {
            T = translate(1, 0) * T;
        }

        if (IsKeyDown(KEY_T))
            T = translate(0, -10) * T;
        if (IsKeyDown(KEY_G))
            T = translate(0, 10) * T;
        if (IsKeyDown(KEY_F))
            T = translate(-10, 0) * T;
        if (IsKeyDown(KEY_H))
            T = translate(10, 0) * T;

        if (IsKeyDown(KEY_Q)) {
            T = translate(Rcx, Rcy) * rotate(-0.01f) * translate(-Rcx, -Rcy) *
                T;
        }
        if (IsKeyDown(KEY_E)) {
            T = translate(Rcx, Rcy) * rotate(0.01f) * translate(-Rcx, -Rcy) * T;
        }
        if (IsKeyDown(KEY_Y)) {
            T = translate(Rcx, Rcy) * rotate(-0.05f) * translate(-Rcx, -Rcy) *
                T;
        }
        if (IsKeyDown(KEY_R)) {
            T = translate(Rcx, Rcy) * rotate(0.05f) * translate(-Rcx, -Rcy) * T;
        }

        if (IsKeyDown(KEY_Z)) {
            T = translate(Rcx, Rcy) * scale(1.1f) * translate(-Rcx, -Rcy) * T;
        }
        if (IsKeyDown(KEY_X)) {
            T = translate(Rcx, Rcy) * scale(1.0f / 1.1f) *
                translate(-Rcx, -Rcy) * T;
        }

        if (IsKeyDown(KEY_I)) {
            T = translate(Rcx, Rcy) * scale(1.1f, 1.0f) *
                translate(-Rcx, -Rcy) * T;
        }
        if (IsKeyDown(KEY_K)) {
            T = translate(Rcx, Rcy) * scale(1.0f / 1.1f, 1.0f) *
                translate(-Rcx, -Rcy) * T;
        }
        if (IsKeyDown(KEY_O)) {
            T = translate(Rcx, Rcy) * scale(1.0f, 1.1f) *
                translate(-Rcx, -Rcy) * T;
        }
        if (IsKeyDown(KEY_L)) {
            T = translate(Rcx, Rcy) * scale(1.0f, 1.0f / 1.1f) *
                translate(-Rcx, -Rcy) * T;
        }

        if (IsKeyPressed(KEY_U)) {
            T = translate(Rcx, Rcy) * mirrorY() * translate(-Rcx, -Rcy) * T;
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            float rectAspect = Rx / Ry;
            const float figureAspect = currentFigure.Vx / currentFigure.Vy;
            float S =
                figureAspect < rectAspect ? Ry / figure.Vy : Rx / figure.Vx;

            const Mat3 T1 =
                translate(-currentFigure.Vx / 2, -currentFigure.Vy / 2);
            const Mat3 S1 = scale(S, -S);
            const Mat3 T2 = translate(Rx / 2 + Rcx, Rcy - Ry / 2);

            initT = T2 * (S1 * T1);
            T = initT;
        }
        if (IsKeyPressed(KEY_J)) {
            T = translate(Rcx, Rcy) * mirrorX() * translate(-Rcx, -Rcy) * T;
        }
        if (GuiButton({Wx - 140, 20, 120, 30}, "OPEN FILE")) {
            nfdchar_t *outPath;
            nfdfilteritem_t filterItem[2] = {{"Text files", "txt"},
                                             {"All files", "*"}};
            nfdresult_t result =
                NFD_OpenDialog(&outPath, filterItem, 2, nullptr);
            if (result == NFD_OKAY) {
                currentFigure = readFromFile(outPath);

                float rectAspect = Rx / Ry;
                const float figureAspect = currentFigure.Vx / currentFigure.Vy;
                float S =
                    figureAspect < rectAspect ? Ry / figure.Vy : Rx / figure.Vx;

                const Mat3 T1 =
                    translate(-currentFigure.Vx / 2, -currentFigure.Vy / 2);
                const Mat3 S1 = scale(S, -S);
                const Mat3 T2 = translate(Rx / 2 + Rcx, Rcy - Ry / 2);

                initT = T2 * (S1 * T1);
                T = initT;

                NFD_FreePath(outPath);
            } else if (result == NFD_CANCEL) {
                std::cerr << "INFO: NFD: user pressed cancel" << std::endl;

            } else {
                std::cerr << "ERROR: " << NFD_GetError() << std::endl;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    NFD_Quit();
    return 0;
}
