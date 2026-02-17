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

    size_t range = max - min + 1;
    std::vector<size_t> indices(range, 0);

    for (size_t i = 0; i < numbers.size(); ++i) {
        int num = numbers[i];
        ++indices[num - min];
    }

    size_t index = 0;
    for (int i = min; i <= max; ++i) {
        size_t a = i - min;
        int count = indices[a];
        for (int j = 0; j < count; ++j) {
            numbers[index] = i;
            ++index;
        }
    }
}

void print_vector(std::vector<int> &numbers) {
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::size_t length;
    std::cout << "Введите длину массива: ";
    std::cin >> length;

    std::vector<int> numbers(length);
    std::cout << "Вводите числа:" << std::endl;
    for (std::size_t i = 0; i < length; ++i) {
        std::cin >> numbers[i];
    }
    counting_sort(numbers);
    print_vector(numbers);
}
