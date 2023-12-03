#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;

regex pattern("one|two|three|four|five|six|seven|eight|nine");

map<string, int> stringToDigit = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

int findDigitInString(string s) {
  smatch match;
  regex_search(s, match, pattern);
  if (match.size() > 0) {
    return stringToDigit[match[0]];
  }
  return 0;
}

int main() {
  int total = 0;
  freopen("input.txt", "r", stdin);

  string line;

  while (getline(cin, line)) {
    int firstDigit = 0, lastDigit = 0;
    string substr;
    for (char c : line) {
      substr += c;
      int digit = isdigit(c) ? c - '0' : findDigitInString(substr);

      if (digit) {
        if (firstDigit == 0) {
          firstDigit = digit;
        } else {
          lastDigit = digit;
        }
        substr = isdigit(c) ? "" : substr.substr(substr.size() - 1);
      }
    }

    if (firstDigit && !lastDigit) {
      total += firstDigit * 10 + firstDigit;
    } else if (firstDigit && lastDigit) {
      total += firstDigit * 10 + lastDigit;
    }
  }
  cout << total << endl;
  return 0;
}
