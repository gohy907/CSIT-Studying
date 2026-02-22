#include <iostream>
#include <vector>

void heapify(std::vector<int> &numbers, size_t i, size_t length) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < length && numbers[left] > numbers[largest]) {
        largest = left;
    }

    if (right < length && numbers[right] > numbers[largest]) {
        largest = right;
    }

    if (largest != i) {
        int tmp = numbers[i];
        numbers[i] = numbers[largest];
        numbers[largest] = tmp;
        heapify(numbers, largest, length);
    }
}

void pyramid_sort(std::vector<int> &numbers) {

    for (size_t i = numbers.size() / 2 - 1; i != 0; --i) {
        heapify(numbers, i, numbers.size());
    }
    heapify(numbers, 0, numbers.size());

    for (size_t i = numbers.size() - 1; i != 0; --i) {
        int tmp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = tmp;
        heapify(numbers, 0, i);
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
    pyramid_sort(numbers);
    print_vector(numbers);
}
