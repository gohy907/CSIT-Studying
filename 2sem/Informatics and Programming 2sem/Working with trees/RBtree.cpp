#include <iostream>
#include <sstream>
#include <vector>

enum color { red, black };

struct tree {
        int inf;
        tree *left;
        tree *right;
        tree *parent;
        bool isFictional;
        color color;
};

tree *ficLeaf(tree *&p) {
    tree *n = new tree;
    n->inf = 0;
    n->parent = p;
    n->right = nullptr;
    n->left = nullptr;
    n->color = red;
    n->isFictional = true;
    return n;
}

tree *node(tree *p, int x) {
    tree *n = new tree;
    n->inf = x;
    n->parent = p;
    n->right = ficLeaf(n);
    n->left = ficLeaf(n);
    n->color = red;
    n->isFictional = false;
    return n;
}

tree *root(int x) {
    tree *n = new tree;
    n->inf = x;
    n->parent = nullptr;
    n->right = ficLeaf(n);
    n->left = ficLeaf(n);
    n->color = black;
    n->isFictional = false;
    return n;
}

tree *grandparent(tree *&x) {
    if (x->parent->parent) {
        return x->parent->parent;
    }
    return nullptr;
}

tree *uncle(tree *&x) {
    tree *g = grandparent(x);
    if (!g) {
        return nullptr;
    }
    if (x->parent == g->left) {
        return g->right;
    }
    return g->left;
}

tree *brother(tree *&x) {
    if (x && x->parent) {
        if (x == x->parent->left) {
            return x->parent->right;
        } else {
            return x->parent->left;
        }
    }
    return nullptr;
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

void left_rotation(tree *&tr, tree *x) {
    tree *y = x->right; // y становится новым корнем
    x->right = y->left; // левое поддерево y переходит к x

    if (!(y->isFictional) && !(y->left->isFictional))
        y->left->parent = x;

    y->parent = x->parent; // родитель y теперь nil (бывший родитель x)

    // Особый случай - x был корнем:
    if (x->parent == nullptr)
        tr = y; // обновляем корень дерева
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;   // x становится левым потомком y
    x->parent = y; // y становится родителем x}
}
void right_rotation(tree *&tr, tree *x) {
    tree *y = x->left;  // y становится новым "верхним" узлом
    x->left = y->right; // правое поддерево y переходит к x

    if (!(y->isFictional) && !(y->right->isFictional))
        y->right->parent = x;

    y->parent = x->parent;

    // Особый случай - x был корнем:
    if (x->parent == nullptr)
        tr = y; // обновляем корень дерева
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;  // x становится правым потомком y
    x->parent = y; // y становится родителем x}
}

void insert_case1(tree *&tr, tree *x);
void insert_case2(tree *&tr, tree *x);
void insert_case3(tree *&tr, tree *x);
void insert_case4(tree *&tr, tree *x);
void insert_case5(tree *&tr, tree *x);

void insert_case1(tree *&tr, tree *x) {
    if (!(x->parent)) {
        x->color = black;
    } else {
        insert_case2(tr, x);
    }
}

void insert_case2(tree *&tr, tree *x) {
    if (x->parent->color == red) {
        insert_case3(tr, x);
    }
}

void insert_case3(tree *&tr, tree *x) {
    tree *U = uncle(x);
    tree *G = grandparent(x);
    if (!(U->isFictional) && U->color == red && x->parent->color == red) {
        x->parent->color = black;
        U->color = black;
        G->color = red;
        insert_case1(tr, G);
    } else {
        insert_case4(tr, x);
    }
}

void insert_case4(tree *&tr, tree *x) {
    tree *G = grandparent(x);
    if (x == x->parent->right && x->parent == G->left) {
        left_rotation(tr, x->parent);
        x = x->left;
    } else {
        if (x == x->parent->left && x->parent == G->right) {
            right_rotation(tr, x->parent);
            x = x->right;
        }
    }
    insert_case5(tr, x);
}

void insert_case5(tree *&tr, tree *x) {
    tree *G = grandparent(x);
    x->parent->color = black;
    G->color = red;
    if (x == x->parent->left && x->parent == G->left) {
        right_rotation(tr, G);
    } else {
        left_rotation(tr, G);
    }
}

void insert(tree *&tr, tree *prev, int x) {
    if (x < prev->inf && prev->left->isFictional) {
        prev->left = node(prev, x);
        insert_case1(tr, prev->left);
    } else {
        if (x > prev->inf && prev->right->isFictional) {
            prev->right = node(prev, x);
            insert_case1(tr, prev->right);
        } else {
            if (x < prev->inf && !(prev->left->isFictional)) {
                insert(tr, prev->left, x);
            } else {
                if (x > prev->inf && !(prev->right->isFictional)) {
                    insert(tr, prev->right, x);
                }
            }
        }
    }
}

void delete_case1(tree *&tr, tree *x);
void delete_case2(tree *&tr, tree *x);
void delete_case3(tree *&tr, tree *x);
void delete_case4(tree *&tr, tree *x);
void delete_case5(tree *&tr, tree *x);
void delete_case6(tree *&tr, tree *x);

void delete_case1(tree *&tr, tree *x) {
    if (!(x->parent)) {
        if (!(x->left->isFictional)) {
            tr = x->left;
        } else {
            tr = x->right;
        }
    } else {
        delete_case2(tr, x);
    }
}

void delete_case2(tree *&tr, tree *x) {
    tree *s = brother(x);
    if (s->color == red) {
        x->parent->color = red;
        s->color = black;
        if (x == x->parent->left) {
            left_rotation(tr, x->parent);
        } else {
            right_rotation(tr, x->parent);
        }
    }
    delete_case3(tr, x);
}

void delete_case3(tree *&tr, tree *x) {
    tree *s = brother(x);
    if (x->parent->color == black && s->color == black &&
        (s->left->isFictional || s->left->color == black) &&
        (s->right->isFictional || s->right->color == black)) {
        delete_case1(tr, x);
    } else {
        delete_case4(tr, x);
    }
}

void delete_case4(tree *&tr, tree *x) {
    tree *s = brother(x);
    if (x->parent->color == red && s->color == black &&
        (s->left->isFictional || s->left->color == black) &&
        (s->right->isFictional || s->right->color == black)) {
        s->color = red;
        x->parent->color = black;
    } else {
        delete_case5(tr, x);
    }
}

void delete_case5(tree *&tr, tree *x) {
    tree *s = brother(x);
    if (s->color == black) {
        s->color = red;
        if (x == x->parent->left &&
            (!(s->left->isFictional) && s->left->color == red) &&
            (s->right->isFictional || s->right->color == black)) {
            s->left->color = black;
            right_rotation(tr, s);
        } else if (x == x->parent->right &&
                   (!(s->right->isFictional) && s->right->color == red) &&
                   (s->left->isFictional || s->left->color == black)) {
            s->right->color = black;
            left_rotation(tr, s);
        }
    }
    delete_case6(tr, x);
}

void delete_case6(tree *&tr, tree *x) {
    tree *s = brother(x);
    s->color = x->color;
    x->parent->color = black;
    if (x == x->parent->left) {
        s->right->color = black;
        left_rotation(tr, x->parent);
    } else {
        s->left->color = black;
        right_rotation(tr, x->parent);
    }
}

void replace(tree *&tr, tree *x) {
    tree *ch;
    if (!(x->left->isFictional)) {
        ch = x->left;
        ch->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->left) {
                x->parent->left = ch;
            } else {
                x->parent->right = ch;
            }
        }
    } else {
        ch = x->right;
        ch->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->left) {
                x->parent->left = ch;
            } else {
                x->parent->right = ch;
            }
        }
    }
}

