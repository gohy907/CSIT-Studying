#include <iostream>

class complexNumber {
    public:
        complexNumber(double r, double phi);
        complexNumber();

        double radius();
        double angle();

        void setRaidus(double r);
        void setAngle(double phi);

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

int main() {
    complexNumber a = complexNumber();
    std::cout << a.radius() << std::endl;
}
