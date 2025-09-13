#include <cctype>
#include <iostream>
#include <string>

struct tree {
        char inf;
        tree *right;
        tree *left;
        tree *parent;
};

tree *node(char x) {
    tree *n = new tree;
    n->inf = x;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;
    return n;
}

tree *create_tree(std::string str) {
    tree *tr = nullptr;
    for (int i = 0; i < str.length(); ++i) {
        tree *n = node(str[i]);
        if (str[i] == '-' || str[i] == '+') {
            tr->parent = n;
            n->left = tr;
            tr = n;
        } else if (str[i] == '/' || str[i] == '*') {
            if (isdigit(tr->inf)) {
                tr->parent = n;
                n->left = tr;
                tr = n;
            } else {
                n->parent = tr;
                n->left = tr->right;
                tr->right->parent = n;
                tr->right = n;
            }
        } else {
            if (!tr) {
                tr = n;
            } else {
                if (!(tr->right)) {
                    n->parent = tr;
                    n->left = tr->right;
                    tr->right = n;
                } else {
                    tree *x = tr->right;
                    while (x->right) {
                        x = x->right;
                    }
                    n->parent = x->parent;
                    x->right = n;
                }
            }
        }
    }
    return tr;
}

void postorder(tree *&root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->inf;
    }
}

void preorder(tree *&root) {
    if (root) {
        std::cout << root->inf;
        preorder(root->left);

        preorder(root->right);
    }
}

int main() {
    std::string s;
    std::cout << "Enter an expression: ";
    std::cin >> s;

    tree *tr = create_tree(s);

    std::cout << "Postifx: ";
    postorder(tr);
    std::cout << std::endl << "Prefix: ";
    preorder(tr);
    std::cout << std::endl;
}
