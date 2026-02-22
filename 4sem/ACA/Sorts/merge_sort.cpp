#include <iostream>
#include <vector>
void merge(std::vector<int> &numbers, size_t left, size_t right,
           size_t middle) {
    std::vector<int> temp(right - left + 1, 0);
    size_t cur = 0;
    size_t i = left;
    size_t j = middle + 1;

    while (i <= middle && j <= right) {
        if (numbers[i] <= numbers[j]) {
            temp[cur] = numbers[i];
            ++i;
        } else {
            temp[cur] = numbers[j];
            ++j;
        }
        ++cur;
    }

    while (i <= middle) {
        temp[cur] = numbers[i];
        ++cur;
        ++i;
    }
    while (j <= right) {
        temp[cur] = numbers[j];
        ++cur;
        ++j;
    }
    for (size_t j = 0; j < temp.size(); ++j) {
        numbers[left + j] = temp[j];
    }
}
void merge_sort(std::vector<int> &numbers, size_t left, size_t right) {
    if (left < right) {
        merge_sort(numbers, left, (left + right) / 2);
        merge_sort(numbers, (left + right) / 2 + 1, right);
        merge(numbers, left, right, (left + right) / 2);
    }
}

void merge_sort_helper(std::vector<int> &numbers) {
    size_t left = 0;
    size_t right = numbers.size() - 1;
    merge_sort(numbers, left, right);
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
    merge_sort_helper(numbers);

    print_vector(numbers);
}
