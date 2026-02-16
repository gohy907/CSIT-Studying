#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

void counting_sort(std::vector<int> &numbers) {
    int min = INT_MAX;
    int max = INT_MIN;
    for (size_t i = 0; i < numbers.size(); ++i) {
        int num = numbers[i];
        if (num > max) {
            max = num;
        }
        if (num < min) {
            min = num;
        }
    }

    size_t range = static_cast<size_t>(max) - static_cast<size_t>(min) + 1;
    std::vector<int> indices(range, 0);

    std::cout << "1" << std::endl;
    for (size_t i = 0; i < numbers.size(); ++i) {
        size_t num = numbers[i];
        ++indices[num - min];
    }

    std::cout << "2" << std::endl;
    size_t index = 0;
    for (int i = min; i <= max; ++i) {
        size_t a = static_cast<size_t>(i) - static_cast<size_t>(min);
        int count = indices[a];
        for (int j = 0; j < count; ++j) {
            numbers[index] = i;
            ++index;
        }
    }

    std::cout << "3" << std::endl;
}

void print_vector(std::vector<int> &numbers) {
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}

#include "tester.hpp"
int main() {
    std::size_t length = 3;
    // std::cout << "Введите длину массива: ";
    // std::cin >> length;

    // std::vector<int> numbers(length);
    // std::cout << "Вводите числа:" << std::endl;
    // for (std::size_t i = 0; i < length; ++i) {
    //     std::cin >> numbers[i];
    // }
    // numbers.push_back(INT_MAX);
    // numbers.push_back(INT_MIN);
    // counting_sort(numbers);
    // print_vector(numbers);
    tester::Tester t;
    t.test(counting_sort);
}
