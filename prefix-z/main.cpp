#include <iostream>
#include <string>
#include <vector>

// aba#ababababa

std::vector<int> prefix(std::string s) {
  std::vector<int> result(s.length());
  result[0] = 0;

  for (int i = 1; i < s.length(); i++) {
    int k = result[i - 1];

    while (k > 0 && s[i] != s[k]) {
      k = result[k - 1];
    }
    if (s[i] == s[k]) {
      k++;
    }
    result[i] = k;
  }
  return result;
}

std::vector<int> z(std::string s) {
  std::vector<int> result(s.length());

  int left = 0, right = 0;

  for (int i = 1; i < s.length(); i++) {
    result[i] = std::max(0, std::min(right - i, result[i - left]));

    while (i + result[i] < s.length() && s[result[i]] == s[i + result[i]]) {
      result[i]++;
    }
    if (i + result[i] > right) {
      left = i;
      right = i + result[i];
    }
  }
  return result;
}

std::vector<int> kmp(std::string s, std::string pattern) {
  int patternLength = pattern.length();
  std::vector<int> result(s.length());
  std::vector<int> p = prefix(pattern + "#" + s);
 
  int count = 0;
  for (int i = patternLength; i < p.size(); i++) {
    if (p[i] == patternLength) {
      result[count++] = i - 2 * patternLength + 1;
    }
  }
  return result;
}

int main() {
  std::cout << "Enter string:" << std::endl;
  std::string str;
  std::cin >> str;

  std::cout << "Enter pattern:" << std::endl;
  std::string pattern;
  std::cin >> pattern;

  std::vector<int> pref = prefix(str);
  std::vector<int> zf = z(str);
  std::vector<int> kmpf = kmp(str, pattern);

  std::cout << "Prefix function:" << std::endl;
  for (int i = 0; i < pref.size(); i++) {
    std::cout << pref[i] << ' ';
  }
  std::cout << std::endl;

  std::cout << "Z function:" << std::endl;
  for (int i = 0; i < pref.size(); i++) {
    std::cout << zf[i] << ' ';
  }
  std::cout << std::endl;

  std::cout << "KMP function:" << std::endl;
  for (int i = 0; i < kmpf.size(); i++) {
    std::cout << kmpf[i] << ' ';
  }

  std::cout << std::endl;

  return 0;
}