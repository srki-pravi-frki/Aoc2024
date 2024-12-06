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

bool isGuard(char &c) { return (c == '<' || c == '>' || c == '^' || c == 'v'); }

struct coord {
  int x;
  int y;
};

struct guard {
  coord location;
  char direction;
};

bool isOut(coord guard) {}

int main() {
  std::ifstream f("Day6.txt");
  string ln;
  int total = 0;

  coord loc = {0, 0};
  guard g;

  vector<vector<char>> levelMap = {};

  // key = first, array of seconds
  map<int, vector<char>> rules;
  while (getline(f, ln)) {
    vector<char> line;
    for (char &c : ln) {
      line.push_back(c);
      if (isGuard(c)) {
        g.location = loc;
        g.direction = c;
      }

      loc.x++;
    }
    levelMap.push_back(line);
    loc.x = 0;
    loc.y++;
  }

  cout << "Guard is at: " << g.location.x << " " << g.location.y << endl;

  bool isDone = false;

  while (!isDone) {
    switch (g.direction) {
    case '^':
      if ((g.location.y - 1) < 0) {
        if (levelMap[g.location.y][g.location.x] != 'X') {
          total++;
          levelMap[g.location.y][g.location.x] = 'X';
        }

        isDone = true;
      } else {
        if (levelMap[g.location.y - 1][g.location.x] == '#') {
          g.direction = '>';
        } else {
          if (levelMap[g.location.y][g.location.x] != 'X') {
            total++;
            levelMap[g.location.y][g.location.x] = 'X';
          }

          g.location.y--;
        }
      }

      break;
    case '<':
      if ((g.location.x - 1) < 0) {
        if (levelMap[g.location.y][g.location.x] != 'X') {
          total++;
          levelMap[g.location.y][g.location.x] = 'X';
        }

        isDone = true;
      } else {
        if (levelMap[g.location.y][g.location.x - 1] == '#') {
          g.direction = '^';
        } else {
          if (levelMap[g.location.y][g.location.x] != 'X') {
            total++;
            levelMap[g.location.y][g.location.x] = 'X';
          }

          g.location.x--;
        }
      }

      break;
    case '>':
      if ((g.location.x + 1) == levelMap[0].size()) {
        if (levelMap[g.location.y][g.location.x] != 'X') {
          total++;
          levelMap[g.location.y][g.location.x] = 'X';
        }

        isDone = true;
      } else {
        if (levelMap[g.location.y][g.location.x + 1] == '#') {
          g.direction = 'v';
        } else {
          if (levelMap[g.location.y][g.location.x] != 'X') {
            total++;
            levelMap[g.location.y][g.location.x] = 'X';
          }

          g.location.x++;
        }
      }
      break;
    case 'v':
      if ((g.location.y + 1) == levelMap.size()) {
        if (levelMap[g.location.y][g.location.x] != 'X') {
          total++;
          levelMap[g.location.y][g.location.x] = 'X';
        }

        isDone = true;
      } else {
        if (levelMap[g.location.y + 1][g.location.x] == '#') {
          g.direction = '<';
        } else {
          if (levelMap[g.location.y][g.location.x] != 'X') {
            total++;
            levelMap[g.location.y][g.location.x] = 'X';
          }

          g.location.y++;
        }
      }
      break;
    }
  }

  cout << "Total: " << total << endl;
}