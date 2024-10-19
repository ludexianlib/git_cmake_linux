#include <iostream>

enum Color { RED, BLACK };

template <typename T>
class RBTreeNode {
public:
    T data;                   // 节点数据
    Color color;               // 节点颜色（红色或黑色）
    RBTreeNode* left;          // 左子节点
    RBTreeNode* right;         // 右子节点
    RBTreeNode* parent;        // 父节点

    RBTreeNode(T value)
        : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RBTree {
private:
    RBTreeNode<T>* root;       // 根节点
    RBTreeNode<T>* TNULL;      // 空节点（哨兵节点）

    // 初始化空节点，所有叶子节点都用TNULL代替
    void initializeNULLNode(RBTreeNode<T>* node, RBTreeNode<T>* parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = BLACK;
    }

    // 前序遍历
    void preOrderHelper(RBTreeNode<T>* node) {
        if (node != TNULL) {
            std::cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // 中序遍历
    void inOrderHelper(RBTreeNode<T>* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            std::cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    // 后序遍历
    void postOrderHelper(RBTreeNode<T>* node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            std::cout << node->data << " ";
        }
    }

    // 查找树中的某个键值
    RBTreeNode<T>* searchTreeHelper(RBTreeNode<T>* node, T key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // 左旋转
    void leftRotate(RBTreeNode<T>* x) {
        RBTreeNode<T>* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // 右旋转
    void rightRotate(RBTreeNode<T>* x) {
        RBTreeNode<T>* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // 插入后的平衡调整
    void fixInsert(RBTreeNode<T>* k) {
        RBTreeNode<T>* u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // 叔叔节点
                if (u->color == RED) {
                    // Case 1: 叔叔是红色
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // Case 2: k是左孩子
                        k = k->parent;
                        rightRotate(k);
                    }
                    // Case 3: k是右孩子
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // 叔叔节点

                if (u->color == RED) {
                    // Case 1: 叔叔是红色
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // Case 2: k是右孩子
                        k = k->parent;
                        leftRotate(k);
                    }
                    // Case 3: k是左孩子
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    // 删除节点后的修复操作
    void fixDelete(RBTreeNode<T>* x) {
        RBTreeNode<T>* s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    // 替换节点操作
    void rbTransplant(RBTreeNode<T>* u, RBTreeNode<T>* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // 删除节点的帮助函数
    void deleteNodeHelper(RBTreeNode<T>* node, T key) {
        RBTreeNode<T>* z = TNULL;
        RBTreeNode<T>* x, * y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            std::cout << "Couldn't find key in the tree" << std::endl;
            return;
        }

        y = z;
        Color yOriginalColor = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }

    // 找到子树中的最小节点
    RBTreeNode<T>* minimum(RBTreeNode<T>* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

public:
    RBTree() {
        TNULL = new RBTreeNode<T>(0);
        TNULL->color = BLACK;
        root = TNULL;
    }

    void preOrder() {
        preOrderHelper(this->root);
    }

    void inOrder() {
        inOrderHelper(this->root);
    }

    void postOrder() {
        postOrderHelper(this->root);
    }

    RBTreeNode<T>* searchTree(T k) {
        return searchTreeHelper(this->root, k);
    }

    void insert(T key) {
        RBTreeNode<T>* node = new RBTreeNode<T>(key);
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;

        RBTreeNode<T>* y = nullptr;
        RBTreeNode<T>* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    void deleteNode(T data) {
        deleteNodeHelper(this->root, data);
    }

    // 清理内存
    void clear(RBTreeNode<T>* node) {
        if (node != TNULL) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    ~RBTree() {
        clear(root);
        delete TNULL;
    }
};

int main() {
    RBTree<int> tree;

    tree.insert(55);
    tree.insert(40);
    tree.insert(65);
    tree.insert(60);
    tree.insert(75);
    tree.insert(57);

    std::cout << "Inorder traversal before deletion:" << std::endl;
    tree.inOrder();
    std::cout << std::endl;

    tree.deleteNode(40);
    std::cout << "Inorder traversal after deletion of 40:" << std::endl;
    tree.inOrder();
    std::cout << std::endl;

    return 0;
}
