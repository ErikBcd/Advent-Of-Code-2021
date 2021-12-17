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

string pretty(pair<int, char> p) {
    string o = "[" + to_string(p.first) + ", " + p.second + "]";
    return o;
}

string pretty(pair<char, int> p) {
    string o = "[" + p.first;
    o += ", " + to_string(p.second) + "]";
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

string pretty(map<string, char> m) {
    string o = "";
    for (pair<string, char> p : m) {
        o += "[" + p.first + "->" + p.second + "], ";
    }

    return o.substr(0, o.length() -2);
}

template <typename T1, typename T2> 
string pretty(map<T1, T2> m) {
    string o = "";
    for (pair<T1, T2> p : m) {
        o += pretty(p) + ", ";
    }

    return o.substr(0, o.length() -2);
}

template <typename T1, typename T2> 
string pretty(vector<pair<T1, T2>> v) {
    string o = "";
    for (size_t i = 0; i < v.size()-1; i++) {
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

string hexadecimal_to_binary(char c) {
    switch (c) {
    case '0':
         return "0000";
      case '1':
         return "0001";
      case '2':
         return "0010";
      case '3':
         return "0011";
      case '4':
         return "0100";
      case '5':
         return "0101";
      case '6':
         return "0110";
      case '7':
         return "0111";
      case '8':
         return "1000";
      case '9':
         return "1001";
      case 'A':
      case 'a':
         return "1010";
      case 'B':
      case 'b':
         return "1011";
      case 'C':
      case 'c':
         return "1100";
      case 'D':
      case 'd':
         return "1101";
      case 'E':
      case 'e':
         return "1110";
      case 'F':
      case 'f':
         return "1111";
      default:
         cout << "Please enter valid hexadecimal digit "<< c;
         return "";
    }
}

string hexadecimal_to_binary(string s) {
    string o = "";
    for (char c : s) {
        o += hexadecimal_to_binary(c);
    }
    return o;
}

