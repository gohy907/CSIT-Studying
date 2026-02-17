#include <cmath>
#include <iostream>
#include <vector>

int number_of_digits(int number) {
    if (number == 0) {
        return 1;
    }
    if (number < 0) {
        number = -number;
    }
    return static_cast<int>(std::log10(number)) + 1;
}

void LSD_sort(std::vector<int> &vec) {
    int base = 10;
    int max_digits = 1;
    for (size_t i = 0; i < vec.size(); ++i) {
        int digits = number_of_digits(vec[i]);
        if (digits > max_digits) {
            max_digits = digits;
        }
    }

    // Здесь я выделяю вектора под все числа от -9 до 9 включительно
    // Чтобы алгоритм работал и на отрицательных числах
    // Из-за этого везде и далее нужно это учитывать в индексах
    std::vector<std::vector<int>> vecs(19);

    for (int i = 0; i < max_digits; ++i) {
        for (int j = 0; j < vec.size(); ++j) {
            int m = vec[j] / pow(10, i);
            if (m < 0) {
                m = -m;
                vecs[9 - m % 10].push_back(vec[j]);
                continue;
            }
            vecs[m % 10 + 9].push_back(vec[j]);
        }

        int l = 0;
        for (int j = 0; j < 19; ++j) {
            for (int h = 0; h < vecs[j].size(); ++h) {
                vec[l] = vecs[j][h];
                ++l;
            }
        }

        for (int j = 0; j < 19; ++j) {
            vecs[j].clear();
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
    LSD_sort(numbers);
    print_vector(numbers);
}
