#pragma once

#include <iostream>
#include <chrono>

#include "../utils/utils.hpp"

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