#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <iomanip>

#include "sorts/quick-sort.hpp"
#include "sorts/merge-sort.hpp"
#include "sorts/heap-sort.hpp"
#include "utils/utils.hpp"
#include "utils/sort-test.hpp"
#include "utils/report.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> <file4>" << endl;
        return 1;
    }

    const size_t numFiles = 4;
    const size_t numTests = 5;
    string fileNames[numFiles] = {argv[1], argv[2], argv[3], argv[4]};
    double results[numFiles][numTests][3]; 

    for (int j = 0; j < numTests; j++) {
        for (int i = 0; i < numFiles; i++) {
            int size;
            int* data = parseData(fileNames[i], size);
    
            if (!data) {
                cerr << "Error fetching data from file: " << fileNames[i] << endl;
                continue;
            }
    
            results[i][j][0] = testSort(quicksort, data, size, QuickSort);
            results[i][j][1] = testSort(mergesort, data, size, MergeSort);
            results[i][j][2] = testSort(heapsort, data, size, HeapSort);
            delete[] data; 
        }    
    }
    
    writeReport("report.txt", fileNames, results, numFiles, numTests);

    cout << "Report successfully created in report.txt" << endl;
    return 0;
}
