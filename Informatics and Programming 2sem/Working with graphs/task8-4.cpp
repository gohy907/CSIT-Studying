#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <vector>

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

void add_cycles(std::vector<int> pr, std::vector<std::vector<int>> &cycles,
                std::vector<std::vector<int>> &cycles_sort, int start,
                int end) {
  int cur = end;
  std::vector<int> tmp;
  while (cur != start) {
    tmp.push_back(cur);
    cur = pr[cur];
  }
  tmp.push_back(start);
  std::reverse(tmp.begin(), tmp.end());
  std::vector<int> tmp1 = tmp;
  std::sort(tmp1.begin(), tmp1.end());
  bool flag = true;
  for (int i = 0; i < cycles_sort.size(); ++i) {
    if (cycles_sort[i] == tmp1) {
      flag = false;
      break;
    }
  }
  if (flag) {
    cycles.push_back(tmp);
  }
  cycles_sort.push_back(tmp1);
}

void DFS(std::map<int, std::list<std::pair<int, double>>> adjMatrix,
         std::vector<int> &order, std::vector<int> &pr, int x) {
  pr[x] = 1;
  for (auto it = adjMatrix[x].begin(); it != adjMatrix[x].end(); ++it) {
    if (pr[(*it).first] == 0) {
      DFS(adjMatrix, order, pr, x);
    }
  }
  order.push_back(x);
}

void findLoop(std::map<int, std::list<std::pair<int, double>>> adjMatrix, int x,
              std::vector<int> &used, std::vector<int> &pr,
              std::vector<std::vector<int>> &cycles,
              std::vector<std::vector<int>> &cycles_sort) {
  used[x] = 1;
  for (auto it = adjMatrix[x].begin(); it != adjMatrix[x].end(); ++it) {
    int cur = (*it).first;
    if (pr[x] == cur) {
      continue;
    }
    if (used[cur] == 0) {
      pr[cur] = x;
      findLoop(adjMatrix, cur, used, pr, cycles, cycles_sort);
    } else if (used[cur] == 1) {
      add_cycles(pr, cycles, cycles_sort, cur, x);
    }
  }
  used[x] = 0;
}
std::vector<std::vector<int>>
findLoopHelper(std::map<int, std::list<std::pair<int, double>>> adjMatrix) {
  std::vector<int> verices;
  std::vector<std::vector<int>> cycles;
  std::vector<std::vector<int>> cycles_sort;
  for (auto it = adjMatrix.begin(); it != adjMatrix.end(); ++it) {
    int x = it->first;
    std::vector<int> used(adjMatrix.size());
    std::vector<int> pr(adjMatrix.size());
    for (int i = 0; i < pr.size(); ++i) {
      pr[i] = -1;
    }
    findLoop(adjMatrix, x, used, pr, cycles, cycles_sort);
  }

  for (int i = 0; i < cycles.size(); ++i) {
    cycles[i].push_back(cycles[i][0]);
  }
  return cycles;
}

int main() {
  std::map<int, std::list<std::pair<int, double>>> adjMatrix =
      createAdjMatrix(false, false);
  outputGraph(adjMatrix, false);

  std::cout << std::endl;
  std::vector<std::vector<int>> loops = findLoopHelper(adjMatrix);
  for (int i = 0; i < loops.size(); ++i) {
    for (int j = 0; j < loops[i].size(); ++j) {
      std::cout << loops[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
