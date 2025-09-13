#include <chrono>
#include <cmath>
#include <iostream>

long long fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

long long fibonacciGoldenRatio(int n) {
    double phi = (1 + sqrt(5)) / 2;
    return round(pow(phi, n) / sqrt(5));
}

void multiplyMatrix(long long F[2][2], long long M[2][2]) {
    long long a = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long b = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long c = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long d = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = a;
    F[0][1] = b;
    F[1][0] = c;
    F[1][1] = d;
}

void powerMatrix(long long F[2][2], int n) {
    if (n == 0 || n == 1) {
        return;
    }

    long long M[2][2] = {{1, 1}, {1, 0}};

    powerMatrix(F, n / 2);
    multiplyMatrix(F, F);

    if (n % 2 != 0) {
        multiplyMatrix(F, M);
    }
}

long long fibonacciMatrix(int n) {
    if (n == 0) {
        return 0;
    }

    long long F[2][2] = {{1, 1}, {1, 0}};
    powerMatrix(F, n - 1);

    return F[0][0];
}

int main() {
    int n;
    std::cout << "Введите номер числа Фибоначчи: ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "Номер должен быть неотрицательным." << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "1. Рекурсивный метод  (сложность O(2^n)): "
              << fibonacciRecursive(n);

    auto stop = std::chrono::high_resolution_clock::now();
    int duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();
    std::cout << ", время выполнения: " << duration << "мс" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    std::cout << "2. Метод золотого сечения (сложность O(1)): "
              << fibonacciGoldenRatio(n);

    stop = std::chrono::high_resolution_clock::now();
    duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();
    std::cout << ", время выполнения: " << duration << "мс" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    std::cout << "3. Матричный метод (сложность O(log(n))): "
              << fibonacciMatrix(n);

    stop = std::chrono::high_resolution_clock::now();
    duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();
    std::cout << ", время выполнения: " << duration << "мс" << std::endl;
}
