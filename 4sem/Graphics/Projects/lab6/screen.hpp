#pragma once

#include <fstream>
#include <sstream>
#include <vector>

#include "figure.hpp"
#include "raylib.h"
#include "transform.hpp"
#include <iostream>

struct Screen {
        // Расстояния рамки до границ окна
        const float left = 30;
        const float right = 140;
        const float top = 20;
        const float bottom = 50;

        // Границы отрисовки в рамке
        float min_x = left;
        float min_y = top;
        float max_x; // Вот эти значения зависят от размера окна и будут
                     // вычислены позже
        float max_y;

        float border_width;
        float border_height;

        float Wcx = left;
        float Wcy;
        // Центер рамки в мировых координатах
        float rect_center_x;
        float rect_center_y;

        float rect_aspect;

        enum projType { Ortho, Frustum, Perspective } pType = Perspective;

        Mat4 initT = Mat4(1.f); // Матрица изначального преобразования
        Mat4 T = Mat4(1.f);

        Vec3 S, P, u; // координаты точки наблюдения
        // точки, в которую направлен вектор наблюдения
        // вектора направления вверх
        float dist; // вспомогательная переменная - расстояние между S и P
        float fovy, aspect; // угол обзора и соотношение сторон окна наблюдения
        float fovy_work, aspect_work; // рабочие переменные для fovy и aspect
        float near, far;  // расстояния до окна наблюдения и до горизонта
        float n, f;       // рабочие переменные для near и far
        float l, r, t, b; // рабочие вспомогательные переменные
                          // для значений координат левой, правой,
                          // нижней и верхней координаты в СКН

        void calculate_borders(float screen_width, float screen_height) {
            border_width = screen_width - left - right;
            border_height = screen_height - top - bottom;

            rect_center_x = border_width / 2.0f + left;
            rect_center_y = border_height / 2.0f + top;

            max_x = screen_width - right;
            max_y = screen_height - bottom;

            rect_aspect = border_width / border_height;

            Wcy = max_y;
        }

        bool is_ignorable_line(const std::string &line) {
            return line.find_first_not_of(" \t\r\n") == std::string::npos ||
                   line.front() == '#';
        }

        std::vector<ssu::Model> get_models_from_file(const char *file_name);
        void key_handler();

    private:
        void initWorkPars() { // инициализация рабочих параметров камеры
            n = near;
            f = far;
            fovy_work = fovy;
            aspect_work = aspect;
            float Vy = 2 * near * tan(fovy / 2);
            float Vx = aspect * Vy;
            l = -Vx / 2;
            r = Vx / 2;
            b = -Vy / 2;
            t = Vy / 2;
            dist = length(P - S);
            T = lookAt(S, P, u);
        }
};

