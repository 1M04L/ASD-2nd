#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <climits>

bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "cant open file: " << fileName << std::endl;
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, maxNumberValue);

    for (int i = 0; i < numbersCount; ++i) {
        file << dist(gen) << " ";
        if (!file) {
            std::cerr << "cant write into the file: " << fileName << std::endl;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool isFileContainsSortedArray(const std::string &fileName) {
    int valueNow = 0, valuePrev = INT_MIN;
    std::string ch;
    std::ifstream file(fileName);
    while (!file.eof()) {
        ch = "";
        file >> ch;
        if (ch != "") {
            valueNow = std::stoi(ch);
            if (valueNow < valuePrev)
                return false;
            valuePrev = valueNow;
        }
    }
    return true;
}

void split(const std::string &filename, const std::string &fileSplit1, const std::string &fileSplit2) {
    std::ifstream file(filename);
    std::ofstream file_1(fileSplit1);
    std::ofstream file_2(fileSplit2);

    int value;
    file >> value;

    while (!file.eof()) {
        file_1 << value << " ";
        file >> value;
        if (!file.eof()) {
            file_2 << value << " ";
            file >> value;
        }
    }

    file.close();
    file_1.close();
    file_2.close();
}

void Merge(const int p, std::ifstream *inputFile, std::ofstream *outputFile) {
    int *mas = new int[2];

    inputFile[0] >> mas[0];
    inputFile[1] >> mas[1];
    int n = 0;

    while (!inputFile[0].eof() && !inputFile[1].eof()) {
        int i = 0, j = 0;
        while (!inputFile[0].eof() && !inputFile[1].eof() && i < p && j < p) {
            if (mas[0] < mas[1]) {
                outputFile[n] << mas[0] << " ";
                inputFile[0] >> mas[0];
                i++;
            } else {
                outputFile[n] << mas[1] << " ";
                inputFile[1] >> mas[1];
                j++;
            }
        }
        while (!inputFile[0].eof() && i < p) {
            outputFile[n] << mas[0] << " ";
            inputFile[0] >> mas[0];
            i++;
        }
        while (!inputFile[1].eof() && j < p) {
            outputFile[n] << mas[1] << " ";
            inputFile[1] >> mas[1];
            j++;
        }
        n = 1 - n;
    }

    while (!inputFile[0].eof()) {
        outputFile[n] << mas[0] << " ";
        inputFile[0] >> mas[0];
    }
    while (!inputFile[1].eof()) {
        outputFile[n] << mas[1] << " ";
        inputFile[1] >> mas[1];
    }

    delete[] mas;
}

void fileSort(const std::string &inputFileName, const std::string &outputFileName) {
    std::string file_0 = "file_0.txt";
    std::string file_1 = "file_1.txt";
    std::string file_2 = "file_2.txt";
    std::string file_3 = "file_3.txt";

    split(inputFileName, file_0, file_1);
    int p = 1;

    while (true) {
        std::ifstream inputFile[2];
        std::ofstream outputFile[2];

        inputFile[0].open(file_0);
        inputFile[1].open(file_1);
        outputFile[0].open(file_2);
        outputFile[1].open(file_3);

        Merge(p, inputFile, outputFile);

        inputFile[0].close();
        inputFile[1].close();
        outputFile[0].close();
        outputFile[1].close();

        if (isFileContainsSortedArray(file_2) && isFileContainsSortedArray(file_3)) {
            break;
        }

        p *= 2;

        inputFile[0].open(file_2);
        inputFile[1].open(file_3);
        outputFile[0].open(file_0);
        outputFile[1].open(file_1);

        Merge(p, inputFile, outputFile);

        inputFile[0].close();
        inputFile[1].close();
        outputFile[0].close();
        outputFile[1].close();

        p *= 2;
    }

    std::ofstream outputFile(outputFileName);
    std::ifstream finalFile(file_2);
    int value;
    while (finalFile >> value) {
        outputFile << value << " ";
    }
    finalFile.close();
    outputFile.close();
}

int main() {
    std::string inputFileName = "random_numbers.txt";
    std::string outputFileName = "sorted_numbers.txt";
    int numbersCount = 1000000;
    int maxNumberValue = 1000000;

    if (createFileWithRandomNumbers(inputFileName, numbersCount, maxNumberValue)) {
        std::cout << "File created successfully: " << inputFileName << std::endl;
    } else {
        std::cerr << "cant create file: " << inputFileName << std::endl;
        return 1;
    }

    fileSort(inputFileName, outputFileName);

    if (isFileContainsSortedArray(outputFileName)) {
        std::cout << " sorted correctly: " << outputFileName << std::endl;
    } else {
        std::cerr << " sorted uncorrectly!" << std::endl;
    }

    return 0;
}
