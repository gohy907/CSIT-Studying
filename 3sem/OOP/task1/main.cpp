#include <cmath>
#include <iostream>
#include <string>

// Возвращает true, если числа a и b отличаются менее чем на eps,
// возвращает false в противном случае
bool equal(double a, double b) {
    double eps = 0.0000000000001;
    return std::abs(a - b) < eps;
}

// Класс комплексного числа в тригонометрической форме
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
        void setIsExtended();
        bool isExtended;
        double re;
        double im;
        double r;
        double phi;
};

void complexNumber::setIsExtended() {
    isExtended = phi > 2 * M_PI || phi < -2 * M_PI;
}

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

bool complexNumber::getIsExtended() { return isExtended; }
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
    setIsExtended();
}

// Конструктор complexNumber
complexNumber::complexNumber() {
    setRadius(0.0);
    setAngle(0.0);
    setRe();
    setIm();
    setIsExtended();
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
void complexNumber::setAngle(double Phi) { phi = Phi; }

// Сеттер атрибута r. Вызовёт исключение invalid_argument, если R < 0
void complexNumber::setRadius(double R) {
    if (R < 0) {
        throw std::invalid_argument("ОШИБКА: Ожидалось, что R > 0");
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

// Структура node для реализации двустороннено списка
struct node {
        complexNumber *inf;
        node *next;
        node *prev;
};

// Двусторонний список, содержащий node, которые содержат complexNumber
class List {
    public:
        List();
        ~List();

        void push(complexNumber num);
        void print();
        void insert(size_t index, complexNumber num);
        bool contains(complexNumber num);
        node *find(complexNumber num);
        void remove(size_t index);

        node *begin();
        node *end();

        void findAll(bool condition(complexNumber &num));

        complexNumber operator[](size_t index);

        size_t length();

    private:
        node *getNodeByIndex(size_t index);
        void erase(node *node);
        node *head;
        node *tail;
};

// Конструктор пустого List
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

complexNumber List::operator[](size_t index) {
    return *getNodeByIndex(index)->inf;
}

// Печатает на экране все complexNumber в List, удовлетворящие функции condition
void List::findAll(bool condition(complexNumber &num)) {
    node *cur = head;
    while (cur) {
        complexNumber &curNum = *(cur->inf);
        if (condition(curNum)) {
            curNum.print();
            std::cout << std::endl;
        }
        cur = cur->next;
    }
}

// Вставляет новый node с inf = num в конец List
void List::push(complexNumber num) {
    node *r = new node;
    r->inf = new complexNumber(num);
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
void List::insert(size_t index, complexNumber num) {
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

// Печатает на экран все complexNumber, содержащиеся в List
void List::print() {
    node *r = head;
    while (r != NULL) {
        complexNumber num = *(r->inf);
        num.print();
        r = r->next;
        std::cout << std::endl;
    }
}

// Возвращает node, в котором inf == num, если .contains(num),
// возвращает .end() в противном случае
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

// Возвращает true, если в List найдётся node с inf == num,
// возвращает false в противном случае
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

void List::remove(size_t index) {
    node *cur = getNodeByIndex(index);
    this->erase(cur);
    cur = cur->next;
}
// Возвращает true, если комплексное число находится в первой четверти
// координатной плоскости, включая границы, и false в обратном случае
bool isInFirstQuarter(complexNumber num) {
    return (0 <= sin(num.angle()) && sin(num.angle()) <= 1) &&
           (0 <= cos(num.angle()) && cos(num.angle()) <= 1);
}

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
        if (num < 0 || num > 8) {
            return false;
        }
    } catch (std::invalid_argument &error) {
        checkForEOF();
        return false;
    }
    return true;
}

bool getComplexNumberFromUser(complexNumber &num) {
    std::string rStr;
    std::string phiStr;

    std::cout << "Введите радиус: ";
    std::getline(std::cin, rStr);

    if (!isValidFloat(rStr)) {
        std::cout << "ОШИБКА: Ошибка ввода, ожидалось число в формате 12.34"
                  << std::endl;
        return false;
    }

    std::cout << "Введите угол: ";
    std::getline(std::cin, phiStr);
    if (!isValidFloat(phiStr)) {
        std::cout << "ОШИБКА: Ошибка ввода, ожидалось число в формате 12.34"
                  << std::endl;
        return false;
    }

    num = complexNumber(std::stod(rStr), std::stod(phiStr));
    return true;
}

int main() {
    List list = List();
    while (true) {
        std::cout << "0: Выйти" << std::endl;
        std::cout << "1: Вывести список" << std::endl;
        std::cout << "2: Добавить в конец списка число" << std::endl;
        std::cout << "3: Добавить число в какое-то место списка" << std::endl;
        std::cout << "4: Удалить из списка число" << std::endl;
        std::cout << "5: Вывести число из списка" << std::endl;
        std::cout << "6: Вывести число из списка в алгебраической форме"
                  << std::endl;
        std::cout
            << "7: Прибавить ко всем числам, с радиусом меньше 2, 0.5 к радиусу"
            << std::endl;
        std::cout
            << "8: Сделать копии чисел из списка, уменьшить вдвое их угол, и "
               "добавить в конец списка"
            << std::endl;

        std::cout << "Выберите действие: ";

        std::string optionStr;
        std::getline(std::cin, optionStr);
        checkForEOF();
        std::cout << std::endl;

        int option;
        if (isValidSize(optionStr)) {
            option = std::stoi(optionStr);
        } else {
            std::cout << "ОШИБКА: Ожидалось число от 0 до 8" << std::endl;
        }

        if (option == 0) {
            break;
        }

        switch (option) {
        case 1: {
            list.print();
            break;
        }
        case 2: {
            complexNumber num;
            if (getComplexNumberFromUser(num)) {
                list.push(num);
            }
            break;
        }
        case 3: {
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
                complexNumber num;
                if (getComplexNumberFromUser(num)) {
                    list.insert(index, num);
                }
            }
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
        }

        std::cout << std::endl;
    }

    complexNumber b = complexNumber(2, 3);
    complexNumber c = complexNumber(3, 4);
}
