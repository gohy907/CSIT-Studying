#pragma once

#include "matrix.hpp"
#include <raylib.h>
#include <vector>

namespace ssu {

struct Path {
        std::vector<Vec2> vertices;
        Color color;
        float thickness;
        Path(std::vector<Vec2> vertices, Color color, float thickness)
            : vertices(vertices),
              color(color),
              thickness(thickness) {}
};
struct Figure {
        std::vector<Path> paths;
        float Vx;
        float Vy;
        Mat3 modelM;
        Figure() = default;
        Figure(std::vector<Path> paths, float Vx, float Vy)
            : paths(paths),
              Vx(Vx),
              Vy(Vy) {}
};

class Model {
    public:
        std::vector<Path> figure;
        Mat3 ModelM;
        Model() = default;
        Model(std::vector<Path> paths, Mat3 mat)
            : figure(paths),
              ModelM(mat) {}
};

} // namespace ssu
