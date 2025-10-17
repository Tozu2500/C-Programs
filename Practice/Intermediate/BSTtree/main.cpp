#include <iostream>
#include <memory>

// ============================================================================
// Binary Search Tree Implementation
// ============================================================================
template<typename T>
class BST {
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(T val) : data(val) {}
    };
    
    std::unique_ptr<Node> root;
    
public:
    // Insert
    void insert(T val) {
        root = insertHelper(std::move(root), val);
    }

    // Search
    bool search(const T& val) const {
        return searchHelper(root.get(), val);
    }

    // Delete
    void remove(const T& val) {
        root = removeHelper(std::move(root), val);
    }

    // Traversals
    void inorder() const {
        inorderHelper(root.get());
        std::cout << "\n";
    }

    void preorder() const {
        preorderHelper(root.get());
        std::cout << "\n";
    }

    void postorder() const {
        postorderHelper(root.get());
        std::cout << "\n";
    }
    
private:
    // Insert helper
    std::unique_ptr<Node> insertHelper(std::unique_ptr<Node> node, T val) {
        if (!node) return std::make_unique<Node>(val);
        
        if (val < node->data)
            node->left = insertHelper(std::move(node->left), val);
        else if (val > node->data)
            node->right = insertHelper(std::move(node->right), val);
        // duplicates ignored
        return node;
    }

    // Search helper
    bool searchHelper(const Node* node, const T& val) const {
        if (!node) return false;
        if (val == node->data) return true;
        if (val < node->data) return searchHelper(node->left.get(), val);
        return searchHelper(node->right.get(), val);
    }

    // Delete helper
    std::unique_ptr<Node> removeHelper(std::unique_ptr<Node> node, const T& val) {
        if (!node) return nullptr;

        if (val < node->data) {
            node->left = removeHelper(std::move(node->left), val);
        } else if (val > node->data) {
            node->right = removeHelper(std::move(node->right), val);
        } else {
            // Case 1: No child
            if (!node->left && !node->right) {
                return nullptr;
            }
            // Case 2: One child
            else if (!node->left) {
                return std::move(node->right);
            } else if (!node->right) {
                return std::move(node->left);
            }
            // Case 3: Two children
            else {
                Node* minNode = findMin(node->right.get());
                node->data = minNode->data;
                node->right = removeHelper(std::move(node->right), minNode->data);
            }
        }
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    // Traversal helpers
    void inorderHelper(const Node* node) const {
        if (!node) return;
        inorderHelper(node->left.get());
        std::cout << node->data << " ";
        inorderHelper(node->right.get());
    }

    void preorderHelper(const Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        preorderHelper(node->left.get());
        preorderHelper(node->right.get());
    }

    void postorderHelper(const Node* node) const {
        if (!node) return;
        postorderHelper(node->left.get());
        postorderHelper(node->right.get());
        std::cout << node->data << " ";
    }
};

// ============================================================================
// Main function to play around with the BST
// ============================================================================
int main() {
    BST<int> tree;

    // Insert some values
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    std::cout << "Initial traversals:\n";
    std::cout << "Inorder:   "; tree.inorder();
    std::cout << "Preorder:  "; tree.preorder();
    std::cout << "Postorder: "; tree.postorder();

    // Search
    std::cout << "\nSearch results:\n";
    std::cout << "Contains 40? " << (tree.search(40) ? "Yes" : "No") << "\n";
    std::cout << "Contains 90? " << (tree.search(90) ? "Yes" : "No") << "\n";

    // Delete a node
    std::cout << "\nDeleting 70...\n";
    tree.remove(70);
    std::cout << "Inorder after deletion: "; tree.inorder();

    // Delete a leaf
    std::cout << "\nDeleting 20...\n";
    tree.remove(20);
    std::cout << "Inorder after deletion: "; tree.inorder();

    // Delete root
    std::cout << "\nDeleting 50 (root)...\n";
    tree.remove(50);
    std::cout << "Inorder after deletion: "; tree.inorder();

    return 0;
}
