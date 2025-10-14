#include <cmath>
#include <cstddef>
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

    public:
        Figure() {};
        Figure(double x, double y, double z)
            : x(x),
              y(y),
              z(z) {}
        void print() {
            std::cout << "Тип: " << getType() << std::endl
                      << "Имя: " << getName() << std::endl
                      << "Координаты: " << "(" << x << ", " << y << ", " << z
                      << ")" << std::endl;
        }
        virtual std::string getName() { return name; }
        virtual std::string getType() { return type; }

        bool operator==(Figure &f) {
            return equal(x, f.x) && equal(y, f.y) && equal(z, f.z) &&
                   type == f.type;
        }
        virtual double size() { return 0; }
        virtual double volume() { return 0; }
        virtual bool input() { return false; }
        virtual Figure &operator=(const Figure &f) {
            if (this != &f) { // Проверка самоприсваивания
                x = f.x;
                y = f.y;
                z = f.z;
                type = f.type;
                name = f.name;
            }
            return *this;
        }
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

        void push(Figure *num);
        void print();
        void insert(size_t index, Figure *num);
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
void List::push(Figure *num) {
    node *r = new node;
    r->inf = num; // Не создаём объект Figure, а просто сохраняем указатель!
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
void List::insert(size_t index, Figure *num) {
    node *Node = getNodeByIndex(index);
    node *newNode = new node;
    newNode->inf = num;
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
        Figure *num = (r->inf);
        num->print();
        r = r->next;
        std::cout << std::endl;
    }
}

// Возвращает индекс num в list
// Если его не найдется, возвращает list.length()
size_t List::find(Figure num) {
    for (size_t i = 0; i < length(); ++i) {
        Figure num1 = (*this)[i];
        if (num1 == num) {
            return i;
        }
    }
    return length();
}

// Возвращает true, если в List найдётся node с inf == num,
// возвращает false в противном случае
bool List::contains(Figure num) {
    node *r = head;
    while (r != NULL) {
        if (*(r->inf) == num) {
            return true;
        }
        r = r->next;
    }
    return false;
}

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
        void setDefaultType() { type = "Точка"; }

    public:
        Point() { setDefaultType(); };
        Point(double x, double y, double z)
            : Figure(x, y, z) {

            setDefaultType();
        }
        Point(double x, double y, double z, std::string name)
            : Figure(x, y, z) {
            setName(name);
            setDefaultType();
        }
        virtual std::string getName() override { return name; }
        virtual std::string getType() override { return type; }

        double getX() { return x; }
        double getY() { return y; }
        double getZ() { return z; }
        virtual void setName(std::string &newName) { name = newName; }
        bool input() override {
            std::cout << "Введите координаты x, y, z через пробел: ";
            if (!(std::cin >> x >> y >> z))
                return false;

            std::cout << "Введите имя: ";
            if (!(std::cin >> name))
                return false;

            return true;
        }
};

class Sphere : public Figure {
    private:
        double radius = 0;
        void setDefaultType() { type = "Сфера"; }

    public:
        Sphere() { setDefaultType(); };
        Sphere(double x, double y, double z)
            : Figure(x, y, z) {}
        Sphere(double x, double y, double z, std::string name)
            : Figure(x, y, z) {
            setName(name);
            setDefaultType();
        }
        Sphere(double x, double y, double z, double r)
            : Figure(x, y, z),
              radius(r) {
            if (r < 0) {
                throw std::invalid_argument(
                    "ОШИБКА: Радиус должен быть неотрицательным");
            }
            setDefaultType();
        }
        Sphere(double x, double y, double z, double r, std::string name)
            : Figure(x, y, z),
              radius(r) {
            if (r < 0) {
                throw std::invalid_argument(
                    "ОШИБКА: Радиус должен быть неотрицательным");
            }
            setName(name);
            setDefaultType();
        }
        virtual std::string getName() override { return name; }
        virtual std::string getType() override { return type; }
        virtual void setName(std::string &newName) { name = newName; }
        bool input() override {
            std::cout << "Введите координаты x, y, z, радиус через пробел: ";
            if (!(std::cin >> x >> y >> z >> radius))
                return false;
            if (radius < 0) {
                std::cout << "Ошибка: радиус не должен быть отрицательным\n";
                return false;
            }

            std::cout << "Введите имя: ";
            if (!(std::cin >> name))
                return false;

            return true;
        }
};

class Polyhedron : public Figure {
    private:
        size_t numberOfEdgesInSide;
        void setDefaultType() { type = "Многогранник"; }

    public:
        Polyhedron() { setDefaultType(); };
        Polyhedron(double x, double y, double z)
            : Figure(x, y, z) {}
        Polyhedron(double x, double y, double z, size_t numberOfEdgesInSide,
                   std::string &name)
            : Figure(x, y, z),
              numberOfEdgesInSide(numberOfEdgesInSide) {
            setDefaultType();
            setName(name);
        }

