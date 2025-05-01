#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
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

std::map<int, std::list<std::pair<int, double>>>
createAdjMatrix(bool isWeight, bool isOrient) {
  std::map<int, std::list<std::pair<int, double>>> l_Adj;
  std::ifstream in("input.txt");
  int x, y;
  double w;
  while (in.peek() != EOF) {
    std::string line;
    getline(in, line);
    std::stringstream ss(line);
    ss >> x >> y >> w;

    if (!isWeight)
      w = 1.0;
    auto it_x = l_Adj.find(x);
    bool fl = true;
    if (it_x != l_Adj.end()) {
      for (auto it_y = it_x->second.begin(); it_y != it_x->second.end(); it_y++)
        if (it_y->first == y) {
          fl = false;
          break;
        }
    }
    if (isOrient) {
      if (fl) {
        l_Adj[x].push_back(std::make_pair(y, w));

        if (l_Adj.find(y) == l_Adj.end()) {

          l_Adj[y].push_back(std::make_pair(0, 0));
          auto it = l_Adj.find(y);
          it->second.erase(it->second.begin());
        }
      }
    } else if (fl) {
      l_Adj[x].push_back(std::make_pair(y, w));
      l_Adj[y].push_back(std::make_pair(x, w));
    }
  }
  return l_Adj;
}

void outputGraph(std::map<int, std::list<std::pair<int, double>>> l_Adj,
                 bool isWeight) {
  for (auto it = l_Adj.begin(); it != l_Adj.end(); it++) {
    std::cout << it->first << " : ";
    if (isWeight) {
      for (auto it_1 = it->second.begin(); it_1 != it->second.end(); it_1++)

        std::cout << "{" << it_1->first << ", " << it_1->second << "};";
    } else {
      for (auto it_1 = it->second.begin(); it_1 != it->second.end(); ++it_1)
        std::cout << it_1->first << "; ";
    }
    std::cout << std::endl;
  }
}

std::vector<int>
BFSMod(std::map<int, std::list<std::pair<int, double>>> adjMatrix, int x) {
  std::vector<int> path;
  for (auto it = adjMatrix[x].begin(); it != adjMatrix[x].end(); ++it) {
    path.push_back((*it).first);
  }
  return path;
}

std::vector<int>
allSources(std::map<int, std::list<std::pair<int, double>>> adjMatrix) {
  std::vector<int> sources;
  for (auto it = adjMatrix.begin(); it != adjMatrix.end(); ++it) {
    int x = (*it).first;
    std::vector<int> vertices = BFSMod(adjMatrix, x);
    if (std::find(vertices.begin(), vertices.end(), x) == vertices.end()) {
      if (vertices.size() == adjMatrix.size() - 1) {
        sources.push_back(x);
      }
    } else if (vertices.size() == adjMatrix.size()) {
      sources.push_back(x);
    }
  }
  return sources;
}

int main() {
  std::map<int, std::list<std::pair<int, double>>> adjMatrix =
      createAdjMatrix(false, true);
  outputGraph(adjMatrix, false);
  std::cout << std::endl;
  std::vector<int> sources = allSources(adjMatrix);
  for (int i = 0; i < sources.size(); ++i) {
    std::cout << sources[i] << " ";
  }
  std::cout << std::endl;
}
