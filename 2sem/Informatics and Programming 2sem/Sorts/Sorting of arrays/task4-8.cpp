#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::vector<int> merge(std::vector<int> vec, int left, int right) {
  std::vector<int> temp(right + left + 1);
  int middle = (left + right) / 2;
  int start = left;
  int final = middle + 1;

  for (int j = left; j <= right; j++) {
    if ((start <= middle) && ((final > right) || (vec[start] < vec[final]))) {
      temp[j] = vec[start];
      start++;
    } else {
      temp[j] = vec[final];
      final++;
    }
  }

  for (int j = left; j <= right; j++) {
    vec[j] = temp[j];
  }
  return vec;
}

std::vector<int> mergeSort(std::vector<int> vec, int left, int right) {
  if (left < right) {
    vec = mergeSort(vec, left, (left + right) / 2);
    vec = mergeSort(vec, (left + right) / 2 + 1, right);
    vec = merge(vec, left, right);
  }
  return vec;
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
  std::map<int, std::vector<int>> matrix;
  readFrom(matrix, "input.txt");

  for (int i = 0; i < matrix[i].size(); ++i) {
    matrix[i] = mergeSort(matrix[i], 0, matrix[i].size() - 1);
    if ((i + 1) % 3 == 0) {
      std::reverse(matrix[i].begin(), matrix[i].end());
    }
  }

  writeTo(matrix, "output.txt");
}
