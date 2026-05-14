#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#show: codly-init
= AVL-дерево

== Код программы

#codly(languages: codly-languages)
```cpp
struct AVLNode {
        int inf;
        AVLNode *left = nullptr;
        AVLNode *right = nullptr;
        int height;
};

AVLNode *newNode(int k) {
    AVLNode *n = new AVLNode;
    n->inf = k;
    n->height = 1;
    return n;
}

int height(AVLNode *node) {
    if (node) {
        return node->height;
    }
    return 0;
}

int getBalance(AVLNode *node) {
    if (node) {
        return height(node->left) - height(node->right);
    }
    return 0;
}

AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode *insert(AVLNode *node, int inf) {
    if (!node) {
        return newNode(inf);
    }
    if (inf < node->inf) {
        node->left = insert(node->left, inf);
    } else if (inf > node->inf) {
        node->right = insert(node->right, inf);
    } else {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && inf < node->left->inf)
        return rightRotate(node);

    if (balance < -1 && inf > node->right->inf)
        return leftRotate(node);

    if (balance > 1 && inf > node->left->inf) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && inf < node->right->inf) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode *minValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

AVLNode *deleteNode(AVLNode *root, int inf) {
    if (!root) {
        return root;
    }
    if (inf < root->inf) {
        root->left = deleteNode(root->left, inf);
    } else if (inf > root->inf) {
        root->right = deleteNode(root->right, inf);
    } else {
        if (!root->left || !root->right) {
            AVLNode *temp;
            if (root->left) {
                temp = root->left;
            } else {
                temp = root->right;
            }

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            AVLNode *temp = minValueNode(root->right);
            root->inf = temp->inf;
            root->right = deleteNode(root->right, temp->inf);
        }
    }

    if (!root)
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(AVLNode *root) {
    if (root) {
        inorder(root->left);
        std::cout << root->inf << " ";
        inorder(root->right);
    }
}

void preorder(AVLNode *root) {
    if (root) {
        std::cout << root->inf << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

bool search(AVLNode *root, int inf) {
    if (!root) {
        return false;
    }
    if (root->inf == inf) {
        return true;
    }
    if (inf < root->inf) {
        return search(root->left, inf);
    }
    return search(root->right, inf);
}

```

AVL-дерево является частным случаем двоичного дерева поиска. Как
и красно-чёрное дерево, оно является самобалансирующимся.

Основным его свойством является то, что в каждый момент времени $abs(h(L) − h(R)) ≤ 1$.
Это достигается с помощью выполнения поворотов: если в какой-то момент разность
высот поддеревьев превысила 1, происходит перебалансировка.
Если соблюдается это свойство, то количество вершин в дереве с высотой $n$ пропорционально $(n + 2)$-ому числу Фибоначчи.
Так как они растут экспоненциально, то высота дерева с $n$ листьями пропорциональна $log(n)$.

Тогда операции вставки,
поиска и удаления выполняются за $O(log(n))$.
