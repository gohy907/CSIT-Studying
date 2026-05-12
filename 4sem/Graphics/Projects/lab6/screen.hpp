#pragma once

#include <fstream>
#include <sstream>
#include <vector>

#include "figure.hpp"
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

        Mat3 initT; // Матрица изначального преобразования
        Mat3 T = Mat3(1.f);

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
};

std::vector<ssu::Model> Screen::get_models_from_file(const char *file_name) {
    std::vector<ssu::Model> models;
    std::ifstream in;

    in.open(file_name);

    if (in.is_open()) {
        Mat3 M = Mat3(1.f); // Модельная матрица
        Mat3 initM;         // Матрица с начальным преобразованием каждой модели
        std::vector<Mat3> transforms;  // Стек преобразований
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
                if (cmd == "frame") { // размеры изображения
                    s >> Vx >> Vy;    // считываем глобальные значение Vx и Vy
                    std::cout << Vx << " " << Vy << std::endl;
                    float figure_aspect =
                        Vx / Vy; // обновление соотношения сторон
                    // смещение центра рисунка с началом координат
                    Mat3 T1 = translate(-Vx / 2.0f, -Vy / 2.0f);
                    // масштабирование остается прежним, меняется
                    // только привязка
                    // коэффициент увеличения при сохранении
                    // исходного соотношения сторон
                    float S = figure_aspect < rect_aspect ? (border_height / Vy)
                                                          : (border_width / Vx);
                    Mat3 S1 = scale(S, -S);
                    // сдвиг точки привязки из начала координат в
                    // нужную позицию
                    Mat3 T2 = translate(Wcx + border_width / 2.0f,
                                        Wcy - border_height / 2.0f);

                    // Mat3 T2 = translate(left, top);
                    // В initT совмещаем эти три преобразования
                    // (справа налево)
                    initT = T2 * (S1 * T1);
                    T = initT;
                    std::cout << T.row1.x << " " << T.row1.y << " " << T.row1.z
                              << std::endl;
                    std::cout << T.row2.x << " " << T.row2.y << " " << T.row2.z
                              << std::endl;
                    std::cout << T.row3.x << " " << T.row3.y << " " << T.row3.z
                              << std::endl;
                    std::cout << std::endl;

                } else if (cmd == "color") { // цвет линии
                    s >> r >> g >> b;        // считываем три составляющие цвета

                } else if (cmd == "thickness") { // толщина линии
                    s >> thickness;              // считываем значение толщины

                } else if (cmd == "path") {     // набор точек
                    std::vector<Vec2> vertices; // список точек ломаной
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
                            float x,
                                y; // переменные для считывания
                            std::stringstream s1(str1); // еще один строковый
                                                        // поток из строки str1
                            s1 >> x >> y;
                            vertices.push_back(
                                Vec2(x, y)); // добавляем точку в список
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
                    float mVcx, mVcy, mVx,
                        mVy; // параметры команды model
                    s >> mVcx >> mVcy >> mVx >>
                        mVy; // считываем значения переменных
                    float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
                    // сдвиг точки привязки из начала координат в
                    // нужную позицию
                    // после которого проводим масштабирование
                    initM = scale(S) * translate(-mVcx, -mVcy);
                    figure.clear();

                } else if (cmd == "figure") { // формирование новой модели
                    models.push_back(ssu::Model(figure, M * initM));

                } else if (cmd == "translate") { // перенос
                    float Tx,
                        Ty;        // параметры преобразования переноса
                    s >> Tx >> Ty; // считываем параметры
                    M = translate(Tx, Ty) *
                        M; // добавляем перенос к общему преобразованию

                } else if (cmd == "scale") { // масштабирование
                    float S;                 // параметр масштабирования
                    s >> S;                  // считываем параметр
                    M = scale(S) * M;        // добавляем масштабирование к
                                             // общему преобразованию

                } else if (cmd == "rotate") { // поворот
                    float theta;              // угол поворота в градусах
                    s >> theta;               // считываем параметр
                    M = rotate(-theta / 180.f * PI) *
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
    }
    return models;
}

void Screen::key_handler() {
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
        T = translate(rect_center_x, rect_center_y) * rotate(-0.01f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyDown(KEY_E)) {
        T = translate(rect_center_x, rect_center_y) * rotate(0.01f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyDown(KEY_Y)) {
        T = translate(rect_center_x, rect_center_y) * rotate(-0.05f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyDown(KEY_R)) {
        T = translate(rect_center_x, rect_center_y) * rotate(0.05f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }

    if (IsKeyDown(KEY_Z)) {
        T = translate(rect_center_x, rect_center_y) * scale(1.1f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyDown(KEY_X)) {
        T = translate(rect_center_x, rect_center_y) * scale(1.0f / 1.1f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }

    if (IsKeyDown(KEY_I)) {
        T = translate(rect_center_x, rect_center_y) * scale(1.1f, 1.0f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyDown(KEY_K)) {
        T = translate(rect_center_x, rect_center_y) * scale(1.0f / 1.1f, 1.0f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyDown(KEY_O)) {
        T = translate(rect_center_x, rect_center_y) * scale(1.0f, 1.1f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyDown(KEY_L)) {
        T = translate(rect_center_x, rect_center_y) * scale(1.0f, 1.0f / 1.1f) *
            translate(-rect_center_x, -rect_center_y) * T;
    }

    if (IsKeyPressed(KEY_U)) {
        T = translate(rect_center_x, rect_center_y) * mirrorY() *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyPressed(KEY_J)) {
        T = translate(rect_center_x, rect_center_y) * mirrorX() *
            translate(-rect_center_x, -rect_center_y) * T;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        T = initT;
    }
}
