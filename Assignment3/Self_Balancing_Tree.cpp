#include<bits/stdc++.h>
class    BSearch {
private:
    struct Node {
        int key;
        int height;
        int size;
        Node* left;
        Node* right;

        Node(int key) : key(key), height(1), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int size(Node* node) {
        return node ? node->size : 0;
    }

    int bFactor(Node* node) {
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    void updateSize(Node* node) {
        node->size = 1 + size(node->left) + size(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        updateSize(y);
        updateSize(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        updateSize(x);
        updateSize(y);

        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        updateSize(node);

        if (bFactor(node) > 1) {
            if (bFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (bFactor(node) < -1) {
            if (bFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }

        return balance(node);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node* remove(Node* node, int key) {
        if (!node) return node;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }

        return balance(node);
    }

    bool find(Node* node, int key) {
        if (!node) return false;
        if (key < node->key) return find(node->left, key);
        if (key > node->key) return find(node->right, key);
        return true;
    }

    int orderOfKey(Node* node, int key) {
        if (!node) return 0;
        if (key <= node->key) return orderOfKey(node->left, key);
        return size(node->left) + 1 + orderOfKey(node->right, key);
    }

    int getByOrder(Node* node, int k) {
        if (!node) return -1;
        int leftSize = size(node->left);
        if (k < leftSize) return getByOrder(node->left, k);
        if (k == leftSize) return node->key;
        return getByOrder(node->right, k - leftSize - 1);
    }

public:
    BSearch() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    bool find(int key) {
        return find(root, key);
    }

    int orderOfKey(int key) {
        return orderOfKey(root, key);
    }

    int getByOrder(int k) {
        return getByOrder(root, k);
    }
};


int main() {
    BSearch tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    
    std::cout << "Find 10: " << tree.find(10) << std::endl;
    std::cout << "Find 25: " << tree.find(25) << std::endl;

    std::cout << "Order of key 15: " << tree.orderOfKey(15) << std::endl; 
    std::cout << "Order of key 10: " << tree.orderOfKey(10) << std::endl;

    std::cout << "Element with order 2: " << tree.getByOrder(2) << std::endl; 

    tree.remove(10);
    std::cout << "Find 10 after removal: " << tree.find(10) << std::endl;

    return 0;
}