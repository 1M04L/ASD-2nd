#include "BSTree.h"
#include <iostream>

int main() {
    BinaryTree* tree = new BinarySearchTree();
    
    tree->insert(50);
    tree->insert(30);
    tree->insert(70);
    tree->insert(20);
    tree->insert(40);
    tree->insert(60);
    tree->insert(228);
    
    std::cout << "Поиск 40: ";
    if (tree->find(40)) {
        std::cout << "найден";
    } else {
        std::cout << "не найден";
    }
    std::cout << std::endl;
    
    std::cout << "Поиск 1448: ";
    if (tree->find(1448)) {
        std::cout << "найден";
    } else {
        std::cout << "не найден";
    }
    std::cout << std::endl;
    
    std::cout << "Уровень 50: " << tree->getNodeLevel(50) << std::endl;
    std::cout << "Уровень 20: " << tree->getNodeLevel(20) << std::endl;
    std::cout << "Уровень 70: " << tree->getNodeLevel(70) << std::endl;
    
    std::cout << "Удаление 20: ";
    if (tree->remove(20)) {
        std::cout << "успешно";
    } else {
        std::cout << "не удалось";
    }
    
    std::cout << "Поиск 20 после удаления: ";
    if (tree->find(20)) {
        std::cout << "найден";
    } else {
        std::cout << "ненайден";
    }
    std::cout << std::endl;
    
    std::cout << "\nДерево в порядке уровней\n";
    tree->printLevelOrder();
    
    delete tree;
    
    BinarySearchTree bst1;
    bst1.insert(10);
    bst1.insert(5);
    bst1.insert(15);
    
    BinarySearchTree bst2 = bst1; 
    BinarySearchTree bst3 = std::move(bst1); 
    
    bst2 = bst3; 
    bst1 = std::move(bst2); 
    
    return 0;
}
