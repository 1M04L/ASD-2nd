#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <climits>

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

void sortFile(const std::string &fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) return;

    std::vector<int> numbers;
    int num;
    while (inFile >> num) {
        numbers.push_back(num);
    }

    std::sort(numbers.begin(), numbers.end());

    std::ofstream outFile(fileName);
    for (int n : numbers) {
        outFile << n << " ";
    }
}

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

void mergeFiles(const std::vector<std::string>& files) {
    std::vector<std::ifstream> inFiles;
    for (const auto& file : files) {
        inFiles.push_back(std::ifstream(file));
    }

    std::ofstream outFile("merged.txt");

    std::vector<int> currentValues(files.size());
    bool hasValues = false;

    for (size_t i = 0; i < files.size(); ++i) {
        if (inFiles[i] >> currentValues[i]) {
            hasValues = true;
        } else {
            currentValues[i] = INT_MAX; 
        }
    }

    while (hasValues) {
        int minValue = INT_MAX;
        int minIndex = -1;

        for (size_t i = 0; i < currentValues.size(); ++i) {
            if (currentValues[i] < minValue) {
                minValue = currentValues[i];
                minIndex = i;
            }
        }

        outFile << minValue << " ";

        if (!(inFiles[minIndex] >> currentValues[minIndex])) {
            currentValues[minIndex] = INT_MAX; 
        }

        hasValues = false;
        for (size_t i = 0; i < currentValues.size(); ++i) {
            if (currentValues[i] != INT_MAX) {
                hasValues = true;
                break;
            }
        }
    }

    for (auto& inFile : inFiles) {
        inFile.close();
    }
}

void fileSort(const std::string &fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) return;

    std::vector<int> numbers;
    int num;
    while (inFile >> num) {
        numbers.push_back(num);
    }

    int partSize = numbers.size() / 4;
    std::vector<std::string> fileParts(4);

    for (int i = 0; i < 4; ++i) {
        fileParts[i] = "part" + std::to_string(i) + ".txt";
        std::ofstream outFile(fileParts[i]);

        int start = i * partSize;
        int end = (i == 3) ? numbers.size() : (i + 1) * partSize;

        for (int j = start; j < end; ++j) {
            outFile << numbers[j] << " ";
        }
    }

    for (auto& part : fileParts) {
        sortFile(part);
    }

    mergeFiles(fileParts);
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

    fileSort(fileName); 
    //std::cout << "File after merge and sorting: ";
    //printFileContent("merged.txt");

    return 0;
}

//sortFile и fileSort выполняют разные функции(sF сортирует каждый файл отдельно и те который получаются в результате работы fS)
//fS выполняет естественную сортировку слиянием на 4х файлах
