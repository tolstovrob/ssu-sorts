#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <iomanip>

#include "../utils/utils.hpp"
#include "../utils/sort-test.hpp"

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
