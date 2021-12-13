#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

string pretty(vector<string> i, string sep) {
    string out = "";
    for (size_t x = 0; x < i.size()-1; x++) {
        out += i[x] + sep;
    }
    out += i[i.size()-1];
    return out;
}

string pretty(map<string, vector<string>> i, string sep) {
    string out = "";
    for (pair<string, vector<string>> p : i) {
        out += p.first + ": " + pretty(p.second, ", ") + sep;
    }
    return out;
}

void pathfinder(map<string, vector<string>> *connections, vector<vector<string>> *foundPaths, vector<string> currentPath, int smallCaves) {    
    if (connections->find(currentPath.back()) == connections->end()) {
        return;
    }
    vector<string> destinations = connections->at(currentPath.back());

    for (string d : destinations) {
        int scTemp = smallCaves;
        if (d == "end") {
            vector<string> t = currentPath;
            t.push_back(d);
            foundPaths->push_back(t);
        } else {
            bool validDest = true;
            if (d == "start") {
                validDest = false;
            // Check if destination is small cave
            } else if (d[0] > 96) {
                // Check if cave was already visited
                for (string s : currentPath) {
                    if (d == s) {
                        validDest = false;
                        break;
                    }
                }
                // Check if it's still fine to visit the same small cave more than once
                if (!validDest && scTemp > 0) {
                    scTemp--;
                    validDest = true;
                }
            } 

            if (validDest) {
                vector<string> t = currentPath;
                t.push_back(d);
                pathfinder(connections, foundPaths, t, scTemp);
            }
        }
    }
}

void pathfinder(map<string, vector<string>> *connections, vector<vector<string>> *foundPaths, int smallCaveNumber) {
    vector<string> startDests = connections->at("start");
    for (string d : startDests) {
        vector<string> p = {"start", d};
        pathfinder(connections, foundPaths, p, smallCaveNumber);
    }
}

int task1(map<string, vector<string>> *in) {
    vector<vector<string>> paths;
    pathfinder(in, &paths, 0);
    return paths.size();
}

int task2(map<string, vector<string>> *in) {
    vector<vector<string>> paths;
    pathfinder(in, &paths, 1);
    return paths.size();
}

int main() {
    // Read the input
    std::ifstream is("input");
    map<string, vector<string>> in;
    for (string str; getline(is, str);) {
        if (str.back() == '\r') {
            str = str.substr(0, str.length() -1);
        }

        size_t x = str.find_first_of('-');
        string start = str.substr(0, x);
        string end = str.substr(x+1);
        if (in.find(start) == in.end()) {
            vector<string> t;
            t.push_back(end);
            in[start] = t;
        } else {
            in[start].push_back(end);
        }

        if (in.find(end) == in.end()) {
            vector<string> t;
            t.push_back(start);
            in[end] = t;
        } else {
            in[end].push_back(start);
        }
    }

    cout << "Task 1: " << task1(&in) << endl;
    cout << "Task 2: " << task2(&in) << endl;

    return 0;
}