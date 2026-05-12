#include "matrix.hpp"
#include <math.h>

inline Mat3 translate(float Tx, float Ty) {
    Mat3 res = Mat3(1.f);
    res[0][2] = Tx;
    res[1][2] = Ty;
    return res;
}

inline Mat3 scale(float Sx, float Sy) {
    Mat3 res = Mat3(1.f);
    res[0][0] = Sx;
    res[1][1] = Sy;
    return res;
}

inline Mat4 translate(float Tx, float Ty, float Tz) {
    Mat4 *res = new Mat4(1.f); // создали единичную матрицу
    (*res)[0][3] = Tx;         // поменяли
    (*res)[1][3] = Ty;         // значения в последнем столбце
    (*res)[2][3] = Tz;         //
    return *res;
}

inline Mat4 scale(float Sx, float Sy, float Sz) {
    Mat4 *res = new Mat4(1.f); // создали единичную матрицу
    (*res)[0][0] = Sx;         // поменяли
    (*res)[1][1] = Sy;         // значения на главной диагонали
    (*res)[2][2] = Sz;
    return *res;
}

inline Mat3 scale(float S) { return scale(S, S); }

inline Mat3 rotate(float theta) {
    Mat3 res = Mat3(1.f);
    res[0][0] = static_cast<float>(cos(theta));
    res[1][1] = res[0][0];
    res[0][1] = static_cast<float>(-sin(theta));
    res[1][0] = -res[0][1];
    return res;
}

// Зеркальное отражение относительно оси Ox (меняем знак Y)
inline Mat3 mirrorX() {
    Mat3 res = Mat3(1.f);
    res[1][1] = -1.f;
    return res;
}

// Зеркальное отражение относительно оси Oy (меняем знак X)
inline Mat3 mirrorY() {
    Mat3 res = Mat3(1.f);
    res[0][0] = -1.f;
    return res;
}

inline Mat4 rotate(float theta, Vec3 n) {
    Vec3 normalized = norm(n);

    Mat3 E(1.0f);
    Mat3 K = crossM(normalized);

    Mat3 R = E + (K * sinf(theta)) + (K * K * (1.0f - cosf(theta)));

    return Mat4(Vec4(R.row1, 0.0f), Vec4(R.row2, 0.0f), Vec4(R.row3, 0.0f),
                Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

inline Mat4 rotateP(float theta, Vec3 n, Vec3 P) {
    return translate(P.x, P.y, P.z) *
           (rotate(theta, n) * translate(-P.x, -P.y, -P.z));
}

inline Mat4 lookAt(Vec3 S, Vec3 P, Vec3 u) {
    Mat4 T = Mat4(Vec4(1, 0, 0, -S.x), Vec4(0, 1, 0, -S.y), Vec4(0, 0, 1, -S.z),
                  Vec4(0, 0, 0, 1));
    Vec3 Ups = (S - P);
    Vec3 e_3 = norm(Ups);
    Vec3 e_1 = norm(cross(u, e_3));
    Vec3 e_2 = norm(cross(e_3, e_1));
    Mat4 R = Mat4(Vec4(e_1, 0), Vec4(e_2, 0), Vec4(e_3, 0), Vec4(0, 0, 0, 1));
    return R * T;
}

inline Mat4 ortho(float l, float r, float b, float t, float zn, float zf) {
    return Mat4(Vec4(2.f / (r - l), 0.f, 0.f, -(r + l) / (r - l)),
                Vec4(0.f, 2.f / (t - b), 0.f, -(t + b) / (t - b)),
                Vec4(0.f, 0.f, -2 / (zf - zn), -(zf + zn) / (zf - zn)),
                Vec4(0.f, 0.f, 0.f, 1.f));
}

inline Mat4 frustum(float l, float r, float b, float t, float n, float f) {
    return Mat4(Vec4((2 * n) / (r - l), 0, (r + l) / (r - l), 0),
                Vec4(0, (2 * n) / (t - b), (t + b) / (t - b), 0),
                Vec4(0, 0, -(f + n) / (f - n), (-2 * f * n) / (f - n)),
                Vec4(0, 0, -1, 0));
}

inline float cot(float rad) { return 1.0f / tanf(rad); }

inline Mat4 perspective(float fovy, float aspect, float n, float f) {
    return Mat4(Vec4(1 / aspect * cot(fovy / 2), 0, 0, 0),
                Vec4(0, cot(fovy / 2), 0, 0),
                Vec4(0, 0, -(f + n) / (f - n), (-2 * f * n) / (f - n)),
                Vec4(0, 0, -1, 0));
}

inline Mat3 cadrRL(Vec2 Vc, Vec2 V, Vec2 Wc, Vec2 W) {
    return translate(Wc.x, Wc.y) *
           (scale(W.x / V.x, -W.y / V.y) * translate(-Vc.x, -Vc.y));
}
