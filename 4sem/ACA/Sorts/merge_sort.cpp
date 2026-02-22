#include <iostream>
#include <vector>
void merge(std::vector<int> &numbers, size_t left, size_t right) {

    size_t middle, start, final, j;
    std::vector<int> temp(right + left + 1, 0);
    middle = (left + right) / 2;
    start = left;
    final = middle + 1;

    for (j = left; j <= right; j++) {
        if ((start <= middle) &&
            ((final > right) || (numbers[start] < numbers[final]))) {
            temp[j] = numbers[start];
            start++;
        } else {
            temp[j] = numbers[final];
            final++;
        }
    }

    for (j = left; j <= right; j++) {
        numbers[j] = temp[j];
    }
}

void merge_sort(std::vector<int> &numbers, size_t left, size_t right) {
    if (left < right) {
        merge_sort(numbers, left, (left + right) / 2);
        merge_sort(numbers, (left + right) / 2 + 1, right);
        merge(numbers, left, right);
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