std::vector<ssu::Model> Screen::get_models_from_file(const char *file_name) {
    std::vector<ssu::Model> models;
    std::ifstream in;

    in.open(file_name);

    if (in.is_open()) {
        Mat4 M = Mat4(1.f); // Модельная матрица
        Mat4 initM;         // Матрица с начальным преобразованием каждой модели
        std::vector<Mat4> transforms;  // Стек преобразований
        std::vector<ssu::Path> figure; // Ломаные, из которых состоит фигура
        float thickness = 2;
        int r = 0;
        int g = 0;
        int b = 0;
        std::string str;
        std::string cmd;
        float Vx, Vy;
        getline(in, str);

        while (in) {
            if (!is_ignorable_line(str)) {
                std::stringstream s(str);
                s >> cmd;
                if (cmd == "camera") {
                    s >> S.x >> S.y >> S.z; // координаты точки наблюдения
                    s >> P.x >> P.y >>
                        P.z; // точка, в которую направлен вектор наблюдения
                    s >> u.x >> u.y >> u.z; // вектор направления вверх

                } else if (cmd == "screen") {
                    s >> fovy_work >> aspect >> near >>
                        far; // параметры команды
                    fovy = fovy_work / 180.f *
                           PI; // перевод угла из градусов в радианты

                } else if (cmd == "color") { // цвет линии
                    s >> r >> g >> b;        // считываем три составляющие цвета

                } else if (cmd == "thickness") { // толщина линии
                    s >> thickness;              // считываем значение толщины

                } else if (cmd == "path") {     // набор точек
                    std::vector<Vec3> vertices; // список точек ломаной
                    int N;                      // количество точек
                    s >> N;
                    std::string str1; // дополнительная строка для
                                      // чтения из файла
                    while (N > 0) {   // пока не все точки считали
                        getline(in,
                                str1); // считываем в str1 из входного
                                       // файла очередную строку
                        // так как файл корректный, то на конец файла
                        // проверять не нужно
                        if (!is_ignorable_line(str1)) {
                            // прочитанная строка не пуста и не
                            // комментарий
                            // значит в ней пара координат
                            float x, y, z; // переменные для считывания
                            std::stringstream s1(str1); // еще один строковый
                                                        // поток из строки str1
                            s1 >> x >> y >> z;
                            vertices.push_back(
                                Vec3(x, y, z)); // добавляем точку в список
                            N--; // уменьшаем счетчик после успешного
                                 // считывания точки
                        }
                    }
                    // все точки считаны, генерируем ломаную (path) и
                    // кладем ее в список figure
                    Color color = Color{static_cast<unsigned char>(r),
                                        static_cast<unsigned char>(g),
                                        static_cast<unsigned char>(b), 255};
                    figure.push_back(ssu::Path(vertices, color, thickness));
                } else if (cmd == "model") { // начало описания нового рисунка
                    float mVcx, mVcy, mVx, mVy, mVcz,
                        mVz; // параметры команды model
                    s >> mVcx >> mVcy >> mVcz >> mVx >> mVy >>
                        mVz; // считываем значения переменных
                    float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
                    // сдвиг точки привязки из начала координат в
                    // нужную позицию
                    // после которого проводим масштабирование
                    initM = scale(S, S, S) * translate(-mVcx, -mVcy, -mVcz);
                    figure.clear();

                } else if (cmd == "figure") { // формирование новой модели
                    models.push_back(ssu::Model(figure, M * initM));

                } else if (cmd == "translate") { // перенос
                    float Tx, Ty, Tz;    // параметры преобразования переноса
                    s >> Tx >> Ty >> Tz; // считываем параметры
                    M = translate(Tx, Ty, Tz) *
                        M; // добавляем перенос к общему преобразованию

                } else if (cmd == "scale") { // масштабирование
                    float S;                 // параметр масштабирования
                    s >> S;                  // считываем параметр
                    M = scale(S, S, S) * M;  // добавляем масштабирование к
                                             // общему преобразованию

                } else if (cmd == "rotate") { // поворот
                    float theta;              // угол поворота в градусах
                    float nx, ny, nz;
                    s >> theta >> nx >> ny >> nz; // считываем параметр
                    M = rotate(theta / 180.f * PI, Vec3(nx, ny, nz)) *
                        M; // добавляем поворот к общему преобразованию
                } else if (cmd == "pushTransform") { // сохранение
                                                     // матрицы в стек
                    transforms.push_back(M);         // сохраняем матрицу в стек

                } else if (cmd == "popTransform") { // откат к матрице
                                                    // из стека
                    M = transforms.back(); // получаем верхний элемент стека
                    transforms.pop_back(); // выкидываем матрицу из стека
                }
            }
            // считываем очередную строку
            getline(in, str);
        }
        initWorkPars();
    }
    return models;
}

