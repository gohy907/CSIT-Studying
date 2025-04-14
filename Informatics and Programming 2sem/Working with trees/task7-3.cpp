#include <iostream>
#include <sstream>
#include <vector>

struct tree {
  double inf;
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

void inorderDepth(tree *tr, std::vector<tree *> &vec, int depth, int k) {
  if (tr) {
    if (!(tr->left || tr->right) && k == depth) {
      vec.push_back(tr);
      return;
    } else if (k == depth) {
      return;
    }
    inorderDepth(tr->left, vec, depth, k + 1);
    inorderDepth(tr->right, vec, depth, k + 1);
  }
}

void inorder(tree *tr) {
  if (tr) {
    std::cout << tr->inf << " ";
    inorder(tr->left);
    inorder(tr->right);
  }
}
tree *Min(tree *tr) {
  if (!tr->left)
    return tr;
  else
    return Min(tr->left);
}

tree *Next(tree *tr, int x) {
  tree *n = find(tr, x);

  if (n->right) {
    return Min(n->right);
  }
  tree *y = n->parent;
  while (y && n == y->right) {
    n = y;
    y = y->parent;
  }
  return y;
}

void Delete(tree *&tr, tree *v) {
  tree *p = v->parent;
  if (!p && !(v->left || v->right)) {
    tr = nullptr;
  } else if (!p) {
    tree *succ = Next(tr, v->inf);
    v->inf = succ->inf;
    if (succ->parent->left == succ) {
      succ->parent->left = succ->right;
      if (succ->right)
        succ->right->parent = succ->parent;
    } else {
      succ->parent->right = succ->right;
      if (succ->right)
        succ->right->parent = succ->parent;
    }
    delete succ;
  } else if (!v->left && !v->right) {
    if (p->left == v)
      p->left = NULL;
    if (p->right == v)
      p->right = NULL;
    delete v;
  } else if (!v->left || !v->right) {
    if (!p) {
      if (!v->left) {
        tr = v->right;
        v->parent = NULL;
      } else {

        tr = v->left;
        v->parent = NULL;
      }
    } else {
      if (!v->left) {
        if (p->left == v) {
          p->left = v->right;
        }

        else {
          p->right = v->right;
        }
        v->right->parent = p;
      } else {
        if (p->left == v)
          p->left = v->left;
        else
          p->right = v->left;
        v->left->parent = p;
      }
      delete v;
    }
  } else {

    tree *succ = Next(tr, v->inf);
    v->inf = succ->inf;
    if (succ->parent->left == succ) {
      succ->parent->left = succ->right;
      if (succ->right)
        succ->right->parent = succ->parent;
    } else {
      succ->parent->right = succ->right;
      if (succ->right)
        succ->right->parent = succ->parent;
    }
    delete succ;
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

  std::cout << "Enter depth: ";
  int depth;
  std::cin >> depth;
  std::vector<tree *> leaves;
  inorderDepth(tr, leaves, depth, 0);
  if (leaves.size() == 0) {
    std::cout << "No leaves found" << std::endl;
    return 0;
  }

  double sm = 0;
  for (int i = 0; i < leaves.size(); ++i) {
    sm += leaves[i]->inf;
  }

  double average = sm / leaves.size();

  tree *aver = leaves[0];
  double min = std::abs(average - aver->inf);
  for (int i = 0; i < leaves.size(); ++i) {
    double dist = std::abs(average - leaves[i]->inf);
    if (dist < min) {
      min = dist;
      aver = leaves[i];
    }
  }

  Delete(tr, aver->parent->parent);
  inorder(tr);
  std::cout << std::endl;
}
