#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

std::map<int, std::list<std::pair<int, double>>>
createAdjMatrix(bool isWeigth, bool isOrient) {
    std::map<int, std::list<std::pair<int, double>>> l_Adj;
    std::ifstream in("input.txt");
    int x, y;
    double w;
    while (in.peek() != EOF) {
        std::string line;
        getline(in, line);
        std::stringstream ss(line);
        ss >> x >> y >> w;

        if (!isWeigth)
            w = 1.0;
        auto it_x = l_Adj.find(x);
        bool fl = true;
        if (it_x != l_Adj.end()) {
            for (auto it_y = it_x->second.begin(); it_y != it_x->second.end();
                 it_y++)
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

void dijkstra(const std::map<int, std::list<std::pair<int, double>>> &adjMatrix,
              int start, std::map<int, double> &distances,
              std::map<int, std::vector<int>> &paths) {

    for (auto it = adjMatrix.begin(); it != adjMatrix.end(); ++it) {
        distances[it->first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;

    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        std::greater<std::pair<double, int>>>
        pq;
    pq.push({0, start});

    std::map<int, int> prev;

    while (!pq.empty()) {
        double current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_dist > distances[u]) {
            continue;
        }

        for (auto edge = adjMatrix.at(u).begin(); edge != adjMatrix.at(u).end();
             ++edge) {
            int v = edge->first;
            double weight = edge->second;

            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                prev[v] = u;
                pq.push({distances[v], v});
            }
        }
    }

    for (auto node = adjMatrix.begin(); node != adjMatrix.end(); ++node) {
        int v = node->first;
        std::vector<int> path;
        if (distances[v] != std::numeric_limits<double>::infinity()) {
            for (int current = v; current != start; current = prev[current]) {
                path.push_back(current);
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
        }
        paths[v] = path;
    }
}

void dijkstraHelper(std::map<int, std::list<std::pair<int, double>>> adjMatrix,
                    int start) {
    std::map<int, double> distances;
    std::map<int, std::vector<int>> paths;
    dijkstra(adjMatrix, start, distances, paths);
    for (auto node = adjMatrix.begin(); node != adjMatrix.end(); ++node) {
        int v = node->first;
        if (v == start) {
            continue;
        }
        std::cout << "Vertice " << v << ": ";
        if (distances[v] == std::numeric_limits<double>::infinity()) {
            std::cout << "is not reachable" << std::endl;
        } else {
            std::cout << "distance = " << distances[v] << ", path: ";
            for (int u : paths[v]) {
                std::cout << u << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    std::map<int, std::list<std::pair<int, double>>> adjMatrix =
        createAdjMatrix(true, false);

    int start_vertex = 0;

    dijkstraHelper(adjMatrix, start_vertex);
}