inline void Screen::key_handler() {
    if (IsKeyDown(KEY_W)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {

            T = lookAt(Vec3(0, 0, -0.1), Vec3(0, 0, -0.2), Vec3(0, 1, 0)) * T;
        } else {
            T = lookAt(Vec3(0, 0, -1), Vec3(0, 0, -2), Vec3(0, 1, 0)) * T;
        }
    }

    if (IsKeyDown(KEY_A)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            T = lookAt(Vec3(-0.1, 0, 0), Vec3(-0.1, 0, -0.1), Vec3(0, 1, 0)) *
                T;
        } else {
            T = lookAt(Vec3(-1, 0, 0), Vec3(-1, 0, -1), Vec3(0, 1, 0)) * T;
        }
    }
    if (IsKeyDown(KEY_S)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {

            T = lookAt(Vec3(0, 0, 0.1), Vec3(0, 0, 0), Vec3(0, 0.1, 0)) * T;
        } else {
            T = lookAt(Vec3(0, 0, 1), Vec3(0, 0, 0), Vec3(0, 1, 0)) * T;
        }
    }
    if (IsKeyDown(KEY_D)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {

            T = lookAt(Vec3(0.1, 0, 0), Vec3(0.1, 0, -0.1), Vec3(0, 0.1, 0)) *
                T;
        } else {
            T = lookAt(Vec3(1, 0, 0), Vec3(1, 0, -1), Vec3(0, 1, 0)) * T;
        }
    }

    if (IsKeyDown(KEY_ESCAPE)) {
        initWorkPars();
        // T = initT;
    }
    if (IsKeyPressed(KEY_THREE)) {
        pType = Perspective;
    }

    if (IsKeyPressed(KEY_ONE)) {
        pType = Ortho;
    }
    if (IsKeyPressed(KEY_TWO)) {
        pType = Frustum;
        // T = frustum(l, r, b, t, n, f) * T;
    }
    if (IsKeyPressed(KEY_THREE)) {
        pType = Perspective;
    }

    if (IsKeyDown(KEY_R)) {

        Vec3 u_new = Mat3(rotate(0.1, Vec3(0, 0, 1))) * Vec3(0, 1, 0);
        T = lookAt(Vec3(0, 0, 0), Vec3(0, 0, -1), u_new) * T;
    }

    if (IsKeyDown(KEY_Y)) {

        Vec3 u_new = Mat3(rotate(-0.1, Vec3(0, 0, 1))) * Vec3(0, 1, 0);
        T = lookAt(Vec3(0, 0, 0), Vec3(0, 0, -1), u_new) * T;
    }
    if (IsKeyDown(KEY_T)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            Mat4 M = rotateP(
                0.1, Vec3(1, 0, 0),
                Vec3(0, 0, -dist)); // матрица вращения относительно точки P
            Vec3 u_new = Mat3(M) * Vec3(0, 1, 0); // вращение направления вверх
            Vec3 S_new =
                normalize(M * Vec4(0, 0, 0, 1)); // вращение начала координат
            // переход к СКН в которой начало координат в новой точке, а
            // направление наблюдения - в точку P
            T = lookAt(S_new, Vec3(0, 0, -dist), u_new) * T;
        } else {
            Mat4 M =
                rotate(0.1, Vec3(1, 0, 0)); // матрица вращения относительно Ox
            Vec3 u_new = Mat3(M) * Vec3(0, 1, 0); // вращение направления вверх
            Vec3 P_new = normalize(
                M * Vec4(0, 0, -1,
                         1)); // вращение точки, в которую смотрит наблюдатель
            T = lookAt(Vec3(0, 0, 0), P_new, u_new) * T;
        }
    }

    if (IsKeyDown(KEY_I)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            --t;
        } else {
            ++t;
        }
    }

    if (IsKeyDown(KEY_J)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            --l;
            ;
        } else {
            ++l;
        }
    }

    if (IsKeyDown(KEY_G)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            T = rotateP(0.1f, Vec3(1, 0, 0), P) * T;
        } else {
            T = rotate(0.1f, Vec3(1, 0, 0)) * T;
        }
    }
    if (IsKeyDown(KEY_F)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            T = rotateP(-0.1f, Vec3(0, 1, 0), P) * T;
        } else {
            T = rotate(-0.1f, Vec3(0, 1, 0)) * T;
        }
    }
    if (IsKeyDown(KEY_H)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            T = rotateP(0.1f, Vec3(0, 1, 0), P) * T;
        } else {
            T = rotate(0.1f, Vec3(0, 1, 0)) * T;
        }
    }

    if (IsKeyDown(KEY_K)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            b -= 1.0f;
        } else {
            b += 1.0f;
        }
    }
    if (IsKeyDown(KEY_L)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            r -= 1.0f;
        } else {
            r += 1.0f;
        }
    }
    if (IsKeyDown(KEY_U)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            n -= 0.2f;
        } else {
            n += 0.2f;
        }
        n = std::max(0.1f, n);
        n = std::min(n, f - 0.1f);
    }
    if (IsKeyDown(KEY_O)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            f -= 0.2f;
        } else {
            f += 0.2f;
        }
        f = std::max(n + 0.1f, f);
    }
    if (IsKeyDown(KEY_B)) {
        Vec3 view_dir = norm(P - S);
        float step = 0.2f;
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            if (length(P - S) - step >= 0.1f) {
                S += view_dir * step;
                initWorkPars();
            }
        } else {
            S -= view_dir * step;
            initWorkPars();
        }
    }
    if (IsKeyDown(KEY_Z)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            fovy_work -= 0.1f;
        } else {
            fovy_work += 0.1f;
        }
        fovy_work = std::max(0.3f, fovy_work);
        fovy_work = std::min(3.0f, fovy_work);
    }
    if (IsKeyDown(KEY_X)) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            aspect_work -= 0.05f;
        } else {
            aspect_work += 0.05f;
        }
        aspect_work = std::max(0.01f, aspect_work);
    }
}

// enum projType { Ortho, Frustum, Perspective } pType;
