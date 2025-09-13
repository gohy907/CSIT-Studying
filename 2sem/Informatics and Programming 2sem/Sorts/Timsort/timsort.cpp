#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

std::ifstream in("input.txt");

template <typename T> void reverse_stack(std::stack<T> &stack) {
    std::stack<T> reversedStack;

    while (!stack.empty()) {
        T tmp = stack.top();
        stack.pop();
        reversedStack.push(tmp);
    }
    stack = reversedStack;
}

template <typename T> T getFromStack(std::stack<T> &stack, int h, int index) {
    std::stack<T> tmp;
    T res;
    for (int i = 0; i <= index; ++i) {
        T inf = stack.top();
        tmp.push(inf);
        stack.pop();
        if (i == index) {
            res = inf;
        }
    }

    for (int i = 0; i <= index; ++i) {
        T inf = tmp.top();
        stack.push(inf);
        tmp.pop();
    }

    return res;
}

template <typename T>
void popFromStack(std::stack<T> &stack, int h, int index) {
    std::stack<T> tmp;
    for (int i = 0; i <= index; ++i) {
        T inf = stack.top();
        if (i != index) {
            tmp.push(inf);
        }
        stack.pop();
    }

    for (int i = 0; i < index; ++i) {
        T inf = tmp.top();
        stack.push(inf);
        tmp.pop();
    }
}

template <typename T>
void pushToStack(std::stack<T> &stack, int h, int index, T inf) {
    std::stack<T> tmp;
    for (int i = 0; i < index; ++i) {
        T inf = stack.top();
        tmp.push(inf);
        stack.pop();
    }
    stack.push(inf);

    for (int i = 0; i < index; ++i) {
        T inf = tmp.top();
        stack.push(inf);
        tmp.pop();
    }
}

int size(std::pair<int, int> pair) { return pair.second - pair.first + 1; }

int getMinrun(int n) {
    int tmp = 0;
    while (n >= 64) {
        tmp = tmp | (n & 1);
        n = n >> 1;
    }

    return n + tmp;
}

