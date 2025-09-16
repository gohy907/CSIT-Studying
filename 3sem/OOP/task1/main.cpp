#include <algorithm>
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
        complexNumber operator+(complexNumber &num);
        complexNumber operator-();
        complexNumber operator-(complexNumber &num);

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

complexNumber complexNumber::operator-() {
    return complexNumber(r, phi + M_PI);
}

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

class node {
    public:
        node(complexNumber *Inf, node *Next, node *Prev);
        complexNumber operator*();
        void operator=(complexNumber num);
        node *getNext();
        node *getPrev();
        void setNext(node *node);
        void setPrev(node *node);

    private:
        complexNumber *inf;
        node *nextNode;
        node *prevNode;
};

complexNumber node::operator*() { return *inf; }
void node::operator=(complexNumber num) { inf = &num; }

node::node(complexNumber *Inf, node *next, node *prev) {
    inf = Inf;
    nextNode = next;
    prevNode = prev;
}

node *node::getNext() { return nextNode; }
node *node::getPrev() { return prevNode; }

void node::setNext(node *node) { nextNode = node; }
void node::setPrev(node *node) { prevNode = node; }

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
    node r = node(num, NULL, NULL);
    r.setNext(NULL);
    if (!head && !tail) {
        r.setPrev(NULL);
        head = &r;
    } else {
        tail->setNext(&r);
        r.setPrev(tail);
    }
    tail = &r;
}

void List::print() {
    node *r = head;
    while (r != NULL) {
        complexNumber num = **r;
        num.print();
        r = r->getNext();
        std::cout << std::endl;
    }
}

bool List::find(complexNumber num) {
    node *r = head;
    while (r != NULL) {
        if (**r == num) {
            return true;
        }
        r = r->getNext();
    }
    return false;
}

node *List::begin() { return head; }
node *List::end() { return tail; }

void List::erase(node *node) {
    if (head == node && tail == node) {
        head = tail = NULL;
    } else if (node == head) {
        head = head->getNext();
        head->setPrev(NULL);
    } else if (node == tail) {
        tail = tail->getPrev();
        tail->setNext(NULL);
    } else {
        node->getNext()->setPrev(node->getPrev());
        node->getPrev()->setNext(node->getNext());
    }
    delete node;
}

int main() {
    List l = List();
    complexNumber a = complexNumber();
    complexNumber b = complexNumber(1, 2);
    complexNumber c = complexNumber(1, M_PI / 3);

    l.push(&a);
    l.push(&b);
    l.push(&c);
    complexNumber d = b - c;
    d.print();
}
