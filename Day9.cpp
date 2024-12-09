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

void advanceFree(int& locationFree, vector<int> diskmap)
{
  while (locationFree != diskmap.size())
  {
    if (diskmap[locationFree] == -1) return;
    locationFree++;
  }
}


void advanceFile(int& locationFile, vector<int> diskmap)
{
  while (locationFile != 0)
  {
    if (diskmap[locationFile] != -1) return;
    locationFile--;
  }
}

void advanceBlockFree(int& locationFree, vector<pair<int, int>> diskmap, int curFree)
{
  while (locationFree != diskmap.size())
  {
    if ((diskmap[locationFree].first == -1) && (locationFree != curFree)) return;
    locationFree++;
  }
}


void advanceBlockFile(int& locationFile, vector<pair<int, int>> diskmap, int curFile)
{
  while (locationFile != 0)
  {
    if ((diskmap[locationFile].first < curFile) && (diskmap[locationFile].first != -1)) return;
    locationFile--;
  }
}

long processPartOne(vector<int>& diskmap) {
  long total = 0;

  int locationFree = 0;
  int locationFile = diskmap.size() - 1;

  advanceFree(locationFree, diskmap);
  advanceFile(locationFile, diskmap);

  while (locationFree < locationFile)
  {
    diskmap[locationFree] = diskmap[locationFile];
    diskmap[locationFile] = -1;
    
    advanceFree(locationFree, diskmap);
    advanceFile(locationFile, diskmap);
  }

  int cnt = 0;
  for (int block : diskmap)
  {
    if (block !=-1)
    total += cnt * block;
    cnt++;
  }


  return total;
}



long processPartTwo(vector<pair<int, int>> diskmap) {
  long total = 0;

  int locationFree = 0;
  int locationFile = diskmap.size() - 1;

  advanceBlockFree(locationFree, diskmap, locationFree);

  while (locationFile > 0)
  {
    cout << locationFile << endl;
  int locationFree = 0;
  advanceBlockFree(locationFree, diskmap, locationFree);
  
  bool done = false;

  while ((locationFree < locationFile) && !done)
  {
    if (diskmap[locationFree].second > diskmap[locationFile].second)
    {
      int freeSpace = diskmap[locationFree].second - diskmap[locationFile].second;
      int fileNum = diskmap[locationFile].first;
      // we can fit the entire file and tehre will be extra space
      diskmap[locationFree] = diskmap[locationFile];
      diskmap[locationFile].first = -1;
      diskmap.insert(diskmap.begin() + locationFree + 1, make_pair(-1, freeSpace));
      advanceBlockFile(locationFile, diskmap, fileNum);
      done = true;

    } else if (diskmap[locationFree].second == diskmap[locationFile].second)
    {
      int fileNum = diskmap[locationFile].first;
      // we can fit the entire file
      diskmap[locationFree] = diskmap[locationFile];
      diskmap[locationFile].first = -1;
      advanceBlockFile(locationFile, diskmap, fileNum);
      done = true;
    }
    
    advanceBlockFree(locationFree, diskmap, locationFree);

  }
  if (!done) 
  {
    // didn't find a solution
    int fileNum = diskmap[locationFile].first;
    advanceBlockFile(locationFile, diskmap, fileNum);
  }
  }

  int cnt = 0;

  for (auto p : diskmap)
  {
    for (int i = 0; i < p.second; i++)
    {
      if (p.first != -1)
      {
        total += p.first * cnt;
      }
      cnt++;
    }
  }


  return total;
}

int main() {
  std::ifstream ifile("Day9.txt");

  vector<int> diskMap;
  vector<pair<int, int>> diskMapBlock;

  if (ifile.is_open()) {

    char fl, sl;
    int fileLen;
    int spaceLen;
    int fileNum = 0;

    while (ifile >> fl >> sl)
    {
      fileLen = fl - '0';
      spaceLen = sl - '0';

      if (fileLen > 0)
      diskMapBlock.push_back(std::make_pair(fileNum, fileLen));

      if (spaceLen > 0)
      diskMapBlock.push_back(std::make_pair(-1, spaceLen));

      for (int i = 0; i < fileLen; ++i)
      {
        diskMap.push_back(fileNum);
        
      }

      for (int i = 0; i < spaceLen; ++i)
      {
        diskMap.push_back(-1);
      }      
      fileNum++;
    }
  }

  cout << "First part is: " << processPartOne(diskMap) << endl;
  cout << "Second part is: " << processPartTwo(diskMapBlock) << endl;

  return 0;
}