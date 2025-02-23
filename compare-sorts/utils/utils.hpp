#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int* parseData(const std::string& filename, int& size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error while trying to parse the file " << filename << std::endl;
        return nullptr;
    }

    size = 0;
    int value;
    while (file >> value) {
        size++;
    }
    
    int* data = new int[size];
    
    file.clear();
    file.seekg(0);

    for (int i = 0; i < size; i++) {
        file >> data[i];
    }

    file.close();
    return data;
}

int* copyArray(const int* source, int size) {
    int* copy = new int[size];
    std::copy(source, source + size, copy);
    return copy;
}