void deleteNode(tree *&tr, tree *&x) {
    if (!(x->right->isFictional || x->left->isFictional)) {
        tree *&buf = x->left;
        while (!(buf->right->isFictional)) {
            buf = buf->right;
        }
        x->inf = buf->inf;
        buf = ficLeaf(buf->parent);
    } else if (!(x->right->isFictional && x->left->isFictional)) {
        tree *ch;
        if (!(x->left->isFictional) && x->right->isFictional) {
            ch = x->left;
        } else if (x->left->isFictional && !(x->right->isFictional)) {
            ch = x->right;
        }
        replace(tr, x);
        if (x->color == black) {
            if (ch->color == red) {
                ch->color = black;
            } else {
                delete_case1(tr, x);
            }
        }
    } else {
        if (x->color == black) {
            delete_case1(tr, x);
            x->inf = 0;
            x->left = nullptr;
            x->right = nullptr;
            x->isFictional = true;
            x->color = red;
        } else {
            if (x == x->parent->left) {
                x->parent->left = ficLeaf(x->parent);
            } else {
                x->parent->right = ficLeaf(x->parent);
            }
        }
    }
}

void inorder(tree *tr) {
    if (!(tr->isFictional)) {
        {
            std::string s;
            if (tr->color == red) {
                s = "(r)";
            } else {
                s = "(b)";
            }
            std::cout << tr->inf << s << " ";
        }
        inorder(tr->left);
        inorder(tr->right);
    }
}

int countSum(tree *tr) {
    if (tr->isFictional) {
        return 0;
    }

    if (tr->left->isFictional && tr->right->isFictional) {
        return tr->inf;
    }

    return countSum(tr->left) + countSum(tr->right);
}

// 1. Дано дерево.Подсчитать сумму листьев.
int main() {
    std::string line;
    getline(std::cin, line);
    std::stringstream ss(line);

    std::vector<int> verices;
    int tmp;
    while (ss >> tmp) {
        verices.push_back(tmp);
    }

    tree *tr = root(verices[0]);
    for (int i = 1; i < verices.size(); ++i) {
        insert(tr, tr, verices[i]);
    }

    inorder(tr);
    std::cout << std::endl;

    int sum = countSum(tr);
    std::cout << "Sum of leaves: " << sum << std::endl;
}