void printVector(std::vector<int> &vec) {
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void insertSort(std::vector<int> &vec, int left, int right) {
    for (int i = left; i <= right; ++i) {
        for (int j = i; j > left; --j) {
            if (vec[j] < vec[j - 1]) {
                int tmp = vec[j];
                vec[j] = vec[j - 1];
                vec[j - 1] = tmp;
            } else {
                break;
            }
        }
    }
}

// Merges two sub-arrays in original array.
// Left = first index of first sub
// Middle = last index of first sub
// Right = last index of second sub
void merge(std::vector<int> &vec, int left, int middle, int right) {
    int size1 = middle - left + 1;
    int size2 = right - middle;
    std::vector<int> vec1(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<int> vec2(vec.begin() + middle + 1, vec.begin() + right + 1);

    int l = left;
    int i = 0;
    int j = 0;
    while (i < size1 && j < size2) {
        if (vec1[i] < vec2[j]) {
            vec[l] = vec1[i];
            ++i;
        } else {
            vec[l] = vec2[j];
            ++j;
        }
        ++l;
    }

    while (i < size1) {
        vec[l] = vec1[i];
        ++i;
        ++l;
    }

    while (j < size2) {
        vec[l] = vec2[j];
        ++j;
        ++l;
    }
}

void merge(std::vector<int> &vec, std::pair<int, int> pair1,
           std::pair<int, int> pair2) {
    merge(vec, pair1.first, pair1.second, pair2.second);
}

void timsort(std::vector<int> &vec) {
    int n = vec.size();
    if (n == 1) {
        return;
    }
    int minrun = getMinrun(n);
    std::cout << "minrun: " << minrun << std::endl;
    std::cout << "minrun: " << minrun << std::endl;

    int i = 0;
    std::stack<std::pair<int, int>> subArrays;
    while (i < n - 1) {
        int j = i + 1;
        bool isReverse = vec[j - 1] > vec[j];

        while (j < n) {
            if (vec[j - 1] > vec[j] && isReverse ||
                vec[j - 1] <= vec[j] && !(isReverse)) {
                ++j;
            } else {
                break;
            }
        }

        if (isReverse) {
            // Not including vec.begin()
            std::reverse(vec.begin() + i, vec.begin() + j);
        }

        j = std::min(std::max(j, i + minrun - 1), n - 1);

        insertSort(vec, i, j);
        subArrays.push({i, j});
        i = j + 1;
    }

    int h = 0;
    std::stack<std::pair<int, int>> stack;
    while (!subArrays.empty()) {
        std::pair<int, int> r = subArrays.top();
        subArrays.pop();
        stack.push(r);
        ++h;
        while (true) {
            if (h >= 3 && size(getFromStack(stack, h, 0)) >
                              size(getFromStack(stack, h, 2))) {
                std::pair<int, int> st1 = getFromStack(stack, h, 1);
                std::pair<int, int> st2 = getFromStack(stack, h, 2);
                merge(vec, st1, st2);
                st1.second = st2.second;
                popFromStack(stack, h, 1);
                popFromStack(stack, h, 2);
                pushToStack(stack, h, 1, st1);
                --h;
            } else if (h >= 2 && size(getFromStack(stack, h, 0)) >=
                                     size(getFromStack(stack, h, 1))) {
                std::pair<int, int> st0 = getFromStack(stack, h, 0);
                std::pair<int, int> st1 = getFromStack(stack, h, 1);
                merge(vec, st0, st1);
                st0.second = st1.second;
                popFromStack(stack, h, 1);
                popFromStack(stack, h, 0);
                pushToStack(stack, h, 0, st0);
                --h;
            } else if (h >= 3 && size(getFromStack(stack, h, 0)) +
                                         size(getFromStack(stack, h, 1)) >=
                                     size(getFromStack(stack, h, 2))) {
                std::pair<int, int> st0 = getFromStack(stack, h, 0);
                std::pair<int, int> st1 = getFromStack(stack, h, 1);
                merge(vec, st0, st1);
                st0.second = st1.second;
                popFromStack(stack, h, 0);
                popFromStack(stack, h, 1);
                pushToStack(stack, h, 0, st0);
                --h;
            } else if (h >= 4 && size(getFromStack(stack, h, 1)) +
                                         size(getFromStack(stack, h, 2)) >=
                                     size(getFromStack(stack, h, 3))) {
                std::pair<int, int> st0 = getFromStack(stack, h, 0);
                std::pair<int, int> st1 = getFromStack(stack, h, 1);
                merge(vec, st0, st1);
                st0.second = st1.second;
                popFromStack(stack, h, 0);
                popFromStack(stack, h, 1);
                pushToStack(stack, h, 0, st0);
                --h;
            } else
                break;
        }
    }
    while (h != 1) {
        std::pair<int, int> st0 = getFromStack(stack, h, 0);
        std::pair<int, int> st1 = getFromStack(stack, h, 1);
        merge(vec, st0, st1);
        st0.second = st1.second;
        popFromStack(stack, h, 0);
        popFromStack(stack, h, 0);
        pushToStack(stack, h, 0, st0);

        --h;
    }
}

int main() {
    std::vector<int> vec{
        1,  3,  5,  8,  10, 15, 16, 17, 18, 19, 20, 25, 29, 31, 32, 33, 35,
        37, 38, 39, 40, 42, 45, 46, 47, 51, 52, 54, 55, 56, 58, 59, 61, 62,
        63, 65, 67, 68, 71, 72, 73, 75, 76, 80, 88, 89, 91, 93, 94, 95, 2,
        4,  6,  7,  9,  11, 12, 13, 14, 21, 22, 23, 24, 26, 27, 28, 30, 34,
        36, 41, 43, 44, 48, 49, 50, 53, 57, 60, 64, 66, 69, 70, 74, 77, 78,
        79, 81, 82, 83, 84, 85, 86, 87, 90, 92, 96, 97, 98, 99};
    // std::string line;
    // getline(in, line);
    // std::stringstream ss(line);
    //
    // int tmp;
    // while (ss >> tmp) {
    //   vec.push_back(tmp);
    // }

    timsort(vec);
    printVector(vec);
}
