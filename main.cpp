#include "HuffmanTree.h"
#include <iostream>
#include <fstream>

int main() {
    HuffmanTree huffman;
    
    std::string inputFile = "test.txt";
    std::string compressedFile = "compressed.bin";
    
    double compressionRatio = huffman.encode(inputFile, compressedFile);
    
    if (compressionRatio > 0) {
        std::cout << "Compression successful!" << std::endl;
        std::cout << "Compression ratio: " << compressionRatio << std::endl;
    } else {
        std::cout << "Compression failed!" << std::endl;
        return 1;
    }
    
    std::cout << "\nHuffman Tree:" << std::endl;
    huffman.print();
    
    return 0;
}
