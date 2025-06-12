#include <iostream>
#include <vector>

std::vector<std::vector<int>> matrix_add(std::vector<std::vector<int>> &A,
                                         std::vector<std::vector<int>> &B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

std::vector<std::vector<int>> matrix_sub(std::vector<std::vector<int>> &A,
                                         std::vector<std::vector<int>> &B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

void split_matrix(std::vector<std::vector<int>> &M,
                  std::vector<std::vector<int>> &M11,
                  std::vector<std::vector<int>> &M12,
                  std::vector<std::vector<int>> &M21,
                  std::vector<std::vector<int>> &M22, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            M11[i][j] = M[i][j];
            M12[i][j] = M[i][j + size];
            M21[i][j] = M[i + size][j];
            M22[i][j] = M[i + size][j + size];
        }
    }
}

std::vector<std::vector<int>> merge_matrix(std::vector<std::vector<int>> &M11,
                                           std::vector<std::vector<int>> &M12,
                                           std::vector<std::vector<int>> &M21,
                                           std::vector<std::vector<int>> &M22,
                                           int size) {
    int n = size * 2;
    std::vector<std::vector<int>> M(n, std::vector<int>(n));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            M[i][j] = M11[i][j];
            M[i][j + size] = M12[i][j];
            M[i + size][j] = M21[i][j];
            M[i + size][j + size] = M22[i][j];
        }
    }
    return M;
}

std::vector<std::vector<int>>
strassenMultiply(std::vector<std::vector<int>> &A,
                 std::vector<std::vector<int>> &B);

std::vector<std::vector<int>>
strassenMultiplyImpl(std::vector<std::vector<int>> &A,
                     std::vector<std::vector<int>> &B) {
    int n = A.size();

    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int new_size = n / 2;

    std::vector<std::vector<int>> A11(new_size, std::vector<int>(new_size));
    std::vector<std::vector<int>> A12(new_size, std::vector<int>(new_size));
    std::vector<std::vector<int>> A21(new_size, std::vector<int>(new_size));
    std::vector<std::vector<int>> A22(new_size, std::vector<int>(new_size));

    std::vector<std::vector<int>> B11(new_size, std::vector<int>(new_size));
    std::vector<std::vector<int>> B12(new_size, std::vector<int>(new_size));
    std::vector<std::vector<int>> B21(new_size, std::vector<int>(new_size));
    std::vector<std::vector<int>> B22(new_size, std::vector<int>(new_size));

    split_matrix(A, A11, A12, A21, A22, new_size);
    split_matrix(B, B11, B12, B21, B22, new_size);

    std::vector<std::vector<int>> A11_plus_A22 = matrix_add(A11, A22);
    std::vector<std::vector<int>> B11_plus_B22 = matrix_add(B11, B22);
    std::vector<std::vector<int>> A21_plus_A22 = matrix_add(A21, A22);
    std::vector<std::vector<int>> A11_plus_A12 = matrix_add(A11, A12);
    std::vector<std::vector<int>> A21_minus_A11 = matrix_sub(A21, A11);
    std::vector<std::vector<int>> B11_plus_B12 = matrix_add(B11, B12);
    std::vector<std::vector<int>> A12_minus_A22 = matrix_sub(A12, A22);
    std::vector<std::vector<int>> B21_plus_B22 = matrix_add(B21, B22);
    std::vector<std::vector<int>> B12_minus_B22 = matrix_sub(B12, B22);
    std::vector<std::vector<int>> B21_minus_B11 = matrix_sub(B21, B11);

    std::vector<std::vector<int>> P1 =
        strassenMultiply(A11_plus_A22, B11_plus_B22);
    std::vector<std::vector<int>> P2 = strassenMultiply(A21_plus_A22, B11);
    std::vector<std::vector<int>> P3 = strassenMultiply(A11, B12_minus_B22);
    std::vector<std::vector<int>> P4 = strassenMultiply(A22, B21_minus_B11);
    std::vector<std::vector<int>> P5 = strassenMultiply(A11_plus_A12, B22);
    std::vector<std::vector<int>> P6 =
        strassenMultiply(A21_minus_A11, B11_plus_B12);
    std::vector<std::vector<int>> P7 =
        strassenMultiply(A12_minus_A22, B21_plus_B22);

    std::vector<std::vector<int>> forC11_1 = matrix_add(P1, P4);
    std::vector<std::vector<int>> forC11_2 = matrix_sub(P7, P5);
    // std::vector<std::vector<int>> C11 = matrix_add(matrix_sub(matrix_add(P1,
    // P4), matrix_sub(P7, P5)));
    std::vector<std::vector<int>> C11 = matrix_add(forC11_1, forC11_2);
    std::vector<std::vector<int>> C12 = matrix_add(P3, P5);
    std::vector<std::vector<int>> C21 = matrix_add(P2, P4);
    std::vector<std::vector<int>> forC22_1 = matrix_add(P1, P3);
    std::vector<std::vector<int>> forC22_2 = matrix_sub(P6, P2);
    std::vector<std::vector<int>> C22 = matrix_add(forC22_1, forC22_2);

    return merge_matrix(C11, C12, C21, C22, new_size);
}

std::vector<std::vector<int>>
strassenMultiply(std::vector<std::vector<int>> &A,
                 std::vector<std::vector<int>> &B) {

    int n = A.size();

    return strassenMultiplyImpl(A, B);
}

bool isPowerOfTwo(int n) { return (n & (n - 1)) == 0; }

std::vector<std::vector<int>> padMatrix(std::vector<std::vector<int>> &M,
                                        int new_size) {
    std::vector<std::vector<int>> padded(new_size,
                                         std::vector<int>(new_size, 0));
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[i].size(); j++) {
            padded[i][j] = M[i][j];
        }
    }
    return padded;
}

std::vector<std::vector<int>> matrixMultiply(std::vector<std::vector<int>> &A,
                                             std::vector<std::vector<int>> &B) {

    int m = A.size();
    int n = B.size();
    int p = B[0].size();

    if (m != n || n != p || !isPowerOfTwo(n)) {
        std::vector<std::vector<int>> C(m, std::vector<int>(p, 0));
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < p; j++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    return strassenMultiply(A, B);
}

void printMatrix(std::vector<std::vector<int>> &M) {
    for (auto &row : M) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> inputMatrix(int size) {
    std::vector<std::vector<int>> vec(size);
    for (int i = 0; i < size; ++i) {
        int tmp;
        for (int j = 0; j < size; ++j) {
            std::cin >> tmp;
            vec[i].push_back(tmp);
        }
    }
    return vec;
}

int main() {
    int size;
    std::cout << "Введите размер матриц: ";
    std::cin >> size;

    std::cout << "Матрица A:" << std::endl;
    std::vector<std::vector<int>> A = inputMatrix(size);
    std::cout << "Матрица B:" << std::endl;
    std::vector<std::vector<int>> B = inputMatrix(size);

    std::vector<std::vector<int>> C = matrixMultiply(A, B);
    std::cout << "Результат умножения:" << std::endl;
    printMatrix(C);
}