        virtual std::string getName() override { return name; }
        virtual std::string getType() override { return type; };
        virtual void setName(std::string &newName) { name = newName; }
        bool input() override {
            std::cout << "Введите координаты x, y, z, количество ребёр на "
                         "грани через пробел: ";
            if (!(std::cin >> x >> y >> z >> numberOfEdgesInSide))
                return false;
            if (numberOfEdgesInSide <= 1) {
                std::cout << "ОШИБКА: Количество сторон должно быть больше 1"
                          << std::endl;
                return false;
            }

            std::cout << "Введите имя: ";
            if (!(std::cin >> name))
                return false;

            return true;
        }
};

class Cube : public Polyhedron {
    private:
        size_t numberOfEdgesInSide = 4;
        void setDefaultType() { type = "Куб"; }

    public:
        Cube() { setDefaultType(); };
        Cube(double x, double y, double z, size_t numberOfEdgesInSide,
             std::string &name)
            : Polyhedron(x, y, z, numberOfEdgesInSide, name) {
            setDefaultType();
            setName(name);
        }

        bool input() override {
            std::cout << "Введите координаты x, y, z: ";
            if (!(std::cin >> x >> y >> z))
                return false;
            std::cout << "Введите имя: ";
            if (!(std::cin >> name))
                return false;

            return true;
        }
};

void checkForEOF() {
    if (std::cin.eof()) {
        exit(0);
    }
}

bool isValidFloat(std::string &str) {
    try {
        double num = std::stod(str);
    } catch (std::invalid_argument &error) {
        checkForEOF();
        return false;
    }

    return true;
}

bool isValidSize(std::string &str) {
    try {
        int num = std::stoi(str);
    } catch (std::invalid_argument &error) {
        checkForEOF();
        return false;
    }
    return true;
}

Figure *createFigure(int n) {
    switch (n) {
    case 1:
        return new Point();
    case 2:
        return new Sphere();
    case 3:
        return new Polyhedron();
    case 4:
        return new Cube();
    }
    return NULL;
}

void pushFromInput(List &list) {
    while (true) {
        std::cout << "Выберите тип фигуры: " << std::endl;
        std::cout << "0: Отменить" << std::endl;
        std::cout << "1: Точка" << std::endl;
        std::cout << "2: Сфера" << std::endl;
        std::cout << "3: Многогранник" << std::endl;
        std::cout << "4: Куб" << std::endl;
        std::string optionStrFig;

        std::getline(std::cin, optionStrFig);
        checkForEOF();
        std::cout << std::endl;
        int optionFig;
        if (isValidSize(optionStrFig)) {
            optionFig = std::stoi(optionStrFig);
        } else {
            std::cout << "ОШИБКА: Ожидалось число от 1 до 3" << std::endl;
            continue;
        }
        if (optionFig == 0) {
            break;
        } else if (optionFig < 1 || optionFig > 4) {
            std::cout << "ОШИБКА: Ожидалось число от 1 до 4" << std::endl;
            continue;
        }

        Figure *fig = createFigure(optionFig);

        if (!fig->input()) {
            std::cout << "ОШИБКА: Ошибка ввода\n";
            delete fig;
            return;
        }

        list.push(fig);
        break;
    }
}

void insertFromInput(List &list) {

    std::cout << "Введите индекс: ";
    std::string indexStr;
    std::getline(std::cin, indexStr);
    checkForEOF();
    if (isValidSize(indexStr)) {
        size_t index = std::stoi(indexStr);
        if (index >= list.length()) {
            std::cout << "ОШИБКА: Индекс больше длины" << std::endl;
            return;
        }

        std::cout << "Выберите тип фигуры: " << std::endl;
        std::cout << "0: Отменить" << std::endl;
        std::cout << "1: Точка" << std::endl;
        std::cout << "2: Сфера" << std::endl;
        std::cout << "3: Многогранник" << std::endl;
        std::string optionStrFig;

        std::getline(std::cin, optionStrFig);
        checkForEOF();
        std::cout << std::endl;
        int optionFig;
        if (isValidSize(optionStrFig)) {
            optionFig = std::stoi(optionStrFig);
        } else {
            std::cout << "ОШИБКА: Ожидалось число от 1 до 3" << std::endl;
            return;
        }
        if (optionFig == 0) {
            return;
        } else if (optionFig < 1 || optionFig > 3) {
            std::cout << "ОШИБКА: Ожидалось число от 1 до 3" << std::endl;
            return;
        }

        Figure *fig = createFigure(optionFig);

        if (!fig->input()) {
            std::cout << "ОШИБКА: Ошибка ввода\n";
            delete fig;
            return;
        }

        list.insert(index, fig);
        return;
    }
}

