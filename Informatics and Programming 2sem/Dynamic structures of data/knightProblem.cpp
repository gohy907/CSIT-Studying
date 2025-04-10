#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace gohy {

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

int solve(std::string strStart, std::string strFinish) {
  Square start = strToSquare(strStart);
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
  return vec.size();
}
} // namespace gohy

#include <iostream>
#include <map>
#include <vector>
namespace Ezhkin_Kot {

class Queue {
private:
  struct Node {
    std::string value;
    Node *next;
    Node(std::string &val) : value(val), next(nullptr) {}
  };

  Node *frontNode = nullptr;
  Node *backNode = nullptr;

public:
  void push(std::string &value) {
    Node *newNode = new Node(value);
    if (!backNode) {
      frontNode = backNode = newNode;
    } else {
      backNode->next = newNode;
      backNode = newNode;
    }
  }

  void pop() {
    if (!empty()) {
      Node *temp = frontNode;
      frontNode = frontNode->next;
      delete temp;
      if (!frontNode) {
        backNode = nullptr;
      }
    }
  }

  std::string front() { return frontNode->value; }

  bool empty() { return frontNode == nullptr; }

  ~Queue() {
    while (!empty()) {
      pop();
    }
  }
};

class Graph {
private:
  std::map<std::string, std::vector<std::string>> adj;

public:
  // Add an edge (undirected)
  void addEdge(std::string &u, std::string &v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // Set all possible moves
  void setHorseGraph() {
    std::vector<std::pair<int, int>> movesXY = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    for (char x = 'A'; x <= 'H'; ++x) {
      for (int y = 1; y <= 8; ++y) {
        std::string beginCell = std::string(1, x) + std::to_string(y);
        for (int i = 0; i < 8; ++i) {
          char nx = x + movesXY[i].first;
          int ny = y + movesXY[i].second;
          if (nx >= 'A' && nx <= 'H' && ny >= 1 && ny <= 8) {
            std::string endCell = std::string(1, nx) + std::to_string(ny);
            addEdge(beginCell, endCell);
          }
        }
      }
    }
  }

  // BFS to find minimal sequence of moves
  int shortestPath(std::string &start, std::string &end) {
    std::map<std::string, bool> visited;
    std::map<std::string, std::string> prev;
    Queue queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty()) {
      std::string current = queue.front();
      queue.pop();

      if (current == end)
        break;

      for (std::string &neighbor : adj[current]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          prev[neighbor] = current;
          queue.push(neighbor);
        }
      }
    }

    if (!visited[end]) {
      std::cout << "Path not found." << std::endl;
      return 0;
    }

    std::vector<std::string> path;
    for (std::string at = end; at != start; at = prev[at]) {
      path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path.size();
  }
};

int solve(std::string u, std::string v) {
  Graph g;
  g.setHorseGraph();

  return g.shortestPath(u, v);
}
} // namespace Ezhkin_Kot

int randFromRange(int start, int end) {
  return rand() % (end - start + 1) + start;
}

int main() {
  srand(time(0));
  char *rows = new char[]{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  char *columns = new char[]{'1', '2', '3', '4', '5', '6', '7', '8'};

  int gohyTotal = 0;
  int Ezhkin_KotTotal = 0;
  int n = 100000;
  for (int i = 0; i < n; ++i) {
    int x = randFromRange(0, 7);
    int y = randFromRange(0, 7);

    std::string start;
    start += rows[y];
    start += columns[x];

    x = randFromRange(0, 7);
    y = randFromRange(0, 7);

    std::string finish;
    finish += rows[y];
    finish += columns[x];

    int gohy = gohy::solve(start, finish);
    int Ezhkin_Kot = Ezhkin_Kot::solve(start, finish);

    std::cout << "Start: " << start << ", finish: " << finish << ". ";
    if (gohy == Ezhkin_Kot) {
      std::cout << "Algorithms are equal";
    } else if (gohy > Ezhkin_Kot) {
      std::cout << "Ezhkin_Kot's algorithm is better";
      ++Ezhkin_KotTotal;
    } else {
      std::cout << "gohy's algorithm is better";
      ++gohyTotal;
    }

    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Ezhkin_Kot's algorithm is better in " << Ezhkin_KotTotal
            << " cases out of " << n << std::endl;
  std::cout << "gohy's algorithm is better in " << gohyTotal << " cases out of "
            << n << std::endl;
}
