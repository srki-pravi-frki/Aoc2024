#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <sstream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

// Recursion baby!


vector<string> split(string s, string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

long concatenate(long a, long b)
{
    return a * pow(10, (int)log10(b) + 1) + b;
}

bool operatorsAndConcat(long result, vector<long> numbers, int index, long current = 0ULL)
{
    if (index == numbers.size())
        return result == current;

    if (current > result || current < 0)
        return false;

    return operatorsAndConcat(result, numbers, index + 1, concatenate(current, numbers[index])) ||
            operatorsAndConcat(result, numbers, index + 1, current + (long)numbers[index]) ||
            operatorsAndConcat(result, numbers, index + 1, current * (long)numbers[index]);
}

bool operators(long result, vector<long> numbers, long index,
               long current = 0ULL) {
  if (index == numbers.size())
    return result == current;

  if (current > result)
    return false;

  return operators(result, numbers, index + 1, current + numbers[index]) ||
         operators(result, numbers, index + 1, current * numbers[index]);
}

long processPartOne(vector<pair<long, vector<long>>> lines) {
  long total = 0;

  for (auto [result, numbers] : lines) {
    if (operators(result, numbers, 0))
      total += result;
  }

  return total;
}

long processPartTwo(vector<pair<long, vector<long>>> lines) {
  long total = 0;

  for (auto [result, numbers] : lines) {
    if (operatorsAndConcat(result, numbers, 0))
      total += result;
  }

  return total;
}

int main() {
  std::ifstream ifile("Day7.txt");

  vector<vector<long>> lines;
  vector<pair<long, vector<long>>> data;

  if (ifile.is_open()) {

    string line;
    while (getline(ifile, line)) {
      vector<string> parts = split(line, " ");
      vector<long> values;
      for (long i = 1; i < parts.size(); i++)
        values.push_back(stoll(parts[i]));
      data.push_back({stoll(parts[0]), values});
    }
  }

  cout << "First part is: " << processPartOne(data) << endl;
  cout << "Second part is: " << processPartTwo(data) << endl;

  return 0;
}