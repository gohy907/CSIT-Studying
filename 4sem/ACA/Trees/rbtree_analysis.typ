#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#show: codly-init
= Красно-чёрное дерево

== Код программы

#codly(languages: codly-languages)
```cpp
enum Color { Black, Red };

class RBTree {
    private:
        struct Node {
                int inf;
                Node *left;
                Node *right;
                Node *parent;
                Color color;

                Node(int inf)
                    : inf(inf),
                      left(nullptr),
                      right(nullptr),
                      parent(nullptr),
                      color(Black) {}
        };
        Node *nil;
        Node *find_helper(Node *node, int x);
        void insert_helper(Node *node);
        bool is_fictive(Node *node);
        void left_rotation(Node *node);
        void right_rotation(Node *node);

        void insert_fixup_1(Node *node); // Вызывается, если при вставке y ---
                                         // красный, т.е. нарушается 4 правило

        void insert_fixup_2(Node *x);

    public:
        Node *root;
        RBTree() {
            nil = new Node(0);
            root = nil;
        }
        void set_left(Node *parent_node, Node *new_node);
        void set_right(Node *parent_node, Node *new_node);
        Node *find(int x);

        void insert(int inf);
};

bool RBTree::is_fictive(Node *node) {
    if (!node) {
        return true;
    }
    return false;
}

RBTree::Node *RBTree::find(int x) { return find_helper(root, x); }

RBTree::Node *RBTree::find_helper(RBTree::Node *node, int x) {
    if (!node || x == node->inf) {
        return node;
    }
    if (x < node->inf) {
        return find_helper(node->left, x);
    }
    return find_helper(node->right, x);
}

void RBTree::set_left(RBTree::Node *parent_node, RBTree::Node *new_node) {
    parent_node->left = new_node;
    new_node->parent = parent_node;
}

void RBTree::set_right(RBTree::Node *parent_node, RBTree::Node *new_node) {
    parent_node->right = new_node;
    new_node->parent = parent_node;
}

void RBTree::insert_helper(RBTree::Node *x) {
    Node *y = nullptr;
    Node *iter_node = root;

    while (iter_node != nil) {
        y = iter_node;
        if (x->inf < iter_node->inf) {
            iter_node = iter_node->left;
        } else {
            iter_node = iter_node->right;
        }
    }

    x->parent = y;

    if (y == nullptr) {
        root = x;
    } else if (x->inf < y->inf) {
        y->left = x;
    } else {
        y->right = x;
    }

    x->left = nil;
    x->right = nil;
    x->color = Red;

    if (!x->parent || x->parent->color == Color::Red) {
        insert_fixup_1(x);
    }
}

void RBTree::insert(int inf) {
    RBTree::Node *x = new Node(inf);
    x->right = nil;
    x->left = nil;
    insert_helper(x);
}

void RBTree::insert_fixup_1(RBTree::Node *x) {
    if (!x->parent) {
        x->color = Black;
    } else {
        Node *y = x->parent;
        Node *g = y->parent;
        Node *u;
        if (y == g->left) {
            u = g->right;
        } else {
            u = g->left;
        }

        if (u->color == Color::Red) {
            g->color = Color::Red;
            y->color = Color::Black;
            u->color = Color::Black;
            insert_fixup_1(g);
        } else {
            if (x == y->left) {
                insert_fixup_2(y);
            } else {
                right_rotation(y);
                insert_fixup_2(x);
            }
        }
    }
}

void RBTree::left_rotation(RBTree::Node *x) {
    RBTree::Node *y = x->right;
    x->right = y->left;

    if (y->left != nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::right_rotation(RBTree::Node *y) {
    RBTree::Node *x = y->left;
    y->left = x->right;

    if (x->right != nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void RBTree::insert_fixup_2(RBTree::Node *x) {
    Node *y = x->parent;
    Node *g = y->parent;
    left_rotation(y);
    y->color = Black;
    g->color = Red;
}

```

== Анализ сложности

Бинарное дерево поиска называется красно-чёрным, если:
+ Все вершины покрашены в красный или чёрный цвет;
+ Корень дерево имеет чёрный цвет;
+ У каждой вершины ровно 2 сына, они могут быть чёрными листьями без ключей;
+ Дети красной вершины --- чёрные;
+ $forall v$ на любом нисходящем пути от $v$ до листа находится одно и то же количество чёрных вершин.


*Утверждение*: Если в красно-чёрном дереве содержится $n$ ключей, то глубина $h$ не превосходит $2 log_2(n+1)$.

*Доказательство:*

Докажем сначала лемму: если $x$ --- произвольная вершина, а $"bh"(x)$ --- чёрная глубина вершины $x$ (количество чёрных вершин в любом нисходящем пути из $x$ без учёта $x$), то в поддереве $x$ лежит по крайней мере $2^"bh"(x) - 1$ ключ.

Докажем это индукцией по $h(x)$.

База $h(x) = 0$ $==>$ $x$ --- лист и фиктивная чёрная вершина, ключей нет. В этом поддереве лежит $2^0 - 1 = 0$ ключей. *База верна.*

*Переход.* Возьмём вершину $x$ произвольной глубины. Пусть левый сын вершины $x$ — $L$, а правый — $R$. Тогда $"bh"(L) ≥ "bh"(x) - 1$ и $"bh"(R) ≥ "bh"(x) - 1$.

Равенство в этих неравенствах достигается, если сыновья соответственно чёрные, а неравенство, если они красные.

По предположению индукции, в левом поддереве будет находиться как минимум $2^"bh"(L) - 1$ ключ, а в правом — $2^"bh"(R) - 1$.
Суммарно в поддереве $x$ ключей будет как минимум

$
  1 + 2^("bh"(L)) - 1 + 2^("bh"(R)) - 1 >= 2^("bh"(x) - 1) + 2^("bh"(x) - 1) - 1 = 2^("bh"(x)) - 1
$

*Лемма доказана.*

Пусть $h$ --- высота всего дерева. Очевидно, что $"bh"("root")$, где $"root"$ — корень дерева, не меньше чем  $h/2$, так как по свойству красно-чёрного дерева, у красной вершины любой сын чёрный. Отсюда следует, что

$
  n >= 2^(h/2) - 1 ==> n + 1 >= 2^(h/2) <==> h/2 <= log_2 (n+1) <==> h <= 2 log_2 (n + 1)
$


Утверждение доказано.

То есть высота красно-чёрного дерева имеет сложность $O(log n)$.

Создание дерева, поиск, вставка и удаление в КЧД выполняется как в любом другом бинарном дереве поиска и работает за $O(h) = O(log(n))$.
