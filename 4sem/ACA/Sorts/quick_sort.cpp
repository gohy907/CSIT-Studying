#include <iostream>
#include <vector>

void quick_sort(std::vector<int> &numbers, size_t left, size_t right) {
    size_t i = left;
    size_t j = right;
    int pivot = numbers[left + (right - left) / 2];

    while (i <= j) {
        while (numbers[i] < pivot) {
            ++i;
        }
        while (numbers[j] > pivot && j != 0) {
            --j;
        }

        if (i <= j) {
            int tmp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = tmp;
            if (j != 0) {
                --j;
            }
            ++i;
        }
    }

    if (left < j)
        quick_sort(numbers, left, j);
    if (i < right)
        quick_sort(numbers, i, right);
}

void quick_sort_helper(std::vector<int> &numbers) {
    quick_sort(numbers, 0, numbers.size() - 1);
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
    quick_sort_helper(numbers);
    print_vector(numbers);
}
