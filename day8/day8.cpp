#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <bitset>

using namespace std;

vector<string> getPatterns(string str) {
    std::stringstream s(str);
    std::string x;
    vector<string> o;
    while(s.good()) {
        std::getline(s, x, ' ');
        if (x=="|") {
            return o;
        }
        o.push_back(x);
    }

    return o;
}

vector<string> getOutput(string str) {
    vector<string> o;
    o.push_back("");
    for (size_t i = 1; i < str.length(); i++) {
        if (str[i] == ' ') {
            o.push_back("");
        } else if (str[i] > 96 && str[i] < 104){
            o.back().push_back(str[i]);
        }
    }

    return o;
}


/**
 * @brief This is hell. Might rework this. 
 */
string decode(vector<string> pattern, vector<string> output) {
    // Find the known patterns
    string correlations[10] = {"", "", "", "", "", "", "", "", "", ""};
    for (string s : pattern) {
        if (s.length() == 2) {
            correlations[1] = s;
        } else if (s.length() == 4) {
            correlations[4] = s;
        } else if (s.length() == 3) {
            correlations[7] = s;
        } else if (s.length() == 7) {
            correlations[8] = s;
        }
    }
    /*
        The bars are the letters a-g, 
        or in my form the numbers 0-6:
         000
        1   2
        1   2
         333
        4   5
        4   5
         666
    */
    char bars[7];

    // Find bars 4, 5, 1
    // They come up exactly 4, 9, 6 times in the pattern
    int count[7] = {0, 0, 0, 0, 0, 0, 0};
    for (string s : pattern) {
        for (size_t i = 0; i < s.length(); i++) {
            count[s[i]-97]++;
        }
    }
    for (size_t i = 0; i < 7; i++) {
        if (count[i] == 4) {
            bars[4] = 'a'+i;
        } else if (count[i] == 9) {
            bars[5] = 'a'+i;
        } else if (count[i] == 6) {
            bars[1] = 'a'+i;
        }
    }

    // With bar 5 we can find bar 2 thanks to corr. 1
    bars[2] = (correlations[1][0] == bars[5]) ? correlations[1][1] : correlations[1][0];

    // Since bar 0 and 2 have the same count, we can find bar 0 now:
    for (size_t i = 0; i < 7; i++) {
        if (count[i] == 8 && ('a'+i) != bars[2]) {
            bars[0] = 'a'+i;
        }
    }

    // Find bar 6 and 3
    // Bar 3 is in the display of digit 4 on, 6 isn't
    for (char c : correlations[4]) {
        bool found = true;
        for (size_t i = 0; i < 7; i++) {
            if (bars[i] == c) {
                found = false;
                break;
            }
        }
        if (found) {
            bars[3] = c;
            break;
        }
    }

    // Now missing: Bar 6
    // 6 occures exactly 7 times
    for (size_t i = 0; i < 7; i++) {
        if (count[i] == 7 && ('a'+i) != bars[3]) {
            bars[6] = ('a'+i);
            break;
        }
    }

    // We found all bars, now decode the message
    // Create a bitset for each letter
    bitset<7> digits[10] = {bitset<7>("1110111"),
                            bitset<7>("0010010"),
                            bitset<7>("1011101"),
                            bitset<7>("1011011"),
                            bitset<7>("0111010"),
                            bitset<7>("1101011"),
                            bitset<7>("1101111"),
                            bitset<7>("1010010"),
                            bitset<7>("1111111"),
                            bitset<7>("1111011") };

    // First, create a bitset for each output
    // Then check which digit equals former bitset
    string out = "";
    for (string s : output) {
        bitset<7> d(0);
        for (char c : s) {
            for (size_t i = 0; i < 7; i++) {
                if (bars[i] == c) {
                    d.flip(6-i);
                    break;
                }
            }
        }

        for (size_t i = 0; i < 10; i++) {
            if ((digits[i] ^ d) == 0) {
                out += to_string(i);
                break;
            }
        }
    }


    return out;
}

int task1() {
    ifstream is("input");
    int digitsFound = 0;
    for (string str; getline(is, str);) {
        size_t x = str.find_first_of('|');
        x++;
        string t = str.substr(x);
        vector<string> vo = getOutput(t);
        for (string s : vo) {
            if (s.length() == 2 || s.length() == 4 || s.length() == 3 || s.length() == 7) {
                digitsFound++;
            }
        }
    }
    cout << "Digits: " << digitsFound << endl;
    return digitsFound;
}

int task2() {
    ifstream is("input");
    vector<vector<string>> sigPat;
    vector<vector<string>> output;
    for (string str; getline(is, str);) {
        // Create signal Patterns
        sigPat.push_back(getPatterns(str));
        // Create outputs
        size_t x = str.find_first_of('|');
        x++;
        string t = str.substr(x);
        output.push_back(getOutput(t));
    }

    int out = 0;
    for (size_t i = 0; i < sigPat.size(); i++) {
        out += stoi(decode(sigPat[i], output[i]));
    }
    
    return out;
}
int main() {
    task1();
    cout << "Task2: " << task2() << endl;
    return 0;
}