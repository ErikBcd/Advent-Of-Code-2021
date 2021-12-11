#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void flash(vector<string> *l, int x, int y) {
    int c[3] = {0, 1, -1};

    auto boundCheck = [](int a, int b) {
        return a >= 0 && a < 10 && b >= 0 && b < 10;
    };

    for (int xc : c) {
        for (int yc : c) {
            if (!(xc == 0 && yc == 0)) {
                if (boundCheck(xc+x, yc+y) == 1 && l->at(yc+y)[xc+x] != '#') {
                    l->at(yc+y)[xc+x]++;
                    if (l->at(yc+y)[xc+x] > '9') {
                        l->at(yc+y)[xc+x] = '#';
                        flash(l, xc+x, yc+y);
                    }
                }
            }
        }
    }
}

int simulateFlashes(vector<string> *l) {
    bool active = true;
    while (active) {
        active = false;
        for (size_t x = 0; x < 10; x++) {
            for (size_t y = 0; y < 10; y++) {
                if (l->at(y)[x] > '9') {
                    l->at(y)[x] = '#';
                    flash(l, x, y);
                    active = true;
                }
            }
        }
    }
    int flashes = 0;

    // Count flashes and set # to 0
    for (size_t x = 0; x < 10; x++) {
        for (size_t y = 0; y < 10; y++) {
            if (l->at(y)[x] == '#') {
                l->at(y)[x] = '0';
                flashes++;
            }
        }
    }
    return flashes;
}

void increaseLevels(vector<string> *l) {
    for (size_t x = 0; x < 10; x++) {
        for (size_t y = 0; y < 10; y++) {
            l->at(y)[x]++;
        }
    }
}

int task1() {
    std::ifstream is("input");
    vector<string> levels;
    for (string s; getline(is, s);) {
        levels.push_back(s);
    }

    int flashes = 0;
    for (size_t i = 0; i < 100; i++) {
        // Increase energy level of each octopus
        increaseLevels(&levels);

        // Flashes
        flashes += simulateFlashes(&levels);
    }

    return flashes;
}

int task2() {
    std::ifstream is("input");
    vector<string> levels;
    for (string s; getline(is, s);) {
        levels.push_back(s);
    }

    int stepCount = 1;
    while (true) {
        // Increase energy level of each octopus
        increaseLevels(&levels);

        // Check if all octos flash
        if (simulateFlashes(&levels) == 100) {
            return stepCount;
        }
        stepCount++;
    }

    // Return dummy for warning removal
    return -1;
}

int main() {
    cout << "Task 1: " << task1() << endl;
    cout << "Task 2: " << task2() << endl;
    return 0;
}