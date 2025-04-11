#include <iostream>
#include <sstream>

struct tree {
  int inf;
  tree *left;
  tree *right;
  tree *parent;
};

tree *node(int x) {
  tree *n = new tree;
  n->inf = x;
  n->parent = nullptr;
  n->right = nullptr;
  n->left = nullptr;
  return n;
}

void insert(tree *&tr, int x) {
  tree *n = node(x);
  if (!tr)
    tr = n;
  else {
    tree *y = tr;
    while (y) {
      if (n->inf > y->inf) {
        if (y->right) {
          y = y->right;
        } else {
          n->parent = y;
          y->right = n;
          break;
        }
      } else if (n->inf < y->inf) {
        if (y->left) {
          y = y->left;
        } else {
          n->parent = y;
          y->left = n;
          break;
        }
      }
    }
  }
}

tree *find(tree *tr, int x) {
  if (!tr || x == tr->inf) {
    return tr;
  }
  if (x < tr->inf) {
    return find(tr->left, x);
  }
  return find(tr->right, x);
}

int main() {
  std::string line;
  getline(std::cin, line);
  std::stringstream ss(line);

  tree *tr = nullptr;
  int tmp;
  while (ss >> tmp) {
    insert(tr, tmp);
  }

  int x;
  std::cout << "Enter x: ";
  std::cin >> x;

  tree *nodeX = find(tr, x);

  if (nodeX) {
    int sum = 0;
    nodeX = nodeX->parent;
    while (nodeX) {
      sum += nodeX->inf;
      nodeX = nodeX->parent;
    }

    std::cout << "Sum of elders: " << sum << std::endl;
  } else {
    std::cout << "X not found" << std::endl;
  }
}
