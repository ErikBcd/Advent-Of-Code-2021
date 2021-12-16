#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

typedef pair<size_t, size_t> coord;
typedef vector<vector<int>> int_mat;

struct Position {
    coord i;
    int val;
    vector<coord> former;
};

int MAX_X, MAX_Y;
int_mat MAP;

bool operator<(const Position& a, const Position& b) {
    return a.val < b.val;
}
bool operator>(const Position& a, const Position& b) {
    return a.val > b.val;
}
bool operator==(const Position& a, const Position& b) {
    return a.i == b.i;
}

int getRisklevel(coord i, bool task2) {
    if (i.first < MAX_X && i.second < MAX_Y) { return MAP.at(i.second).at(i.first); }

    if (!task2 || i.first >= 5*MAX_X || i.second >= 5*MAX_Y) { return -1; }

    size_t tile = (i.first / MAX_X) + (i.second / MAX_Y);
    int level = MAP.at(i.second % MAX_Y).at(i.first % MAX_X);
    level = (level + tile <= 9) ? level + tile : level + tile -9;

    return level;
}

vector<Position> getNeighbors(Position p, bool task2) {
    vector<Position> out;
    for (int yc = -1; yc < 2; yc++) {
        for (int xc = -1; xc < 2; xc++) {
            if (abs(xc) != abs(yc)) {
                int x = p.i.first + xc, y = p.i.second + yc;
                int rl = getRisklevel({x,y}, task2);
                if (rl >= 1) {
                    Position b{
                        {x,y},
                        rl + p.val,
                        p.former
                    };
                    b.former.push_back(p.i);
                    out.push_back(b);
                }
            }
        }
    }
    return out;
}

typedef priority_queue<Position, vector<Position>, greater<Position>> pos_queue;

Position dijkstra(coord dest, bool task2) {
    pos_queue q;
    q.push({{0, 0}, 0});
    set<coord> closed;

    while (!q.empty()) {
        Position p = q.top();
        q.pop();
        if (p.i == dest) {
            return p;
        }
        // If this position was already checked out, ignore it
        if (closed.find(p.i) != closed.end()) {
            continue;
        }
        closed.insert(p.i);

        vector<Position> neighbors = getNeighbors(p, task2);
        for (Position pp : neighbors) {
            if (closed.find(pp.i) == closed.end()) {
                q.push(pp);
            }
        }
    }

    return {{0,0},0};
}

int task1() {
    Position end = dijkstra({MAX_X-1, MAX_Y-1}, false);

    return end.val;
}

int task2() {
    // Create the big map
    Position end = dijkstra({(MAX_X * 5)-1, (MAX_Y * 5)-1}, true);
    return end.val;
}

/* int_mat createBigMap() {
    int_mat big((MAX_Y+1) * 5);
    for (size_t yc = 0; yc < MAX_Y; yc++) {
        vector<int> row((MAX_X+1) * 5);
        for (size_t i = 0; i < row.size(); i++) {
            int x = 
        }
    }
} */

int main() {
    std::ifstream is("input");
    for (string s; getline(is, s);) {
        vector<int> row;
        for (char c : s) {
            if (c != '\r') {
                row.push_back(c - '0');
            }
        }
        MAP.push_back(row);
    }

    /* int_mat bigMap = createBigMap(); */

    MAX_X = MAP.front().size();
    MAX_Y = MAP.size();

    cout << task1() << endl;
    cout << task2() << endl;
    return 0;
}