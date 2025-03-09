#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>



bool createFileWithRandomNumbers(const std::string &fileName, int numbersCount, int maxNumberValue) {
    std::ofstream outFile(fileName);
    if (!outFile) return false;

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, maxNumberValue);

    for (int i = 0; i < numbersCount; ++i)
        outFile << dist(gen) << " ";

    return true;
}



bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) return false;
    
    int prev, current;
    if (!(inFile >> prev)) return true;
    
    while (inFile >> current) {
        if (current < prev) return false;
        prev = current;
    }
    
    return true;
}



void sortFile(const std::string &fileName) 




int createAndSortFile(const std::string &fileName, int numbersCount, int maxNumberValue) {
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }
    
    sortFile(fileName);
    
    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }
    
    return 1;
}

void printFileContent(const std::string &fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cout << "cant open yr file" << std::endl;
        return;
    }

    int num;
    while (inFile >> num) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::string fileName = "file.txt";
    int numbersCount = 1000000;
    int maxNumberValue = 100000;
    
    for (int i = 0; i < 10; i++) {
        int result = createAndSortFile(fileName, numbersCount, maxNumberValue);
        if (result == 1) {
            std::cout << "Test passed." << std::endl;
        } else if (result == -1) {
            std::cout << "Test failed: can't create file." << std::endl;
                             printFileContent(fileName);

        } else if (result == -2) {
            std::cout << "Test failed: file isn't sorted." << std::endl;
                             printFileContent(fileName);

        }
    }
    
    return 0;
}
