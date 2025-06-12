#include <iostream>

long long modPow(long long a, long long b, long long m) {
    long long result = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b = b >> 1;
    }
    return result;
}

bool millerRabinTest(long long n, long long d, long long a) {
    long long x = modPow(a, d, n);
    if (x == 1 || x == n - 1) {
        return true;
    }
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }
    return false;
}

bool isPrime(long long n, int k = 5) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;

    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    srand(time(0));
    for (int i = 0; i < k; ++i) {
        long long a = 2 + rand() % (n - 3);
        if (!millerRabinTest(n, d, a)) {
            return false;
        }
    }
    return true;
}

int main() {
    long long num;
    std::cout << "Введите число для проверки на простоту: ";
    std::cin >> num;

    if (isPrime(num)) {
        std::cout << num << " — простое число (с высокой вероятностью)."
                  << std::endl;
    } else {
        std::cout << num << " — составное число." << std::endl;
    }

    return 0;
}
