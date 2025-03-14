#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <random>
#include <algorithm>

void generateRandomNumbers(const std::string& fileName, int numbersCount, int maxNumberValue) {
    std::ofstream file(fileName);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, maxNumberValue);
    for (int i = 0; i < numbersCount; i++) {
        file << dist(gen) << " ";
    }
    file.close();
}

void split(const std::string& filename, const std::string& fileSplit1, const std::string& fileSplit2) {
    std::ifstream file(filename);
    std::ofstream file_1(fileSplit1);
    std::ofstream file_2(fileSplit2);

    int value;
    bool toggle = true;
    while (file >> value) {
        if (toggle) {
            file_1 << value << " ";
        } else {
            file_2 << value << " ";
        }
        toggle = !toggle;
    }
}

void merge(int p, std::ifstream inputFile[2], std::ofstream outputFile[2]) {
    int mas[2];
    bool hasData[2] = {false, false};
    
    if (inputFile[0] >> mas[0]) {
        hasData[0] = true;
    }
    if (inputFile[1] >> mas[1]) {
        hasData[1] = true;
    }
    
    int n = 0;
    while (hasData[0] || hasData[1]) {
        int i = 0, j = 0;
        while (hasData[0] && hasData[1] && i < p && j < p) {
            if (mas[0] < mas[1]) {
                outputFile[n] << mas[0] << " ";
                if (!(inputFile[0] >> mas[0])) hasData[0] = false;
                i++;
            } else {
                outputFile[n] << mas[1] << " ";
                if (!(inputFile[1] >> mas[1])) hasData[1] = false;
                j++;
            }
        }
        while (hasData[0] && i < p) {
            outputFile[n] << mas[0] << " ";
            if (!(inputFile[0] >> mas[0])) hasData[0] = false;
            i++;
        }
        while (hasData[1] && j < p) {
            outputFile[n] << mas[1] << " ";
            if (!(inputFile[1] >> mas[1])) hasData[1] = false;
            j++;
        }
        n = 1 - n;
    }
}

void fileSort(std::string& filename) 

bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream inFile(fileName);
    int value;
    if (!(inFile >> value)) return true;
    int prev = value;
    int current;
    while (inFile >> current) {
        if (current < prev) return false;
        prev = current;
    }
    return true;
}

void printFileContent(const std::string &fileName) {
    std::ifstream inFile(fileName);
    int value;
    while (inFile >> value) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string fileName = "file.txt";
    int numbersCount = 1000000;
    int maxNumberValue = 100000;
    
    generateRandomNumbers(fileName, numbersCount, maxNumberValue);

    fileSort(fileName);
    return 0;
} 
