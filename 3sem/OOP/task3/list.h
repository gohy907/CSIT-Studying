#pragma once
#include <cmath>

class complexNumber;

struct node;

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
