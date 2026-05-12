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
        // std::cout << "max_y: " << screen.max_y << std::endl;
        screen.key_handler();

        BeginDrawing();
        ClearBackground(SKYBLUE);

        DrawRectangleLinesEx({screen.left, screen.top, screen.border_width,
                              screen.border_height},
                             2, BLACK);

        // for (const auto &model : models) {
        //     // std::cout << "dasdasd" << std::endl;
        //     std::vector<ssu::Path> figure = model.figure;
        //     Mat3 TM = screen.T * model.ModelM;
        //     for (const auto &lines : figure) {
        //         Vec2 start = normalize(TM * Vec3(lines.vertices[0], 1));
        //         for (const auto &line : lines.vertices) {
        //             Vec2 end = normalize(TM * Vec3(line, 1));
        //             Vec2 tmp_end = end;
        //             if (clip(start, end, screen.min_x, screen.min_y,
        //                      screen.max_x, screen.max_y)) {
        //                 std::cout << "x: " << start.x << " y: " << start.y
        //                           << std::endl;
        //                 DrawLineEx({start.x, start.y}, {end.x, end.y},
        //                            lines.thickness, lines.color);
        //             }
        //             start = tmp_end;
        //         }
        //     }
        // }

        for (const auto &model : models) {
            Mat3 TM = screen.T * model.ModelM;
            for (const auto &lines : model.figure) {
                Vec2 start = normalize(TM * Vec3(lines.vertices[0], 1));
                std::cout << lines.vertices.size() << std::endl;
                for (const auto &line : lines.vertices) {
                    Vec2 end = normalize(TM * Vec3(line, 1));
                    Vec2 tmpEnd = end;

                    std::cout << "x: " << start.x << " y: " << start.y
                              << std::endl;
                    if (clip(start, end, screen.min_x, screen.min_y,
                             screen.max_x, screen.max_y)) {
                        DrawLineEx({start.x, start.y}, {end.x, end.y},
                                   lines.thickness, lines.color);
                    }
                    start = tmpEnd;
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
