#include <iostream>
#include <stack>
using namespace std;

// Node definition for BST
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Iterator class for BST
class BSTIterator {
public:
    BSTIterator(Node* root) {
        pushAll(root);
    }

    bool hasNext() {
        return !s.empty();
    }

    int next() {
        Node* node = s.top();
        s.pop();
        pushAll(node->right);
        return node->data;
    }
    
    BSTIterator& operator++() {
        if (!s.empty()) {
            Node* node = s.top();
            s.pop();
            pushAll(node->right);
        }
        return *this;
    }

private:
    stack<Node*> s;
    void pushAll(Node* node) {
        while (node) {
            s.push(node);
            node = node->left;
        }
    }
};

// Example usage of the BSTIterator class
int main() {
    Node* root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(7);
    root->left->left = new Node(1);
    root->left->right = new Node(4);
    root->right->left = new Node(6);
    root->right->right = new Node(9);

    BSTIterator it(root);
    while (it.hasNext()) {
        cout << it.next() << " ";
    }
    cout << endl;
    
    // Testing prefix increment operator
    cout << "Using prefix increment operator: ";
    BSTIterator it2(root);
    ++it2;
    cout << it2.next() << endl;
    return 0;
}