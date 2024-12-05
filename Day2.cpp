#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <iterator>
#include <ranges>

using namespace std;

template <typename T>
bool isSafe(T&& report)
{
    if(!std::ranges::is_sorted(report, std::greater{}) && !std::ranges::is_sorted(report, std::less{})) {
        return false;
    }

    for (const auto [n1, n2] : std::views::pairwise(report)) {
        const auto delta = std::abs(n1-n2);
        if(delta < 1 || delta > 3) {
            return false;
        }
    }
    return true;    
}

bool isSafeWithProblemDampener (const std::vector<int>& report) {
    if (isSafe(report)) {
        return true;
    }

    for (int i = 0; i < report.size(); i++) {

        // Remove one element in succession and check if the report is now Safe. Probably not an optimal solution
        auto damped_report = std::views::enumerate(report) 
                              | std::views::filter([i](const auto paired){return std::get<0>(paired) != i;});
                              | std::views::transform([](const auto paired) {return std::get<1>(paired);});


        if(isSafe(damped_report)) {
            return true;
        }
    }
    return false;
}

int processPartOne(vector<string> report_lines) {
  int total = 0;

    for (const auto oneline : report_lines)
    {
        istringstream iss(oneline);
        vector<int> report;

        copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter(report));

        if (isSafe(report)) total++;

    }

  return total;
}

int processPartTwo(vector<string> report_lines) {
  int total = 0;

    for (const auto oneline : report_lines)
    {
        istringstream iss(oneline);
        vector<int> report;

        copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter(report));

        if (isSafeWithProblemDampener(report)) total++;
    }

  return total;
}

int main() {
  std::ifstream ifile("Day2.txt");

  vector<string> report_lines;

  if (ifile.is_open()) {

    string str;
    while (getline(ifile, str)) {
      report_lines.push_back(str);
    }
  }

  cout << "First part is: " << processPartOne(report_lines) << endl;
  cout << "Second part is: " << processPartTwo(report_lines) << endl;
}