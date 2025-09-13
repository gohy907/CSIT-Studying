#include <cmath>
#include <iostream>

bool equal(double a, double b) {
    double eps = 0.00000000000001;
    return std::abs(a - b) < eps;
}

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

        bool operator==(complexNumber &num) {
            return equal(r, num.radius()) &&
                   equal(sin(phi), sin(num.angle())) &&
                   equal(cos(phi), cos(num.angle()));
        }

        bool operator!=(complexNumber &num) {
            return !equal(r, num.radius()) ||
                   !equal(sin(phi), sin(num.angle()) ||
                                        !equal(cos(phi), cos(num.angle())));
        }

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

void complexNumber::print() { std::cout << "(" << r << ", " << phi << ")"; }

struct node {
        complexNumber *inf;
        node *next;
        node *prev;
};

class List {
    public:
        List();
        void push(complexNumber *num);
        void print();
        bool find(complexNumber num);

    private:
        node *head;
        node *tail;
};

List::List() {
    head = NULL;
    tail = NULL;
}

void List::push(complexNumber *num) {
    node *r = new node;
    r->inf = num;
    r->next = NULL;
    if (!head && !tail) {
        r->prev = NULL;
        head = r;
    } else {
        tail->next = r;
        r->prev = tail;
    }
    tail = r;
}

void List::print() {
    node *r = head;
    while (r != NULL) {
        complexNumber num = *(r->inf);
        num.print();
        r = r->next;
        std::cout << std::endl;
    }
}

bool List::find(complexNumber num) {
    node *r = head;
    while (r != NULL) {
        if (*(r->inf) == num) {
            return true;
        }
        r = r->next;
    }
    return false;
}

int main() {
    List l = List();
    complexNumber a = complexNumber();
    complexNumber b = complexNumber(1, 2);
    complexNumber c = complexNumber(2, M_PI / 4);

    l.push(&a);
    l.push(&b);
    l.push(&c);

    complexNumber d = complexNumber(2, 9 * M_PI / 4);

    std::cout << l.find(d) << std::endl;

    l.print();
}
