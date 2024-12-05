#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

int CountXmas(const std::vector<std::string> &lines)
{
  int xmasCount = 0;
  auto checkWords = [](const std::vector<std::string> &words)
  {
    return std::count_if(words.begin(), words.end(), [](const std::string &word)
                         { return word == "XMAS" || std::string(word.rbegin(), word.rend()) == "XMAS"; });
  };

  for (size_t row = 0; row < lines.size(); ++row)
  {
    for (size_t column = 0; column < lines[row].size(); ++column)
    {
      std::vector<std::string> words;

      // horizontal
      if (column < lines[row].size() - 3)
        words.push_back(lines[row].substr(column, 4));

      // vertical
      if (row < lines.size() - 3)
        words.push_back({lines[row][column], lines[row + 1][column], lines[row + 2][column], lines[row + 3][column]});

      // diagonally down-right
      if (row < lines.size() - 3 && column < lines[row].size() - 3)
        words.push_back({lines[row][column], lines[row + 1][column + 1], lines[row + 2][column + 2], lines[row + 3][column + 3]});

      // diagonally down-left
      if (row < lines.size() - 3 && column >= 3)
        words.push_back({lines[row][column], lines[row + 1][column - 1], lines[row + 2][column - 2], lines[row + 3][column - 3]});

      xmasCount += checkWords(words);
    }
  }

  return xmasCount;
}

int CountCrossedMas(const std::vector<std::string> &lines)
{
  int xmasCount = 0;

  for (size_t row = 1; row < lines.size() - 1; ++row)
  {
    for (size_t column = 1; column < lines.at(row).size() - 1; ++column)
    {
      std::vector<std::string> words;
      std::string xmas = "MAS";

      words.push_back(std::string{lines.at(row - 1)[column - 1], lines.at(row)[column], lines.at(row + 1)[column + 1]});
      words.push_back(std::string{lines.at(row - 1)[column + 1], lines.at(row)[column], lines.at(row + 1)[column - 1]});

      xmasCount += (words[0] == xmas || std::string(words[0].rbegin(), words[0].rend()) == xmas) &&
                   (words[1] == xmas || std::string(words[1].rbegin(), words[1].rend()) == xmas);
    }
  }

  return xmasCount;
}



long processPartOne(vector<string> lines) {
  long long total = 0;

  total = CountXmas(lines);

  return total;
}

int processPartTwo(vector<string> lines) {
  int total = 0;

  total = CountCrossedMas(lines);

  return total;
}

int main() {
  std::ifstream ifile("Day4.txt");

  vector<string> report_lines;

  if (ifile.is_open()) {

    string str;
    while (getline(ifile, str)) {
      report_lines.push_back(str);
    }

    cout << "First part is: " << processPartOne(report_lines) << endl;
    cout << "Second part is: " << processPartTwo(report_lines) << endl;
  }
}