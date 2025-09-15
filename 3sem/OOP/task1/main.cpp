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

        bool operator==(complexNumber &num);
        bool operator!=(complexNumber &num);

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

bool complexNumber::operator!=(complexNumber &num) {
    return !equal(r, num.radius()) ||
           !equal(sin(phi),
                  sin(num.angle()) || !equal(cos(phi), cos(num.angle())));
}

bool complexNumber::operator==(complexNumber &num) {
    return equal(r, num.radius()) && equal(sin(phi), sin(num.angle())) &&
           equal(cos(phi), cos(num.angle()));
}

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
        void erase(node *node);
        node *begin();
        node *end();

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

node *List::begin() { return head; }
node *List::end() { return tail; }

void List::erase(node *node) {
    if (head == node && tail == node) {
        head = tail = NULL;
    } else if (node == head) {
        head = head->next;
        head->prev = NULL;
    } else if (node == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
    delete node;
}

int main() {
    List l = List();
    complexNumber a = complexNumber();
    complexNumber b = complexNumber(1, 2);
    complexNumber c = complexNumber(2, M_PI / 4);

    l.push(&a);
    l.push(&b);
    l.push(&c);
}
