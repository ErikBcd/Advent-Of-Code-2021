#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool lowestInLocation(vector<vector<char>> *heightmap, int x, int y) {
    char lowest = heightmap->at(y).at(x);

    if (x-1 >= 0 && heightmap->at(y).at(x-1) <= lowest) {
        return false;
    }
    // Explore right side
    if (x+1 < heightmap->at(y).size() && heightmap->at(y).at(x+1) <= lowest) {
        return false;
    }
    // Explore bottom side
    if (y+1 < heightmap->size() && heightmap->at(y+1).at(x) <= lowest) {
        return false;
    }
    // Explore upper side
    if (y-1 >= 0 && heightmap->at(y-1).at(x) <= lowest) {
        return false;
    }

    return true;
}

/** 
 * @param indices The lowest points will be saved here
 * @return int 
 */
int task1(vector<vector<char>> *heightmap, vector<pair<int, int>> *indices) {
    // Check lowpoints
    int sumRiskLevels = 0;
    for (int x = 0; x < heightmap[0].size(); x++) {
        for (int y = 0; y < heightmap->size(); y++) {
            if (lowestInLocation(heightmap, x, y)) {
                sumRiskLevels += heightmap->at(y).at(x) + 1 - '0';
                indices->push_back(pair<int, int>(x,y));
            }
        }
    }

    return sumRiskLevels;
}

int findBasinFields(vector<vector<char>> *heightmap, int x, int y) {
    heightmap->at(y).at(x) = '9';
    int found = 1;

    if (x-1 >= 0 && heightmap->at(y).at(x-1) != '9') {
        found += findBasinFields(heightmap, x-1, y);
    }
    // Explore right side
    if (x+1 < heightmap->at(y).size() && heightmap->at(y).at(x+1) != '9') {
        found += findBasinFields(heightmap, x+1, y);
    }
    // Explore bottom side
    if (y+1 < heightmap->size() && heightmap->at(y+1).at(x) != '9') {
        found += findBasinFields(heightmap, x, y+1);
    }
    // Explore upper side
    if (y-1 >= 0 && heightmap->at(y-1).at(x) != '9') {
        found += findBasinFields(heightmap, x, y-1);
    }

    return found;
}

/**
 * @param indices The lowest points of task 1
 * @return int 
 */
int task2(vector<vector<char>> *heightmap, vector<pair<int, int>> indices) {
    int topBasins[3] = {0, 0, 0};
    for (pair<int, int> i : indices) {
        int size = findBasinFields(heightmap, i.first, i.second);
        if (size > topBasins[0]) {
            topBasins[2] = topBasins[1];
            topBasins[1] = topBasins[0];
            topBasins[0] = size;
        } else if (size > topBasins[1]) {
            topBasins[2] = topBasins[1];
            topBasins[1] = size;
        } else if (size > topBasins[2]) {
            topBasins[2] = size;
        }
    }
    return (topBasins[0] * topBasins[1] * topBasins[2]);
}

int main() {
    std::ifstream is("input");
    vector<vector<char>> heightmap;
    for (string str; getline(is, str);) {
        vector<char> row;
        for (char c : str) {
            if (c >= '0') {
                row.push_back(c);
            }
        }

        heightmap.push_back(row);
    }

    vector<pair<int, int>> i;
    
    cout << "Task 1: " << task1(&heightmap, &i) << endl;
    cout << "Task 2: " << task2(&heightmap, i) << endl;
}