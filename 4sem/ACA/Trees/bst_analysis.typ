#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#show: codly-init
= Двоичное дерево поиска

== Код программы

#codly(languages: codly-languages)
```cpp
struct Node {
        int key;
        Node *left;
        Node *right;

        Node(int key)
            : key(key),
              left(nullptr),
              right(nullptr) {}
};

Node *search(Node *root, int key) {
    if (!root || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

Node *insert(Node *root, int key) {
    if (!root) {
        return new Node(key);
    } else if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

Node *remove(Node *root, int key) {
    if (!root) {
        return root;
    }
    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else if (root->left && root->right) {
        root->key = minimum(root->right)->key;
        root->right = remove(root->right, root->key);
    } else {
        if (root->left) {
            root = root->left;
        } else if (root->right) {
            root = root->right;
        } else {
            root = nullptr;
        }
    }

    return root;
}

void inorder(Node *root) {
    if (root) {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}

void preorder(Node *root) {
    if (root) {
        std::cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->key << " ";
    }
}
```

== Анализ сложности

Рассмотрим основные функции:

#table(
  columns: (auto, auto),
  [Создание узла], [$O(1)$],
  [Вставка узла], [$O(h)$],
  [Удаление узла], [$O(h)$],
  [Поиск узла], [$O(h)$],
  [Поиск минимального (максимального) узла], [$O(h)$],
  [Симметричный, прямой и обратный обходы], [$O(n)$],
)

Здесь $n$ --- количество узлов в дереве, $h$ --- высота дерева.

=== Основные операции

Создание узла занимает $O(1)$ времени, а вставка узла за $O(h)$, так как чтобы найти ему подходящее место, в худшем случае нужно пройти до листьев дерева.

Поэтому создание всего дерева занимает $O(3 * n) = O(n)$, потому что в каждом узле находится информация в виде числа и указателей на левого и правого сыновей.

Обходы дерева занимают $O(n)$, потому что мы обрабатываем все узлы дерева, проходясь по каждому один раз.

Остальные функции занимают $O(h)$, потому что, как и для вставки, в худшем случае нужно пройти до листьев дерева.

=== Высота дерева

Рассмотрим теперь оценку для высоты дерева.

В лучшем случае высота дерева будет составлять $O(log n)$, потому что мы можем подобрать так значения, чтобы последовательно наполнять дерево уровень за уровнем, и на каждом уровне будет в 2 раза больше узлов, чем на предыдущем.

В среднем случае при вставке случайных чисел высота дерева будет составлять $O(log n)$.

В худшем случае дерево может выродиться в цепь, и высота будет иметь сложность $O(n)$.

