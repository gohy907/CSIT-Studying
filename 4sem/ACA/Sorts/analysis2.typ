= Быстрая сортировка

== Код программы

```cpp
void quick_sort(std::vector<int> &numbers, size_t left, size_t right) {
    size_t i = left;
    size_t j = right;


    // Выбираем опорным элементом середину массива
    size_t pivot = numbers[left + (right - left) / 2];

    // В цикле проходим максимум n итераций
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
        // Вызываем функцию сортировки от массива размером n / 2
        // Значит дерево рекурсии будет логарифмической высоты
        // Поэтому сложность алгоритма будет O(n) * O(log n) = O(n log n)
        quick_sort(numbers, left, j);
    if (i < right)
        quick_sort(numbers, i, right);
}
```

== Анализ сложности

$n$ --- количество элементов в массиве.

Опорным элементов выбирается середина массива.

В цикле проводится максимум $n$ итераций.
Далее мы вызываем функцию сортировки от массива размером:
- В лучшем и среднем случае $n/2$, так как выбрали опорным элементом середину;
- В худшем случае $n - 1$, так как от массива может отделиться всего один элемент.

Тогда дерево рекурсии алгоритма будет высоты:
- В лучшем и среднем случае $log_2 n$;
- В худшем случае $n$.

Значит сложность алгоритма:
- В лучшем и среднем случае $O(n) * O(log n) = O(n log n)$;
- В худшем случае $O(n) * O(n) = O(n^2)$.

= Пирамидальная сортировка

== Код программы

```cpp
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
        // Каждый раз прыгаем на элемент, индекс которого в два раза больше
        // предыдущего
        // Поэтому высота дерева рекурсии будет логарифмической
        // А функция работать за O(log n)
        heapify(numbers, largest, length);
    }
}

void pyramid_sort(std::vector<int> &numbers) {

    // Вызываем heapify от n / 2 элементов
    // Т.е. цикл будет работать за O(n) * O(log n) = O(n log n)
    for (size_t i = numbers.size() / 2 - 1; i != 0; --i) {
        heapify(numbers, i, numbers.size());
    }
    heapify(numbers, 0, numbers.size());

    // В цикле меняем первый и последний элементы местами
    // Проходим по всему массиву чисел
    // Вызываем перестройку дерева на каждой итерации
    // Поэтому сложность - O(n) * O(log n) = O(n log n)
    for (size_t i = numbers.size() - 1; i != 0; --i) {
        int tmp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = tmp;
        heapify(numbers, 0, i);
    }
}
```

== Анализ сложности

$n$ --- количество элементов в массиве.

Рассмотрим сначала функцию `heapify`:

Она работает рекурсивно, увеличивая входной индекс примерно в 2 раза каждый вызов рекурсии, пока не дойдет до конца массива.
Поэтому высота дерева рекурсии имеет вид $O(log n)$.

В самой функции происходит $O(1)$ операций, поэтому её сложность --- $O(log n)$.

В основном алгоритме мы сначала вызываем `heapify` от $n/2$ элементов, то есть сложность первого цикла --- $O(n) * O(log n) = O(n log n)$.

Во втором цикле мы проходимся по всем элементам массива и вызываем перестройку кучи, сложность второго цикла будет так же $O(n log n)$.

Итого, сложность алгоритма ---  $O(n log n)$ во всех случаях.
