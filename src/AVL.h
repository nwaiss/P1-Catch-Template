#ifndef AVL_H
#define AVL_H
#include <string>
#include <vector>

struct Node {
    // Pointers to Left and Right nodes
    struct Node* left;
    struct Node* right;

    // Data
    int UFID;
    std::string name;

    // Constructor
    Node();
    Node(int id, std::string name);

    // Getters
    int getID();
    std::string getName();

    // Setters
    void setID(int id);
    void setName(std::string name);
};

class AVLTree {
private:
    // Root Node of tree
    struct Node* root;

    // Insert/Remove Helpers
    Node* insertHelper(Node* node, std::string& name, int id);
    Node* removeHelper(Node* node, int id);

    // Returns height of a node
    int height(Node* node);

    // Returns balance factor (height(left) - height(right))
    int getBalance(Node* node);

    // Printing Helpers
    void printOrderHelper(Node* node, std::vector<std::string>& names, const int& type);
    Node* searchIDHelper(Node* node, int id);
    void searchNameHelper(Node* node, const std::string& name, std::vector<int>& ids);

    // nth node in-order traversal
    void treeInOrder(Node* node, std::vector<Node*>& nodes);

    // Prints in code (I got laz)
    void fail(); // std::cout << "unsuccessful" << endl;
    void passed(); // std::cout << "successful" << endl;
    void comma(); // std::cout << ", ";
    void nLine(); // std::cout << endl;
    void printNames(std::vector<std::string>& names);

    void deleteTree(Node* node);

public:
    //Constructor
    AVLTree();

    // Getter
    struct Node* getRoot();

    // Setter
    void setRoot(Node* root);

    // Insertion and Removal commands
    void insert(std::string name, int id);
    void remove(int id);

    // Search for Name corresponding to an ID, returns "unsuccessful" if not exist
    void search(int id);

    // Search for all students with the inserted name (in pre-order traversal) and prints each ID, returns "unsuccessful" if not exist
    void search(std::string name);

    // Performs a right rotation on inserted node
    Node* rotateRight(Node* node);

    // Performs a left rotation on inserted node
    Node* rotateLeft(Node* node);

    // Returns the minimum value within a tree given the root (used for subtrees)
    Node* minValueNode(Node* node);

    //Tree Printing
    // Print out a comma separated inorder traversal of the names in the tree
    void printInOrder();
    // Print out a comma-separated preorder traversal of the names in the tree
    void printPreOrder();
    // Print out a comma-separated postorder traversal of the names in the tree
    void printPostOrder();
    // End of tree printing

    // Prints the number of levels that exist in the tree, prints 0 if the head of the tree is null
    void printLevelCount();

    // Remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc)
    void removeInOrder(int n);

    bool isNameValid(const std::string& name);

    ~AVLTree();
};

#endif //AVL_H