#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "../util/helpers.h"

using namespace std;

typedef pair<ulong, ulong> coord;

void decodeInstruction(string s, bool *axis, int *pos) {
    *axis = (s[0] == 'x');
    *pos  = stoi(s.substr(2));
}

set<coord> fold(bool axis, int at, set<coord> coords) {
    // axis: True = x, false = y
    set<coord> newCoords;
    for (coord c : coords) {
        if (axis) {
            if (c.first > at) {
                ulong dist = c.first - at;
                coord newC = {at-dist, c.second};
                if (newC.first >= 0) {
                    newCoords.insert(newC);
                }
            } else {
                newCoords.insert(c);
            }
        } else {
            if (c.second > at) {
                ulong dist = c.second - at;
                coord newC = {c.first, at-dist};
                if (newC.second >= 0) {
                    newCoords.insert(newC);
                }
            } else {
                newCoords.insert(c);
            }
        }
    }

    return newCoords;
}

string createPattern(vector<string> *instructions, set<coord> coords) {
    // First evaluate every instruction
    for (string s : *instructions) {
        bool axis;
        int  pos;
        decodeInstruction(s, &axis, &pos);
        coords = fold(axis, pos, coords);
    }

    // Now create the field
    // First we need the sizes
    ulong cols = 0, rows = 0;
    for (coord c : coords) {
        if (c.first  > cols) { cols = c.first;  }
        if (c.second > rows) { rows = c.second; }
    }
    // Now create the bool field
    string out = "";
    for (size_t y = 0; y <= rows; y++) {
        for (size_t x = 0; x <= cols; x++) {
            out += ' ';
        }
        out += '\n';
    }
    // Fill in the marked points
    for (coord c : coords) {
        out[c.first + (c.second * (cols+2))] = '#';
    }
    return out;
}

string task2(set<coord> *coords, vector<string> *instructions) {
    return createPattern(instructions, *coords);
}

int task1(set<coord> *coords, string f) {
    // We only want to execute one fold, so we only send one fold. Life is simple :)
    vector<string> fold = {f};
    string field = createPattern(&fold, *coords);

    // Count the non-set points
    int count = 0;
    for (char b : field) {
        if (b == '#') {
            count++;
        }
    }
    return count;
}

int main() {
    set<coord> coords;
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
                coords.insert(c);
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