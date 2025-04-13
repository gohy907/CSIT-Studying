#include <iostream>
#include <sstream>
#include <vector>

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
  if (!p)
    tr = NULL;
  else if (!v->left && !v->right) {
    if (p->left == v)
      p->left = NULL;
    if (p->right == v)
      p->right = NULL;
    delete v;
  } else if (!v->left || !v->right) { // если только один ребенок
    if (!p) {          // если удаляем корень, у которого 1 ребенок
      if (!v->left) {  // если есть правый ребенок
        tr = v->right; // он становится корнем
        v->parent = NULL;
      } else { // аналогично для левого

        tr = v->left;
        v->parent = NULL;
      }
    } else {
      if (!v->left) {       // если есть правый ребенок
        if (p->left == v) { // если удаляемый узел явл. левым ребенком
          p->left = v->right;
        } // ребенок удаляемого узла становится левым ребенком

        else {
          p->right = v->right;
        } ////ребенок удаляемого узла становится правым
        v->right->parent = p; // родителем ребенка становится его "дед"
      } else {                // аналогично для левого ребенка
        if (p->left == v)
          p->left = v->left;
        else
          p->right = v->left;
        v->left->parent = p;
      }
      delete v;
    }
  } else {                              // есть оба ребенка
    tree *succ = Next(tr, v->inf);      // следующий за удаляемым узлом
    v->inf = succ->inf;                 // присваиваем значение
    if (succ->parent->left == succ) {   // если succ левый ребенок
      succ->parent->left = succ->right; // его правый ребенок становится левым
      if (succ->right)                  // если этот ребенок существует
        succ->right->parent = succ->parent; // его родителем становится "дед"
    } else { // аналогично если succ - правsq ребенок
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
