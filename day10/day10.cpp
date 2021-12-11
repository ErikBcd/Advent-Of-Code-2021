#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

map<char, char> OPEN_CLOSE  = {make_pair<char, char>('{', '}'), 
                               make_pair<char, char>('[', ']'), 
                               make_pair<char, char>('(', ')'), 
                               make_pair<char, char>('<', '>')};
map<char, int> ERROR_SCORE  = {make_pair<char, int>('}', 1197), 
                               make_pair<char, int>(']', 57), 
                               make_pair<char, int>(')', 3), 
                               make_pair<char, int>('>', 25137)};
map<char, int> AUTOC_SCORE  = {make_pair<char, int>('}', 3), 
                               make_pair<char, int>(']', 2), 
                               make_pair<char, int>(')', 1), 
                               make_pair<char, int>('>', 4)};

bool startOfChunk(char c) {
    return (c == '(' || c == '{' || c == '[' || c == '<');
}

int findCorrLines(string line) {
    string missingChars;
    for (char c : line) {
        if (startOfChunk(c)) {
            missingChars = OPEN_CLOSE[c] + missingChars;
        } else if (c >= 40) {
            if (missingChars[0] != c) {
                return ERROR_SCORE[c];
            }
            missingChars = missingChars.substr(1);
        }
    }
    return 0;
}

ulong autocompleteScore(string missing) {
    ulong score = 0;
    for (char c : missing) {
        score *= 5;
        score += AUTOC_SCORE[c];
    }

    return score;
}

ulong correctLine(string l) {
    string missingChars;
    for (char c : l) {
        if (startOfChunk(c)) {
            missingChars = OPEN_CLOSE[c] + missingChars;
        } else if (c >= 40) {
            missingChars = missingChars.substr(1);
        }
    }
    return autocompleteScore(missingChars);
}


int task1(vector<string> *s) {
    int err = 0;
    for (size_t i = 0; i < s->size(); i++) {
        int error = findCorrLines(s->at(i));
        if (error > 0) {
            err += error;
            s->erase(s->begin() + i);
            i--;
        }
    }
    return err;
}

ulong task2(vector<string> *lines) {
    vector<ulong> scores;
    for (string s : *lines) {
        scores.push_back(correctLine(s));
    }
    // Sort scores 
    sort(scores.begin(), scores.end());
    return scores.at(scores.size() / 2);
}

int main() {
    std::ifstream is("input");
    vector<string> lines;
    for (string s; getline(is, s);) {
        lines.push_back(s);
    }

    cout << "Task 1: " << task1(&lines) << endl;
    cout << "Task 2: " << task2(&lines) << endl;
}