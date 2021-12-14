#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <thread>
#include "../util/helpers.h"

using namespace std;

map<string, pair<string, string>> rules;

ulong proc(int steps, map<string, ulong> ruleCounts, map<char, ulong> counts) {
    // Create a map with the keys from ruleCounts, but without the values
    map<string, ulong> ruleCountsEmpty;
    for (pair<string, pair<string, string>> r : rules) {
        ruleCountsEmpty.insert(make_pair(r.first, 0));
    }

    for (size_t i = 0; i < steps; i++) {
        map<string, ulong> ruleCountTemp = ruleCountsEmpty;

        // Get the rules that would be applied to the polymer.
        // Every applied rule creates two new rules in the next step.
        // Also every applied rule creates a new polymer which will be added
        // the the polymer count.
        for (pair<string, ulong> r : ruleCounts) {
            if (r.second > 0 && rules.find(r.first) != rules.end()) {
                pair<string, string> rule   = rules[r.first];
                // Save the rules for the next process step
                ruleCountTemp[rule.first]  += r.second;
                ruleCountTemp[rule.second] += r.second;
                counts[rule.second[0]] += r.second;
            }
        }
        ruleCounts = ruleCountTemp;
    }
    

    ulong max = 0;
    ulong min = ULONG_MAX;
    for (pair<char, ulong> c : counts) {
        if (c.second > max) { max = c.second; }
        if (c.second < min) { min = c.second; }
    }
    return max - min;
}

ulong task1(map<string, ulong> ruleCounts, map<char, ulong> counts) {
    return proc(10, ruleCounts, counts);
}

ulong task2(map<string, ulong> ruleCounts, map<char, ulong> counts) {
    return proc(40, ruleCounts, counts);
}

int main() {
    std::ifstream is("input");

    string s;
    getline(is, s);
    string poly = s.substr(0, s.size() -1);

    map<char, ulong> counts;
    map<string, ulong> ruleCounts;
    
    getline(is, s);
    for (;getline(is, s);) {
        if (s[s.length()-1] == '\r') { s = s.substr(0, s.length()-1); }
        string rule = s.substr(0,2);
        char c = s[s.length()-1];

        rules.insert_or_assign(rule, 
                               make_pair(string{rule[0], c}, 
                                         string{c, rule[1]}));
        counts.insert_or_assign(c, 0);
        ruleCounts.insert_or_assign(rule, 0);
    }

    for (size_t i = 1; i < poly.length(); i++) {
        string r{poly[i-1], poly[i]};
        ruleCounts[r]++;
        counts[poly[i]]++;
    }
    counts[poly[0]]++;

    cout << "Task 1: " << task1(ruleCounts, counts) << endl;
    cout << "Task 2: " << task2(ruleCounts, counts) << endl;
    return 1;
}