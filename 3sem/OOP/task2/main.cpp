#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

bool equal(double a, double b) {
    double eps = 0.0000000000001;
    return std::abs(a - b) < eps;
}

class Figure {
    protected:
        double x;
        double y;
        double z;
        std::string type = "Фигура";
        std::string name = "Безымянная фигура";
        virtual void additionalPrint() {}

    public:
        Figure() {};
        Figure(double x, double y, double z)
            : x(x),
              y(y),
              z(z) {}
        void print() {
            std::cout << "Тип: " << getName() << std::endl
                      << "Имя: " << getType() << std::endl
                      << "Координаты: " << "(" << x << ", " << y << ", " << z
                      << ")" << std::endl;
            additionalPrint();
        }
        virtual std::string getName() { return name; }
        virtual std::string getType() { return type; }
};

struct node {
        Figure *inf;
        node *next;
        node *prev;
};
class List {
    public:
        List();
        ~List();

        void push(Figure num);
        void print();
        void insert(size_t index, Figure num);
        bool contains(Figure num);
        size_t find(Figure num);
        void remove(size_t index);

        node *begin();
        node *end();

        Figure &operator[](size_t index);

        size_t length();

    private:
        node *getNodeByIndex(size_t index);
        void erase(node *node);
        node *head;
        node *tail;
};
List::List() {
    head = NULL;
    tail = NULL;
}

// Деструктор List
List::~List() {}

size_t List::length() {
    node *cur = head;
    size_t length = 0;
    while (cur) {
        ++length;
        cur = cur->next;
    }
    return length;
}

// Вернёт node, находящийся в index-ой ячейке List
// ОСТОРОЖНО! РАБОТАЕТ ЗА ЛИНЕЙНОЕ ВРЕМЯ!
// ВСЕ ЖАЛОБЫ НА ВРЕМЯ РАБОТЫ БУДУТ ПЕРЕАДРЕСОВАНЫ В /dev/null
node *List::getNodeByIndex(size_t index) {
    node *cur = this->begin();

    for (int i = 0; i < index; ++i) {
        if (!cur) {
            throw std::out_of_range("ОШИБКА: Индекс больше длины");
            break;
        }
        cur = cur->next;
    }
    if (!cur) {
        throw std::out_of_range("ОШИБКА: Индекс больше длины");
    }

    return cur;
}

// Вернёт Figure, находящийся в index-ой ячейке List
Figure &List::operator[](size_t index) { return *getNodeByIndex(index)->inf; }

// Печатает на экране все Figure в List, удовлетворящие функции condition
// void List::findAll(bool condition(Figure &num)) {
//     node *cur = head;
//     while (cur) {
//         Figure &curNum = *(cur->inf);
//         if (condition(curNum)) {
//             curNum.print();
//             std::cout << std::endl;
//         }
//         cur = cur->next;
//     }
// }

