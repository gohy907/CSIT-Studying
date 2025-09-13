#include <cmath>
#include <iostream>

class complexNumber {
    public:
        complexNumber(double r, double phi);
        complexNumber();

        double radius();
        double angle();
        double re();
        double im();

        void setRaidus(double r);
        void setAngle(double phi);

        void print();

        ~complexNumber();

    private:
        double r;
        double phi;
};

complexNumber::complexNumber(double R, double Phi) {
    r = R;
    phi = Phi;
}
complexNumber::complexNumber() {
    r = 0.0;
    phi = 0.0;
}

complexNumber::~complexNumber() {}

double complexNumber::radius() { return r; }
double complexNumber::angle() { return phi; }
double complexNumber::re() { return r * cos(phi); }
double complexNumber::im() { return r * sin(phi); }

void complexNumber::setAngle(double Phi) { phi = Phi; }
void complexNumber::setRaidus(double R) { r = R; }

int main() {
    complexNumber a = complexNumber(1, 2);
    std::cout << a.angle() << std::endl;
    a.setAngle(5);
    std::cout << a.angle() << std::endl;
}
