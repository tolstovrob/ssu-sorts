#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define alphabetSize 256

void genBadChar(string &needle, int size, int badChar[alphabetSize]) {
  for (int i = 0; i < alphabetSize; i++)
    badChar[i] = size;
  for (int i = 0; i < size; i++)
    badChar[(int)needle[i]] = i;
}

vector<int> BM(string &haystack, string &needle) {
  int n = haystack.size();
  int m = needle.size();
  int badChar[alphabetSize];
  genBadChar(needle, m, badChar);
  vector<int> result;
  int s = 0;

  while (s <= (n - m)) {
    int i = m - 1;
    while (i >= 0 && needle[i] == haystack[s + i])
      i--;
    if (i < 0) {
      result.push_back(s);
      s += (s + m < n) ? badChar[haystack[s + m]] : 1;
    } else {
      s += max(1, i - badChar[haystack[s + i]]);
    }
  }

  return result;
}

int main() {
  string haystack, needle;
  cout << "String:" << endl;
  cin >> haystack;
  cout << "Substring:" << endl;
  cin >> needle;
  vector<int> ans = BM(haystack, needle);
  for (int pos : ans) {
    for (int i = pos; i < pos + (int)needle.length(); i++)
      cout << haystack[i];
    cout << " " << pos << endl;
  }

  return 0;
}
