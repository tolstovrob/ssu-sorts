#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <functional>
#include <iomanip>

#include "sorts/quick-sort.hpp"
#include "sorts/merge-sort.hpp"
#include "sorts/heap-sort.hpp"
#include "utils/utils.hpp"

using namespace std;
using namespace std::chrono;

enum SORT {
  QuickSort,
  MergeSort,
  HeapSort
};

string enumToString(SORT sortName) {
    return sortName == SORT::QuickSort
        ? "quicksort"
        : sortName == SORT::MergeSort
        ? "mergesort"
        : "heapsort";
}

double testSort(function<void(int*, int)> sortFunc, int* data, int size, SORT sortName) {
  int* arr = copyArray(data, size);

  cout << "TEST: " << enumToString(sortName) << ", data size: " << size << endl;
  auto start = high_resolution_clock::now();
  sortFunc(arr, size);
  auto end = high_resolution_clock::now();
  cout << "TEST COMPLETED!" << endl << endl;

  duration<double> elapsed = end - start;

  delete[] arr;
  return elapsed.count() * 1000;
}

double testSort(function<void(int*, int, int)> sortFunc, int* data, int size, SORT sortName) {
  int* arr = copyArray(data, size);

  cout << "TEST: " << enumToString(sortName) << ", data size: " << size << endl;
  auto start = high_resolution_clock::now();
  sortFunc(arr, 0, size - 1);
  auto end = high_resolution_clock::now();
  cout << "TEST COMPLETED!" << endl << endl;

  duration<double> elapsed = end - start;

  delete[] arr;
  return elapsed.count() * 1000;
}

void writeReport(const string& filename, const string* fileNames, double results[][5][3], size_t numFiles, size_t numTests) {
    ofstream report(filename);
    if (!report.is_open()) {
        cerr << "Error creating report file!" << endl;
        return;
    }

    report << setw(25) << "File"
           << setw(10) << "Test"
           << setw(20) << "Quicksort (ms)"
           << setw(20) << "Mergesort (ms)"
           << setw(20) << "Heapsort (ms)" << endl;

    for (size_t i = 0; i < numFiles; i++) {
        for (size_t j = 0; j < numTests; j++) {
            report << setw(25) << fileNames[i]
                   << setw(10) << j + 1
                   << setw(20) << results[i][j][0]
                   << setw(20) << results[i][j][1]
                   << setw(20) << results[i][j][2] << endl;
        }
    }

    report << string(100, '-') << endl;

    report << setw(25) << "File"
           << setw(10) << "Test"
           << setw(20) << "Quicksort (ms)"
           << setw(20) << "Mergesort (ms)"
           << setw(20) << "Heapsort (ms)" << endl;

    for (size_t i = 0; i < numFiles; i++) {
        double avgQuicksort = 0.0;
        double avgMergesort = 0.0;
        double avgHeapsort = 0.0;

        for (size_t j = 0; j < numTests; j++) {
            avgQuicksort += results[i][j][0];
            avgMergesort += results[i][j][1];
            avgHeapsort += results[i][j][2];
        }

        avgQuicksort /= numTests;
        avgMergesort /= numTests;
        avgHeapsort /= numTests;

        report << setw(25) << fileNames[i]
               << setw(10) << "Avg"
               << setw(20) << fixed << setprecision(2) << avgQuicksort
               << setw(20) << fixed << setprecision(2) << avgMergesort
               << setw(20) << fixed << setprecision(2) << avgHeapsort << endl;
    }

    report.close();
}


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
