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

void parse_vector(string ln, vector<int>& out_vector)
{
	out_vector.clear();
	size_t comma = ln.find(',');
	while (comma != string::npos)
	{
		int next = stoi(ln.substr(0, comma));
		out_vector.push_back(next);
		ln = ln.substr(comma + 1);
		comma = ln.find(',');
	}

	out_vector.push_back(stoi(ln));
}

// returns the number of swaps made.
int bubble(map<int, vector<int>>& rules, vector<int>& v)
{
	int n = v.size();
	int swaps = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int k = 0; k < n - i - 1; k++)
		{
			int b = v[k + 1];
			const vector<int>& r = rules[b];
			if (find(r.begin(), r.end(), v[k]) != r.end())
			{
				int temp = v[k];
				v[k] = v[k + 1];
				v[k + 1] = temp;

				swaps++;
			}
		}
	}

	return swaps;
}

int main()
{
	std::ifstream f("Day5.txt");
	string ln;
	
	// key = first, array of seconds
	map<int, vector<int>> rules;
	while (getline(f, ln))
	{
		if (ln == "")
		{
			break;
		}

		int a = stoi(ln.substr(0, 2));
		int b = stoi(ln.substr(3, 2));
		rules[a].push_back(b);
	}

	long tot = 0;
	while (getline(f, ln))
	{
		vector<int> line;
		parse_vector(ln, line);

		bool good = true;
		for (int i = 0; i < line.size() - 1; i++)
		{
			int a = line[i];
			int b = line[i + 1];

			const vector<int>& v = rules[b];
			if (find(v.begin(), v.end(), a) != v.end())
			{
				good = false;
				break;
			}
		}

		if (!good)
		{
			int numswaps = 0;
			do 
			{
				numswaps = bubble(rules, line);
			} while (numswaps > 0);
			
			
			tot += line[line.size() / 2];
		}
	}

	cout << "P2: " << tot << endl;
}