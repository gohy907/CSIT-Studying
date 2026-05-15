#include "clip.hpp"
#include "figure.hpp"
#include "matrix.hpp"
#include "screen.hpp"
#include <nfd.h>
#include <raygui.h>
#include <raylib.h>

#include <iostream>

bool isIgnorableLine(const std::string &line) {
    return line.find_first_not_of(" \t\r\n") == std::string::npos ||
           line.front() == '#';
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

    Screen screen;

    std::vector<ssu::Model> models;

    while (!WindowShouldClose()) {
        float screen_width = static_cast<float>(GetScreenWidth());
        float screen_height = static_cast<float>(GetScreenHeight());
        screen.calculate_borders(screen_width, screen_height);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        DrawRectangleLinesEx({screen.left, screen.top, screen.border_width,
                              screen.border_height},
                             2, BLACK);
        screen.key_handler();

        Mat4 proj = Mat4(1.f);
        switch (screen.pType) {
        case Screen::projType::Ortho: // прямоугольная проекция
            proj = ortho(screen.l, screen.r, screen.b, screen.t, -screen.n,
                         -screen.f);
            break;
        case Screen::projType::Frustum: // перспективная проекция с Frustum
            proj = frustum(screen.l, screen.r, screen.b, screen.t, screen.n,
                           screen.f);
            break;
        case Screen::projType::Perspective: // перспективная проекция с
                                            // Perspective
            proj = perspective(screen.fovy_work, screen.aspect_work, screen.n,
                               screen.f);
            break;
        }
        // WARNING: возможно тут жёсткие хихи хаха
        Mat3 cdr = cadrRL(Vec2(-1.f, -1.f), Vec2(2.f, 2.f),
                          Vec2(screen.Wcx, screen.Wcy),
                          Vec2(screen.border_width, screen.border_height));
        Mat4 C = proj * screen.T;
        for (const auto &model : models) {
            std::vector<ssu::Path> figure = model.figure;
            Mat4 TM = C * model.ModelM;
            for (const auto &lines : figure) {
                Vec3 start_ndc = normalize(TM * Vec4(lines.vertices[0], 1));
                Vec3 tmp_s = cdr * Vec3(start_ndc.x, start_ndc.y, 1.f);
                Vec2 start = {tmp_s.x, tmp_s.y};
                // std::cout << "x: " << tmp_s.x << ", y: " << tmp_s.y
                //           << std::endl;

                for (size_t i = 1; i < lines.vertices.size(); ++i) {
                    const auto &vertex = lines.vertices[i];

                    Vec3 end_ndc = normalize(TM * Vec4(vertex, 1));
                    Vec3 tmp_e = cdr * Vec3(end_ndc.x, end_ndc.y, 1.f);
                    Vec2 end = {tmp_e.x, tmp_e.y};

                    Vec2 next_start = end;
                    Vec3 next_start_ndc = end_ndc;

                    Vec2 s_copy = start;
                    Vec2 e_copy = end;
                    if (clip(s_copy, e_copy, screen.min_x, screen.min_y,
                             screen.max_x, screen.max_y)) {
                        DrawLineEx({s_copy.x, s_copy.y}, {e_copy.x, e_copy.y},
                                   lines.thickness, lines.color);
                    }

                    start = next_start;
                    start_ndc = next_start_ndc;
                }
            }
        }

        if (GuiButton({screen_width - 140, 20, 120, 30}, "OPEN FILE")) {
            nfdchar_t *outPath;
            nfdfilteritem_t filterItem[2] = {{"Text files", "txt"},
                                             {"All files", "*"}};
            nfdresult_t result =
                NFD_OpenDialog(&outPath, filterItem, 2, nullptr);
            if (result == NFD_OKAY) {
                models = screen.get_models_from_file(outPath);
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
