#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int processPartOne(vector<int> first, vector<int> second)
{
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    int total = 0;

    for (int i = 0; i < first.size(); ++i)
    {
        total += abs((second[i]-first[i]));

    }

return total;
}

int processPartTwo(vector<int> first, vector<int> second)
{
    map<int, int> secondMap;

    for (auto num : second)
    {
        secondMap[num]++;
    }

    int total = 0;

    for (auto num: first)
    {
        total += (num * secondMap[num]);
    }

return total;
}

int main()
{
	std::ifstream ifile("Day1.txt");

    int first, second;
    vector<int> firstvec, secondVec;

	if (ifile.is_open())
	{
		while (ifile >> first >> second)
		{
		  firstvec.push_back(first);
          secondVec.push_back(second);
		}
	}

    cout << "First part is: " << processPartOne(firstvec, secondVec) << endl;
    cout << "Second part is: " << processPartTwo(firstvec, secondVec) << endl;
}