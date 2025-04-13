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
      } else {
        return;
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

bool found = false;
void inorder(tree *tr) {
  if (tr) {
    if (!(tr->left || tr->right) && tr->inf % 2 != 0) {
      std::cout << tr->inf << " ";
      found = true;
    }
    inorder(tr->left);
    inorder(tr->right);
  }
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

  inorder(tr);
  if (!found) {
    std::cout << "Odd leaves not found";
  }
  std::cout << std::endl;
}
