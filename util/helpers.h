#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

typedef pair<ulong, ulong> coord;

string pretty(coord c) {
    string o = "[" + to_string(c.first) + ", " + to_string(c.second) + "]";
    return o;
}

string pretty(vector<coord> v) {
    string o = "";
    for (int i = 0; i < v.size()-1; i++) {
        o += pretty(v.at(i)) + ", ";
    }
    o += pretty(v.at(v.size()-1));
    return o;
}

template <typename T>
string pretty(vector<T> v) {
    string o = "";
    for (size_t i = 0; i < v.size()-1; i++) {
        o += v.at(i) + ", ";
    }
    o += v.at(v.size()-1);
    return o;
}

