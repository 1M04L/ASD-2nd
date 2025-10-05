
#include "hash_table.h"
#include <iostream>

int main() {
    try {
        HashTable<std::string> table1(5);
        HashTable<std::string> table2(5, new HashFunction2());
        
        table1.insert(1, "One");
        table1.insert(2, "Two");
        table1.insert(3, "Three");
        table1.insert(11, "Eleven"); // Коллизия
        
        std::cout << "Table 1 (HashFunction1):" << std::endl;
        table1.print();
        
        // Проверка оператора []
        std::cout << "\ntable1[2] = " << table1[2] << std::endl;
        table1[4] = "Four"; // Добавление через operator[]
        
        std::cout << "\nContains key 3: " << (table1.contains(3) ? "Yes" : "No") << std::endl;
        table1.remove(3);
        std::cout << "After removing key 3:" << std::endl;
        table1.print();
        
        // Смена хеш-функции
        table1.setHashFunction(new HashFunction3());
        std::cout << "\nAfter switching to HashFunction3:" << std::endl;
        table1.print();
        
        table1.resize(8);
        std::cout << "\nAfter resizing to 8:" << std::endl;
        table1.print();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
