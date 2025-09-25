/*
* Cites used:
Source 1:   https://www.geeksforgeeks.org/dsa/introduction-to-avl-tree/
Source 2:   https://www.w3schools.com/dsa/dsa_data_avltrees.php
Source 3:   https://visualgo.net/en/bst
Source 4:   https://stackoverflow.com/questions/63276864/is-post-order-traversal-bottom-up-traversal-and-pre-order-traversal-top-do
 */

/*
 *  "Helpers" are implemented to handle the actual purpose of the
 *  function its helping just so the actual function has and easier
 *  time handling pre and post cases. I got the idea for helpers from ChatGPT
 *  when I asked how do I add a newline after my prints within the function.
*/

#include "AVL.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
// Node Functions (Purpose in AVL.h)
Node::Node() {
    this->UFID = 0;
    this->name = "";
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(int id, std::string name) {
    this->UFID = id;
    this->name = name;
    this->left = nullptr;
    this->right = nullptr;
}

int Node::getID() {
    return UFID;
}

std::string Node::getName() {
    return name;
}

void Node::setID(int id) {
    this->UFID = id;
}

void Node::setName(std::string name) {
    this->name = name;
}


// AVLTree Functions (Purpose in AVL.h)
void AVLTree::fail() {
    std::cout << "unsuccessful" << std::endl;
}

void AVLTree::passed() {
    std::cout << "successful" << std::endl;
}

void AVLTree::comma() {
    std::cout << ", ";
}

void AVLTree::nLine() {
    std::cout << std::endl;
}

//Used ai chatbot to help me understand unsigned int vs signed int comparison issues
void AVLTree::printNames(std::vector<std::string> &names) {
    for (size_t i = 0; i < names.size(); i++) {
        std::cout << names.at(i);
        if (i < names.size() - 1) {
            comma();
        }
    }
    nLine();
}


AVLTree::AVLTree() {
    root = nullptr;
}

Node* AVLTree::getRoot() {
    return root;
}

void AVLTree::setRoot(Node* root) {
    this->root = root;
}

Node *AVLTree::rotateLeft(Node* node) {
    if (node == nullptr || node->right == nullptr) {
        return node;
    }

    Node* rightNode = node->right;
    Node* rightLeftNode = rightNode->left;

    rightNode->left = node;
    node->right = rightLeftNode;

    return rightNode;
}

Node *AVLTree::rotateRight(Node* node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }

    Node* leftNode = node->left;
    Node* leftRightNode = leftNode->right;

    leftNode->right = node;
    node->left = leftRightNode;

    return leftNode;
}

Node* AVLTree::minValueNode(Node* node) {
    if (node == nullptr) {
        return node;
    }

    // Keeps track of current node
    Node* current = node;

    // Finds the left most node from the starting node
    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

int AVLTree::height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

int AVLTree::getBalance(Node *node) {
    if (node == nullptr) {return 0;}
    return height(node->left) - height(node->right);
}

// Help from Source 2
Node* AVLTree::insertHelper(Node *node, std::string &name, int id) {
    // Once node finds its location it gets made and sent to its caller
    if (node == nullptr) {
        Node* n = new Node(id, name);
        return n;
    }

    // Recursively puts the node where it needs to go
    if (id < node->getID()) {
        node->left = insertHelper(node->left, name, id);
    } else if (id > node->getID()) {
        node->right = insertHelper(node->right, name, id);
    } else {
        // Safety net in case the same node is called on itself
        return node;
    }

    //Rebalance the tree once the node is added with the recursion above at each step

    // Gets the balance of the current node
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && id < node->left->getID()) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balance > 1 && id > node->left->getID()) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && id > node->right->getID()) {
        return rotateLeft(node);
    }

    // Right Left
    if (balance < -1 && id < node->right->getID()) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Assuming root needed no rotations returns the root
    return node;
}

void AVLTree::insert(std::string name, int id) {
    // Checks if UFID is 8 digits
    if (id < 10000000 || id > 99999999) {
        fail();
        return;
    }

    if (!isNameValid(name)) {
        fail();
        return;
    }

    // Checks for duplicate id
    if (searchIDHelper(root, id) != nullptr) {
        fail();
        return;
    }

    root = insertHelper(root, name, id);
    passed();
}

