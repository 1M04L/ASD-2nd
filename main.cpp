#include "BinaryTree.h"
#include <iostream>

int main() {
    BinaryTree tree;
    std::cout << "Tree is empty: " << (tree.isEmpty() ? "true" : "false") << "\n";

    tree.insert(10);
    tree.insert(-5);
    tree.insert(15);
    tree.insert(3228);
    tree.insert(7);
    tree.insert(1288);
    tree.insert(107);

    tree.printLevelOrder();
    std::cout << "\nMin key: " << tree.getMinKey() << "\n";
    std::cout << "Max key: " << tree.getMaxKey() << "\n";
    std::cout << "\nTree is balanced: " << (tree.isBalanced() ? "true" : "false") << "\n";
    std::cout << "\nTree horizontal view:\n";
    tree.printHorizontal(10, 5);
    return 0;
}
