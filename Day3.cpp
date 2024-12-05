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

std::vector<std::string> regex_search(std::regex regular_expression,
                                      std::string line) {
  std::vector<std::string> matches;
  auto regex_begin =
      std::sregex_iterator(line.begin(), line.end(), regular_expression);
  auto regex_end = std::sregex_iterator();

  for (std::sregex_iterator i = regex_begin; i != regex_end; ++i) {
    std::smatch match = *i;
    matches.push_back(match.str());
  }
  return matches;
}

long processPartOne(vector<string> lines) {
  long long total = 0;

  const regex mul_regex("mul\\(\\d{1,3},\\d{1,3}\\)");
  const regex children_regex("mul\\((\\d+),(\\d+)\\)");

  for (auto& line : lines) {

    std::vector<std::string> mul_operators = regex_search(mul_regex, line);

    for (auto &oper : mul_operators) {
      smatch pieces_match;
      if (regex_match(oper, pieces_match, children_regex)) {
        total += stoi(pieces_match[1]) * stoi(pieces_match[2]);
      }
    }
  }

  return total;
}

int processPartTwo(vector<string> lines) {
  int total = 0;

  const regex mul_regex("mul\\((\\d+),(\\d+)\\)|(do\\(\\))|(don't\\(\\))");
  bool enabled = true;
  for (auto& line : lines) {
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), mul_regex);
    auto words_end = std::sregex_iterator();


    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        std::string match_str = match.str();
        std::cout << match_str << '\n';
    
        if (match[3].matched) enabled = true;
        if (match[4].matched) enabled = false;
        if (match[1].matched && match[2].matched && enabled)
        {
          total += stoi(match[1]) * stoi(match[2]);
        }
    }

  }

  return total;
}

int main() {
  std::ifstream ifile("Day3.txt");

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