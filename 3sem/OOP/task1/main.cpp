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
        void insert(node *node, complexNumber num);
        bool contains(complexNumber num);
        node *find(complexNumber num);
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

void List::insert(node *Node, complexNumber num) {
    node *newNode = new node;
    newNode->inf = &num;
    newNode->next = Node;
    newNode->prev = Node->prev;

    if (Node->prev) {
        Node->prev->next = newNode;
    } else {
        head = newNode;
    }
    Node->prev = newNode;
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

node *List::find(complexNumber num) {
    node *r = head;
    while (r != NULL) {
        if (*(r->inf) == num) {
            return r;
        }
        r = r->next;
    }
    return this->end();
}

bool List::contains(complexNumber num) {
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
    complexNumber a = complexNumber(0, 0);
    complexNumber b = complexNumber(1, 1);
    complexNumber c = complexNumber(2, 2);
    complexNumber d = complexNumber(3, 3);
    l.push(&a);
    l.push(&b);
    l.push(&c);
    l.insert(l.begin()->next, d);
    l.print();
}