int main() {
    try {
        List list = List();
        while (true) {
            std::cout << std::endl;
            std::cout << "0: Выйти" << std::endl;
            std::cout << "1: Вывести список" << std::endl;
            std::cout << "2: Добавить в конец списка фигуру" << std::endl;
            std::cout << "3: Добавить фигуру в какое-то место списка"
                      << std::endl;
            std::cout << "4: Удалить из списка фигуру" << std::endl;
            std::cout << "5: Вывести фигуру из списка" << std::endl;
            std::cout << "6: Скопировать фигуру по индексу и добавить её в "
                         "конец списка"
                      << std::endl;
            std::cout << "7: Попытаться динамически перекастовать одну "
                         "фигуру "
                         "в другую"
                      << std::endl;

            std::cout << "Выберите действие: ";

            std::string optionStr;
            while (optionStr == "") {
                std::getline(std::cin, optionStr);
            }
            checkForEOF();
            std::cout << std::endl;

            int option;
            if (isValidSize(optionStr)) {
                option = std::stoi(optionStr);
            } else {
                std::cout << "ОШИБКА: Ожидалось число от 0 до 9" << std::endl;
                continue;
            }

            if (option == 0) {
                break;
            } else if (option < 0 || option > 9) {
                std::cout << "ОШИБКА: Ожидалось число от 0 до 9" << std::endl;
            }

            switch (option) {
            case 1: {
                list.print();
                break;
            }
            case 2: {
                pushFromInput(list);
                break;
            }
            case 3: {
                insertFromInput(list);
                break;
            }
            case 4: {
                std::cout << "Введите индекс: ";
                std::string indexStr;
                std::getline(std::cin, indexStr);
                checkForEOF();
                if (isValidSize(indexStr)) {
                    size_t index = std::stoi(indexStr);
                    if (index >= list.length()) {
                        std::cout << "ОШИБКА: Индекс больше длины" << std::endl;
                        break;
                    }

                    list.remove(index);
                }
                break;
            }
            case 5: {
                std::cout << "Введите индекс: ";
                std::string indexStr;
                std::getline(std::cin, indexStr);
                checkForEOF();
                if (isValidSize(indexStr)) {
                    size_t index = std::stoi(indexStr);
                    if (index >= list.length()) {
                        std::cout << "ОШИБКА: Индекс больше длины" << std::endl;
                        break;
                    }
                    list[index].print();
                    std::cout << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "Введите индекс: ";
                std::string indexStr;
                std::getline(std::cin, indexStr);
                checkForEOF();
                if (isValidSize(indexStr)) {
                    size_t index = std::stoi(indexStr);
                    if (index >= list.length()) {
                        std::cout << "ОШИБКА: Индекс больше длины" << std::endl;
                        break;
                    }
                    Figure *f = &list[index];
                    Figure *newF = f;
                    list.push(newF);
                    std::cout << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << "Введите индекс: ";
                std::string indexStr;
                std::getline(std::cin, indexStr);
                checkForEOF();
                if (isValidSize(indexStr)) {
                    size_t index = std::stoi(indexStr);
                    if (index >= list.length()) {
                        std::cout << "ОШИБКА: Индекс больше длины" << std::endl;
                        break;
                    }
                    std::cout << "Выберите тип фигуры: " << std::endl;
                    std::cout << "0: Отменить" << std::endl;
                    std::cout << "1: Точка" << std::endl;
                    std::cout << "2: Сфера" << std::endl;
                    std::cout << "3: Многогранник" << std::endl;
                    std::cout << "4: Куб" << std::endl;
                    std::string optionStrFig;

                    std::getline(std::cin, optionStrFig);
                    checkForEOF();
                    std::cout << std::endl;
                    int optionFig;
                    if (isValidSize(optionStrFig)) {
                        optionFig = std::stoi(optionStrFig);
                    } else {
                        std::cout << "ОШИБКА: Ожидалось число от 1 до 4"
                                  << std::endl;
                        break;
                    }
                    if (optionFig == 0) {
                        break;
                    } else if (optionFig < 1 || optionFig > 4) {
                        std::cout << "ОШИБКА: Ожидалось число от 1 до 4"
                                  << std::endl;
                        break;
                    }
                    Figure *f = &list[index];
                    Figure *newF;
                    switch (optionFig) {
                    case 1: {
                        newF = dynamic_cast<Point *>(f);
                        break;
                    }
                    case 2: {
                        newF = dynamic_cast<Sphere *>(f);
                        break;
                    }
                    case 3: {
                        newF = dynamic_cast<Polyhedron *>(f);
                        break;
                    }
                    case 4: {
                        newF = dynamic_cast<Cube *>(f);
                        break;
                    }
                    }
                    if (newF == NULL) {
                        std::cout << "ОШИБКА: Невозможно перекастовать"
                                  << std::endl;
                        break;
                    }
                    list.push(newF);
                }
                break;
            }
            }
        }

        std::cout << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
