#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void appendRightDigits(string line, int j, string &n) {
  while (j < line.size() && isdigit(line[j])) {
    n = n + line[j];
    j++;
  }
}

void appendLeftDigits(string line, int j, string &n) {
  while (j >= 0 && isdigit(line[j])) {
    n = line[j] + n;
    j--;
  }
}

void findNumbersLeft(const vector<string> &lines, int row, int col,
                     vector<int> &numbers, vector<int> &ratioNumbers) {
  string line = lines[row];
  string n;
  if (isdigit(line[col - 1])) {
    appendLeftDigits(line, col - 1, n);
    numbers.push_back(stoi(n));
    ratioNumbers.push_back(stoi(n));
  }
}

void findNumbersRight(const vector<string> &lines, int row, int col,
                      vector<int> &numbers, vector<int> &ratioNumbers) {

  string line = lines[row];
  string n;

  if (isdigit(line[col + 1])) {
    appendRightDigits(line, col + 1, n);
    numbers.push_back(stoi(n));
    ratioNumbers.push_back(stoi(n));
  }
}

void findNumbersBelow(const vector<string> &lines, int row, int col,
                      vector<int> &numbers, vector<int> &ratioNumbers) {
  if (row == lines.size() - 1) {
    return;
  }
  string line = lines[row + 1];
  string n;
  if (isdigit(line[col])) {
    n = line.substr(col, 1);
    appendLeftDigits(line, col - 1, n);
    appendRightDigits(line, col + 1, n);
    numbers.push_back(stoi(n));
    ratioNumbers.push_back(stoi(n));
  } else {
    if (col > 0 && isdigit(line[col - 1])) {
      n = "";
      appendLeftDigits(line, col - 1, n);
      numbers.push_back(stoi(n));
      ratioNumbers.push_back(stoi(n));
    }
    if (col < line.size() - 1 && isdigit(line[col + 1])) {
      n = "";
      appendRightDigits(line, col + 1, n);
      numbers.push_back(stoi(n));
      ratioNumbers.push_back(stoi(n));
    }
  }
}

void findNumbersAbove(const vector<string> &lines, int row, int col,
                      vector<int> &numbers, vector<int> &ratioNumbers) {
  if (row == 0) {
    return;
  }
  string line = lines[row - 1];
  string n = line.substr(col, 1);
  if (isdigit(n[0])) {
    appendLeftDigits(line, col - 1, n);
    appendRightDigits(line, col + 1, n);
    numbers.push_back(stoi(n));
    ratioNumbers.push_back(stoi(n));
  } else {
    if (col > 0 && isdigit(line[col - 1])) {
      n = "";
      appendLeftDigits(line, col - 1, n);
      numbers.push_back(stoi(n));
      ratioNumbers.push_back(stoi(n));
    }
    if (col < line.size() - 1 && isdigit(line[col + 1])) {
      n = "";
      appendRightDigits(line, col + 1, n);
      numbers.push_back(stoi(n));
      ratioNumbers.push_back(stoi(n));
    }
  }
}

vector<int> findAdjacentNumbers(vector<string> &lines, int row, int &ratio) {
  string line = lines[row];
  vector<int> numbers;
  for (int j = 0; j < line.size(); j++) {
    vector<int> ratioNumbers;
    if (line[j] != '.' && !isdigit(line[j])) {
      findNumbersAbove(lines, row, j, numbers, ratioNumbers);
      findNumbersBelow(lines, row, j, numbers, ratioNumbers);
      findNumbersLeft(lines, row, j, numbers, ratioNumbers);
      findNumbersRight(lines, row, j, numbers, ratioNumbers);
      if (ratioNumbers.size() == 2 && line[j] == '*') {
        ratio = ratio + ratioNumbers[0] * ratioNumbers[1];
      }
    }
  }
  return numbers;
}

int main() {
  fstream data("input.txt");
  vector<string> lines;
  int total = 0, ratio = 0;

  if (data.is_open()) {
    string line;
    while (getline(data, line)) {
      lines.push_back(line);
    }
    data.close();
  } else {
    cout << "Unable to open file" << endl;
  }

  for (int i = 0; i < lines.size(); i++) {
    vector<int> numbers;
    numbers = findAdjacentNumbers(lines, i, ratio);
    for (int n : numbers) {
      total += n;
    }
  }
  cout << "total: " << total << endl;
  cout << "ratio: " << ratio << endl;
  return 0;
}
