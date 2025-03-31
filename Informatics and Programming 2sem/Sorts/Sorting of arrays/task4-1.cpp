#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <pthread.h>
#include <sstream>
#include <vector>

void LSD_sort(std::vector<int> &vec) {
  int k = 1;
  for (int i = 0; i < vec.size(); ++i) {
    int size = floor(log10(vec[i]) + 1);
    if (size > k) {
      k = size;
    }
  }
  int p = 10;
  std::vector<std::vector<int>> vecs(p);

  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < vec.size(); ++j) {
      int m = vec[j] / pow(p, i);
      vecs[m % p].push_back(vec[j]);
    }

    int l = 0;
    for (int j = 0; j < p; ++j) {
      for (int h = 0; h < vecs[j].size(); ++h, ++l) {
        vec[l] = vecs[j][h];
      }
    }

    for (int j = 0; j < p; ++j) {
      vecs[j].clear();
    }
  }
}

void transpose(std::map<int, std::vector<int>> &matrix) {
  std::map<int, std::vector<int>> matrix2;
  for (int i = 0; i < matrix[i].size(); ++i) {
    std::vector<int> vec;
    for (int j = 0; j < matrix[i].size(); ++j) {
      vec.push_back(0);
    }
    matrix2[i] = vec;
  }

  for (int i = 0; i < matrix[i].size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      matrix2[j][i] = matrix[i][j];
    }
  }

  matrix = matrix2;
}

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

int main() {
  srand(time(0));
  std::map<int, std::vector<int>> matrix;
  readFrom(matrix, "input.txt");
  transpose(matrix);
  for (int i = 0; i < matrix[0].size(); ++i) {
    LSD_sort(matrix[i]);
    std::reverse(matrix[i].begin(), matrix[i].end());
  }
  transpose(matrix);
  writeTo(matrix, "output.txt");
}
