#include <iostream>
#include "AVL.h"

int main() {
    AVLTree tree;
    tree.insert("Brandon", 45679999);
    tree.insert("Brian", 35459999);
    tree.insert("Briana", 87879999);
    tree.insert("Bella", 95469999);
    tree.printInOrder();
    tree.remove(45679999);
    tree.removeInOrder(2);
    tree.printInOrder();
    return 0;
}