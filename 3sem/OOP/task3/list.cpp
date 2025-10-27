#pragma once
#include "complexNumber.h"
#include <cmath>
#include <iostream>

struct node {
        complexNumber *inf;
        node *next;
        node *prev;
};

class List {
    public:
        List();
        ~List();

        void push(complexNumber num);
        void print();
        void insert(size_t index, complexNumber num);
        bool contains(complexNumber num);
        size_t find(complexNumber num);
        void remove(size_t index);

        node *begin();
        node *end();

        void findAll(bool condition(complexNumber &num));
        void addIf(bool condition(complexNumber &num));
        void halfAngleIf(bool condition(complexNumber &num));

        complexNumber &operator[](size_t index);

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

// Вернёт complexNumber, находящийся в index-ой ячейке List
complexNumber &List::operator[](size_t index) {
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

// Возвращает индекс num в list
// Если его не найдется, возвращает list.length()
size_t List::find(complexNumber num) {
    for (size_t i = 0; i < length(); ++i) {
        complexNumber num1 = (*this)[i];
        if (equal(num.angle(), num1.angle()),
            equal(num.radius(), num1.radius())) {
            return i;
        }
    }
    return length();
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

// Удалит complexNumber, расположенный в index-ой ячейке List
void List::remove(size_t index) {
    node *cur = getNodeByIndex(index);
    this->erase(cur);
    cur = cur->next;
}
