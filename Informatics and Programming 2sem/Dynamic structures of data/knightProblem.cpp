#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T> struct Queue {
  T inf;
  Queue<T> *next;
};

template <typename T> void push(Queue<T> *&h, Queue<T> *&t, T x) {
  Queue<T> *r = new Queue<T>;
  r->inf = x;
  r->next = nullptr;
  if (!h && !t) {
    h = t = r;
  }

  else {
    t->next = r;
    t = r;
  }
}

template <typename T> T pop(Queue<T> *&h, Queue<T> *&t) {
  T i = h->inf;
  Queue<T> *r = h;
  h = h->next;
  if (!h) {
    t = nullptr;
  }
  delete r;
  return i;
}

template <typename T> T top(Queue<T> *&h) {
  T i = h->inf;
  return i;
}

template <typename T> bool empty(Queue<T> *&h) { return (h == nullptr); }

struct Square {
  int x = -1;
  int y = -1;
};

Square strToSquare(std::string str) {
  Square square;
  square.x = str[0] - 'A';
  if (!std::isdigit(str[1])) {
    square.y = -1;
    return square;
  }
  square.y = std::stoi(str.substr(1)) - 1;
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

  Queue<Square> *h = nullptr;
  Queue<Square> *t = nullptr;
  push(h, t, start);
  while (!empty(h)) {
    Square current = pop(h, t);
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

      push(h, t, next);
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

  if (!(validPosition(start) && validPosition(finish))) {
    if (!validPosition(start)) {
      std::cout << "Invalid start position" << std::endl;
    }
    if (!validPosition(finish)) {
      std::cout << "Invaild finish position" << std::endl;
    }

    return 0;
  }

  std::vector<std::vector<Square>> table = bfs(start, finish);

  std::vector<std::string> vec;
  while (start != finish) {
    vec.push_back(squareToStr(finish));
    finish = table[finish.x][finish.y];
  }
  vec.push_back(squareToStr(start));
  std::reverse(vec.begin(), vec.end());

  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
}