// Вставляет новый node с inf = num в конец List
void List::push(Figure num) {
    node *r = new node;
    r->inf = new Figure(num);
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

// Вставляет новый node с inf = num перед Node
void List::insert(size_t index, Figure num) {
    node *Node = getNodeByIndex(index);
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

// Печатает на экран все Figure, содержащиеся в List
void List::print() {
    node *r = head;
    while (r != NULL) {
        Figure num = *(r->inf);
        num.print();
        r = r->next;
        std::cout << std::endl;
    }
}

// Возвращает индекс num в list
// Если его не найдется, возвращает list.length()
// size_t List::find(Figure num) {
//     for (size_t i = 0; i < length(); ++i) {
//         Figure num1 = (*this)[i];
//         if (equal(num.angle(), num1.angle()),
//             equal(num.radius(), num1.radius())) {
//             return i;
//         }
//     }
//     return length();
// }

// Возвращает true, если в List найдётся node с inf == num,
// возвращает false в противном случае
// bool List::contains(Figure num) {
//     node *r = head;
//     while (r != NULL) {
//         if (*(r->inf) == num) {
//             return true;
//         }
//         r = r->next;
//     }
//     return false;
// }

// Вернёт указатель на первый node в List
node *List::begin() { return head; }

// Вернёт указатель на последний node в List
node *List::end() { return tail; }

// Удалит node из List
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

// Удалит Figure, расположенный в index-ой ячейке List
void List::remove(size_t index) {
    node *cur = getNodeByIndex(index);
    this->erase(cur);
    cur = cur->next;
}

class Point : public Figure {
    private:
        std::string type = "Точка";
        std::string name = "Безымянная точка";

    public:
        Point() {};
        Point(double x, double y, double z)
            : Figure(x, y, z) {}
        Point(double x, double y, double z, std::string name)
            : Figure(x, y, z),
              name(name) {}
        virtual std::string getName() { return name; }
        virtual std::string getType() { return type; }

        double getX() { return x; }
        double getY() { return y; }
        double getZ() { return z; }
        bool operator==(Point &point2) {
            return (equal(x, point2.getX()) && equal(y, point2.getY()),
                    equal(z, point2.getZ()));
        }
};

class Sphere : public Figure {
    private:
        double radius = 0;
        std::string type = "Шар";
        std::string name = "Безымянный шар";

    public:
        Sphere() {};
        Sphere(double x, double y, double z)
            : Figure(x, y, z) {}
        Sphere(double x, double y, double z, std::string name)
            : Figure(x, y, z),
              name(name) {}
        Sphere(double x, double y, double z, double r)
            : Figure(x, y, z),
              radius(r) {
            if (r < 0) {
                throw std::invalid_argument(
                    "ОШИБКА: Радиус должен быть неотрицательным");
            }
        }
        Sphere(double x, double y, double z, double r, std::string name)
            : Figure(x, y, z),
              radius(r),
              name(name) {

            throw std::invalid_argument(
                "ОШИБКА: Радиус должен быть неотрицательным");
        }
        virtual std::string getName() { return name; }
        virtual std::string getType() { return type; }
};

class Segment : public Figure {
    private:
        Point beginPoint;
        Point endPoint;
        std::string type = "Отрезок";
        std::string name = "Безымянный отрезок";

    public:
        Segment() {};
        Segment(Point beginPoint, Point endPoint)
            : beginPoint(beginPoint),
              endPoint(endPoint) {}
        Point getBeginPoint() { return beginPoint; }
        Point getEndPoint() { return endPoint; }
        double getLength() {
            Point point1 = getBeginPoint();
            Point point2 = getEndPoint();
            double x1 = point1.getX();
            double y1 = point1.getY();
            double z1 = point1.getZ();

            double x2 = point2.getX();
            double y2 = point2.getY();
            double z2 = point2.getZ();

            double diffX = x1 - x2;
            double diffY = y1 - y2;
            double diffZ = z1 - z2;

            return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
        }
        bool operator==(Segment &seg2) {
            Point point11 = getBeginPoint();
            Point point12 = getEndPoint();

            Point point21 = seg2.getBeginPoint();
            Point point22 = seg2.getEndPoint();
            return (point11 == point21 && point12 == point22);
        }
};

class Polyhedron : public Figure {
    private:
        std::string type = "Многогранник";
        std::string name = "Безымянный многогранник";
        List edges = List();

    public:
        Polyhedron() {};
        Polyhedron(double x, double y, double z, List &inputEdges)
            : Figure(x, y, z) {
            for (size_t i = 0; i < edges.length(); ++i) {
                edges.push(inputEdges[i]);
            }
        }
        Polyhedron(double x, double y, double z, std::string name)
            : Figure(x, y, z),
              name(name) {}
        virtual std::string getName() { return name; }
        virtual std::string getType() { return type; }
};

int main() {
    try {
        Figure f = Figure(1, 2, 3);
        Point a = Point(1, 3, 5);
        Sphere b = Sphere(1, 3, 5, -1);
        a.print();
        b.print();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