// Help from Source 2
Node *AVLTree::removeHelper(Node *node, int id) {
    if (node == nullptr) {
        return node;
    }

    if (id < node->getID()) { // Searches for node on the left
        node->left = removeHelper(node->left, id);
    } else if (id > node->getID()) { // Searches for node on right
        node->right = removeHelper(node->right, id);
    } else {  // Found the node

        // No children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        // One child
        if (node->left == nullptr) { // Child is on right
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {  // Child is on left
            Node* temp = node->left;
            delete node;
            return temp;
        } else {
            Node* temp = minValueNode(node->right); // Finds inorder successor
            node->UFID = temp->getID();             // Changes node to delete to  its successor
            node->name = temp->getName();
            node->right = removeHelper(node->right, temp->getID()); // Deletes true successor
        }

        //Rebalance the tree once the correct node is deleted

        // Gets current balance of node
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;

    }

    return node;
}

void AVLTree::remove(int id) {
    if (searchIDHelper(root, id) == nullptr) {
        fail();
        return;
    }

    root = removeHelper(root, id);
    passed();
}

void AVLTree::printOrderHelper(Node *node, std::vector<std::string> &names, const int &type) {
    if (node == nullptr) {
        return;
    }

    if (type == 1) { // In-order
        // Travel down left side of tree
        printOrderHelper(node->left, names, 1);

        // Add name to name vector
        names.push_back(node->getName());

        //Go down the right subtree of current node
        printOrderHelper(node->right, names, 1);
    }

    if (type == 2) { // Pre-order
        names.push_back(node->getName());

        // Traverse the left side of tree
        printOrderHelper(node->left, names, 2);

        // Traverse the right side of tree
        printOrderHelper(node->right, names, 2);
    }

    if (type == 3) { // Post-order
        // Travel down the left subtree
        printOrderHelper(node->left, names, 3);

        // Travel down the right subtree
        printOrderHelper(node->right, names, 3);

        // Print out the name of current node
        names.push_back(node->getName());
    }

}

void AVLTree::printInOrder() { // Number 1
    if (root == nullptr) {
        nLine();
        return;
    }

    std::vector<std::string> names;
    printOrderHelper(root, names, 1);
    printNames(names);
}

void AVLTree::printPreOrder() {
    if (root == nullptr) {
        nLine();
        return;
    }

    std::vector<std::string> names;
    printOrderHelper(root, names, 2);
    printNames(names);
}

void AVLTree::printPostOrder() {
    if (root == nullptr) {
        nLine();
        return;
    }

    std::vector<std::string> names;
    printOrderHelper(root, names, 3);
    printNames(names);
}

void AVLTree::treeInOrder(Node *node, std::vector<Node *> &nodes) {
    if (node == nullptr) {
        return;
    }

    // Traverse the left of tree
    treeInOrder(node->left, nodes);

    // puts the current node in vector
    nodes.push_back(node);

    // Traverses the right side
    treeInOrder(node->right, nodes);

    //Note: only when a node has no more left nodes is it added to vector
}

void AVLTree::removeInOrder(int n) {
    if (root == nullptr) {
        fail();
        return;
    }

    std::vector<Node *> nodes;
    treeInOrder(root, nodes);

    if (n < 0 || n >= static_cast<int>(nodes.size())) {
        fail();
        return;
    }

    // Removes the nth node
    remove(nodes.at(n)->getID());
}

// Checks to see if name fits requirement (had help from ChatGPT regarding syntax of C++) Ex: isaplha
bool AVLTree::isNameValid(const std::string& name) {
    if (name.empty()) {
        return false;
    }

    for (char c : name) {
        if (!(std::isalpha(c) || c == ' ')) {
            return false;
        }
    }

    return true;
}


Node* AVLTree::searchIDHelper(Node* node, int id) {
    // Base Case
    if (node == nullptr) { // Returns null if the node does not exist
        return node;
    } else if (node->getID() == id) { // If node is found, returns node of location
        return node;
    }

    if (id < node->getID()) {
        return searchIDHelper(node->left, id);
    }

    return searchIDHelper(node->right, id);

}

void AVLTree::search(int id) {
    Node* location = searchIDHelper(root, id);

    if (location == nullptr) {
        fail();
    } else {
        std::cout << location->getName() << std::endl;
    }
}

void AVLTree::searchNameHelper(Node* node, const std::string& name, std::vector<int>& ids) {
    if (node == nullptr) {
        return;
    }

    // If name matches adds id to vector
    if (node->getName() == name) {
        ids.push_back(node->getID());
    }

    // Traverse down left subtree
    searchNameHelper(node->left, name, ids);
    // Traverse down right subtree
    searchNameHelper(node->right, name, ids);
}

void AVLTree::search(std::string name) {
    std::vector<int> ids;
    searchNameHelper(root, name, ids);

    if (ids.empty()) { // Checks if id's have been found
        fail();
    } else { // prints out all the id's
        for (size_t i = 0; i < ids.size(); i++) {
            std::cout << ids.at(i);
            if ( i < ids.size() - 1) { // If there is more id's to print adds a comma after current id
                comma();
            }
        }
        nLine();
    }
}

void AVLTree::printLevelCount() {
    std:: cout << height(root) << std::endl;
}

// Had help from ChatGPT to make sure I did not have any memory leaks
void AVLTree::deleteTree(Node *node) {
    if (node == nullptr) {
        return;
    }

    //Traverses the right side
    deleteTree(node->left);
    //Traverses the left side
    deleteTree(node->right);
    delete node;
}

AVLTree::~AVLTree() {
    deleteTree(root);
    root = nullptr;
}

