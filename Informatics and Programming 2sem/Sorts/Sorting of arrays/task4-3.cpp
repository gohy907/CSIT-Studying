#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

void readFrom(std::map<int, std::vector<int>> &matrix, std::string file) {
  std::ifstream in(file);
  int i = 0;
  while (in.peek() != EOF) {
    std::string line;
    getline(in, line);
    std::stringstream ss(line);
    int tmp;
    std::vector<int> vec2;
    while (ss >> tmp) {
      vec2.push_back(tmp);
    }
    matrix[i] = vec2;
    ++i;
  }

  in.close();
}

void writeTo(std::map<int, std::vector<int>> &matrix, std::string file) {
  std::ofstream out(file);
  for (int i = 0; i < matrix[0].size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      out << matrix[i][j] << " ";
    }
    out << std::endl;
  }
}

void insertionSort(std::vector<int> &vec) {
  int left = 0;
  int right = vec.size();
  for (int i = left; i < right; ++i) {
    for (int j = i - 1; j >= left; --j) {
      if (vec[j] > vec[j + 1]) {
        int tmp = vec[j + 1];
        vec[j + 1] = vec[j];
        vec[j] = tmp;
      } else {
        break;
      }
    }
  }
}

int main() {
  std::map<int, std::vector<int>> matrix;
  readFrom(matrix, "input.txt");

  int n = matrix[0].size();
  for (int k = 1; k < 2 * n - 2; ++k) {
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) {
      if (k - i < n && k - i >= 0) {
        vec.push_back(matrix[i][k - i]);
      }
    }

    insertionSort(vec);

    int l = 0;
    for (int i = 0; i < n; ++i) {
      if (k - i < n && k - i >= 0) {
        matrix[i][k - i] = vec[l];
        ++l;
      }
    }
  }

  writeTo(matrix, "output.txt");
}
