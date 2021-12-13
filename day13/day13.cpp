#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "../util/helpers.h"

using namespace std;

typedef pair<int, int> coord;

void decodeInstruction(string s, bool *axis, int *pos) {
    *axis = (s[0] == 'x');
    *pos  = stoi(s.substr(2));
}

vector<coord> fold(bool axis, int at, vector<coord> coords) {
    // axis: True = x, false = y
    vector<coord> newCoords;
    for (coord c : coords) {
        if (axis) {
            int dist = abs(at - c.first);
            coord newC = {at-dist, c.second};
            if (newC.first >= 0) {
                newCoords.push_back(newC);
            }
        } else {
            int dist = abs(at - c.second);
            coord newC = {c.first, at-dist};
            if (newC.second >= 0) {
                newCoords.push_back(newC);
            }
        }
    }

    return newCoords;
}

vector<vector<bool>> createPattern(vector<string> instructions, vector<coord> coords) {
    // First evaluate every instruction
    for (string s : instructions) {
        bool axis;
        int  pos;
        decodeInstruction(s, &axis, &pos);
        coords = fold(axis, pos, coords);
    }

    // Now create the field
    // First we need the sizes
    int cols = 0, rows = 0;
    for (coord c : coords) {
        if (c.first  > cols) { cols = c.first;  }
        if (c.second > rows) { rows = c.second; }
    }
    // Now create the bool field
    vector<vector<bool>> out;
    for (size_t y = 0; y <= rows; y++) {
        vector<bool> line;
        for (size_t x = 0; x <= cols; x++) {
            line.push_back(false);
        }
        out.push_back(line);
    }

    // Fill in the marked points
    for (coord c : coords) {
        out.at(c.second).at(c.first) = true;
    }
    return out;
}

string prettyField(vector<vector<bool>> field) {
    string o = "";
    for (vector<bool> bv : field) {
        for (bool b : bv) {
            if (b) { 
                o += '#';
            } else {
                o += '.';
            }
        }
        o += '\n';
    }

    return o;
}

string task2(vector<coord> *coords, vector<string> *instructions) {
    vector<vector<bool>> field = createPattern(*instructions, *coords);
    return prettyField(field);
}

int task1(vector<coord> *coords, string f) {
    // We only want to execute one fold, so we only send one fold. Life is simple :)
    vector<vector<bool>> field = createPattern({ f }, *coords);

    // Count the non-set points
    int count = 0;
    for (vector<bool> bv : field) {
        for (bool b : bv) {
            if (b) { count++; }
        }
    }

    return count;
}

int main() {
    vector<coord> coords;
    vector<string> folds;
    std::ifstream is("input");
    int colums = 0, rows = 0;
    for (string str; getline(is, str);) {
        if (str.length() != 1) {
            if (str[str.length()-1] == '\r') {
                str = str.substr(0, str.length()-1);
            }
            if (str[0] == 'f') {
                folds.push_back(str.substr(11));
            } else {
                coord c;
                c.first = stoi(str.substr(0, str.find_first_of(',')));
                c.second = stoi(str.substr(str.find_first_of(',')+1));
                coords.push_back(c);
                if (c.first > colums) { colums = c.first;  }
                if (c.second > rows ) { rows   = c.second; }
            }
        }
    }

    stringstream msg;
    msg << "Task 1: " << task1(&coords, folds.at(0)) << endl;
    msg << "Task 2: " << endl << task2(&coords, &folds) << endl;
    cout << msg.str();
}