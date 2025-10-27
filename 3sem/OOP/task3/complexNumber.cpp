#include <cmath>
#include <iostream>

bool equal(double a, double b) {
    double eps = 0.0000000000001;
    return std::abs(a - b) < eps;
}

class complexNumber {
    public:
        complexNumber(double r, double phi);
        complexNumber();

        double radius();
        double angle();
        double getRe();
        double getIm();
        bool getIsExtended();

        void setRadius(double r);
        void setAngle(double phi);

        void print();

        ~complexNumber();

        bool operator==(complexNumber &num);
        bool operator!=(complexNumber &num);
        complexNumber operator+(complexNumber &num);
        complexNumber operator-();
        complexNumber operator-(complexNumber &num);
        complexNumber operator*(complexNumber &num);
        complexNumber operator/(complexNumber &num);

    private:
        void setRe();
        void setIm();
        double re;
        double im;
        double r;
        double phi;
};

complexNumber complexNumber::operator*(complexNumber &num) {
    double newRadius = std::abs(r * num.radius());
    double newAngle = phi + num.phi;
    return complexNumber(newRadius, newAngle);
}

complexNumber complexNumber::operator/(complexNumber &num) {
    if (equal(num.radius(), 0)) {
        std::cerr << "Division by zero" << std::endl;
        std::abort();
    }

    double newRadius = std::abs(r / num.radius());
    double newAngle = phi - num.phi;
    return complexNumber(newRadius, newAngle);
}

void complexNumber::setRe() { re = r * cos(phi); }
void complexNumber::setIm() { im = r * sin(phi); }

// Конструктор complexNumber
complexNumber::complexNumber(double R, double Phi) {
    try {
        setRadius(R);
    } catch (std::invalid_argument &error) {
        std::cerr << error.what() << std::endl;
    }

    setAngle(Phi);
    setRe();
    setIm();
}

// Конструктор complexNumber
complexNumber::complexNumber() {
    setRadius(0.0);
    setAngle(0.0);
    setRe();
    setIm();
}

// Деконструктор complexNumber
complexNumber::~complexNumber() {}

// Перегрузка бинарного оператора - для complexNumber
complexNumber complexNumber::operator-() {
    return complexNumber(r, phi + M_PI);
}

// Возвращает радиус у complexNumber
double complexNumber::radius() { return r; }

// Возвращает угол у complexNumber
double complexNumber::angle() { return phi; }

// Возвращает реальную часть complexNumber в алгебраическом виде
double complexNumber::getRe() { return re; }

// Возвращает мнимую часть complexNumber в алгебраическом виде
double complexNumber::getIm() { return im; }

// Сеттер атрибута phi
void complexNumber::setAngle(double Phi) {
    if (std::abs(Phi) > M_PI * 2) {
        throw Phi;
    }
    phi = Phi;
}
// Сеттер атрибута r. Вызовёт исключение invalid_argument, если R < 0
void complexNumber::setRadius(double R) {
    if (R < 0) {
        throw R;
    }
    r = R;
}

// Печатает complexNumber в виде (радиус, угол)
void complexNumber::print() { std::cout << "(" << r << ", " << phi << ")"; }

// Перегруженный бинарный оператор != для complexNumber
bool complexNumber::operator!=(complexNumber &num) {
    return !equal(r, num.radius()) ||
           !equal(sin(phi),
                  sin(num.angle()) || !equal(cos(phi), cos(num.angle())));
}

// Перегруженный бинарный оператор == для complexNumber
bool complexNumber::operator==(complexNumber &num) {
    double sin1 = sin(phi);
    double sin2 = sin(num.angle());

    double cos1 = cos(phi);
    double cos2 = cos(num.angle());
    return equal(r, num.radius()) && equal(sin1, sin2) && equal(cos1, cos2);
}

// Перегруженный бинарный оператор - для complexNumber
complexNumber complexNumber::operator-(complexNumber &num) {
    double r2 = num.radius();
    double phi2 = num.angle();
    double r3 = std::sqrt(
        (r * cos(phi) - r2 * cos(phi2)) * (r * cos(phi) - r2 * cos(phi2)) +
        (r * sin(phi) - r2 * sin(phi2)) * (r * sin(phi) - r2 * sin(phi2)));
    double phi3 =
        atan2((r * sin(phi) - r2 * sin(phi2)), (r * cos(phi) - r2 * cos(phi2)));
    return complexNumber(r3, phi3);
}

// Перегруженный бинарный оператор + для complexNumber
complexNumber complexNumber::operator+(complexNumber &num) {
    double r2 = num.radius();
    double phi2 = num.angle();
    double r3 = std::sqrt(
        (r * cos(phi) + r2 * cos(phi2)) * (r * cos(phi) + r2 * cos(phi2)) +
        (r * sin(phi) + r2 * sin(phi2)) * (r * sin(phi) + r2 * sin(phi2)));
    double phi3 =
        atan2((r * sin(phi) + r2 * sin(phi2)), (r * cos(phi) + r2 * cos(phi2)));
    return complexNumber(r3, phi3);
}
