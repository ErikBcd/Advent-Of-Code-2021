#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "../util/helpers.h"

using namespace std;

// Why parse the parameters when you can ~~~~*define*~~~~ it? :))
#define BEGIN_X 94
#define END_X   151
#define BEGIN_Y -156
#define END_Y   -103

typedef pair<int, int> vec2d;
typedef pair<vec2d, vec2d> probe;

string to_string(probe *p) {
    string o = "{P = [" + to_string(p->first.first) + ", " + to_string(p->first.second);
    o += "], V = [" + to_string(p->second.first) + ", " + to_string(p->second.second) + "]}";
    return o;
}

void progress(probe *p) {
    p->first.first  += p->second.first;
    p->first.second += p->second.second;

    p->second.first += (p->second.first > 0) ? -1 
                                             : (p->second.first != 0) ? 1 
                                                                      : 0;
    p->second.second--;
}

bool hitTarget(probe *p) {
    return (p->first.first >= BEGIN_X && p->first.first <= END_X)
                && (p->first.second >= BEGIN_Y && p->first.second <= END_Y);
}
bool canHit(probe *p) {
    if (abs(p->first.first) > abs(END_X)) { return false; }
    if (abs(p->first.first) < abs(BEGIN_X) && p->second.first == 0) {
        return false;
    }
    if (p->first.second < BEGIN_Y && p->second.second <= 0) { return false; }

    return true;
}

bool willHitTarget(probe *p, long *max_height) {
    //cout << to_string(p) << endl;
    if (hitTarget(p)) { return true; }
    // Check if target is out of range
    if (!canHit(p)) { return false; }
    // Advance probe
    progress(p);
    if (p->first.second > *max_height) {
        *max_height = p->first.second;
    }
    return willHitTarget(p, max_height);
}

int minVelocityX() {
    int v = ceil(0.5 * (-1 + sqrt(1+(8 * abs(BEGIN_X)))));
    return (BEGIN_X >= 0) ? v : -v;
}

int minVelocityY() {
    int v = max(abs(BEGIN_Y), abs(END_Y));
    return (BEGIN_Y >= 0) ? v : -v;
}

pair<long, long> findMaxY() {
    int minX = minVelocityX();
    int minY = minVelocityY();
    long maxY = LONG_MIN;
    coord maxCord;
    long hits = 0;
    // Bruteforce lets goooo
    // For every possible x velocity, 
    // test every possible y velocity
    for (int x = minX; x <= max(abs(END_X), abs(BEGIN_X)); x++) {
        for (int y = minY; y <= max(abs(END_Y), abs(BEGIN_Y)); y++) {
            long maxYTEMP = LONG_MIN;
            probe p{{0,0}, {x,y}};
            if (willHitTarget(&p, &maxYTEMP)) {
                hits++;
                if (maxYTEMP > maxY) {
                    maxY = maxYTEMP;
                    maxCord = p.first;
                }
            }
        }
    }

    return {maxY, hits};
}

int main() {
    pair<long, long> task1 = findMaxY();
    cout << "Max height: " << task1.first << " Hits: " << task1.second << endl;
    return 0;
}