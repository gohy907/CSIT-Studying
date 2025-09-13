#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>

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

int main() {
  std::map<int, std::list<std::pair<int, double>>> adjMatrix =
      createAdjMatrix(false, true);
  outputGraph(adjMatrix, false);

  int x;
  std::cout << "Enter vertice: ";
  std::cin >> x;

  std::cout << std::endl << adjMatrix[x].size() << std::endl;
}
