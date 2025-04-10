#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T> struct Stack {
  T inf;
  Stack<T> *next;
};

template <typename T> void push(Stack<T> *&h, T x) {
  Stack<T> *r = new Stack<T>;
  r->inf = x;
  r->next = h;
  h = r;
}

template <typename T> T pop(Stack<T> *&h) {
  T i = h->inf;
  Stack<T> *r = h;
  h = h->next;
  delete r;
  return i;
}

template <typename T> bool empty(Stack<T> *&stack) {
  return (stack == nullptr);
}

struct Square {
  int x = -1;
  int y = -1;
};

Square strToSquare(std::string str) {
  Square square;
  square.x = str[0] - 'A';
  square.y = str[1] - '1';
  return square;
}

std::string squareToStr(Square square) {
  std::string str;
  str += square.x + 'A';
  str += square.y + '1';
  return str;
}

bool validPosition(Square s) {
  return (s.x >= 0 && s.x <= 7 && s.y >= 0 && s.y <= 7);
}

bool operator==(Square a, Square b) { return (a.x == b.x) && (a.y == b.y); }

bool operator!=(Square a, Square b) { return !(a == b); }

int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
Square emptySquare = {-1, -1};

std::vector<std::vector<Square>> bfs(Square start, Square finish) {
  std::vector<std::vector<Square>> table;

  for (int i = 0; i < 8; ++i) {
    std::vector<Square> tmp;
    for (int j = 0; j < 8; ++j) {
      tmp.push_back(emptySquare);
    }
    table.push_back(tmp);
  }

  Stack<Square> *d;
  push(d, start);
  while (!empty(d)) {
    Square current = pop(d);
    for (int i = 0; i < 8; ++i) {
      Square next{current.x + dx[i], current.y + dy[i]};
      if (!validPosition(next)) {
        continue;
      }

      if (table[next.x][next.y] == emptySquare) {
        table[next.x][next.y] = current;
      } else {
        continue;
      }

      if (next == finish) {
        return table;
      }

      push(d, next);
    }
  }
  return table;
}

int main() {
  std::string strStart;
  std::string strFinish;

  std::cout << "Enter start square: ";
  std::cin >> strStart;
  Square start = strToSquare(strStart);

  std::cout << "Enter final square: ";
  std::cin >> strFinish;
  Square finish = strToSquare(strFinish);

  std::vector<std::vector<Square>> table = bfs(start, finish);

  std::vector<std::string> vec;
  while (start != finish) {
    vec.push_back(squareToStr(finish));
    finish = table[finish.x][finish.y];
  }

  std::reverse(vec.begin(), vec.end());

  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
}
