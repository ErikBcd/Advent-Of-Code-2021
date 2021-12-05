#include <iostream>
#include <fstream>
#include <vector>

struct point
{
    int x;
    int y;

    std::string printPoint() {
        return ("(" + std::to_string(x) + "," + std::to_string(y) + ")");
    }
};

struct line
{
    point start;
    point end;

    std::string printLine() {
        return start.printPoint() + " -> " + end.printPoint();
    }
};

/**
 * @brief This is the most stupid shit I ever wrote.
 *        Please just ignore it.
 * 
 * @param s 
 * @return line 
 */
line stringToLine(std::string s) {
    point start;
    point end;
    std::string temp = "";
    size_t c = 0;
    // x1
    while (s[c] != ',') {
        temp = temp + s[c];
        c++;
    }
    start.x = std::stoi(temp);
    temp = "";
    c++;

    // y1
    while (s[c] != ' ') {
        temp = temp + s[c];
        c++;
    }
    start.y = std::stoi(temp);
    temp = "";
    c += 3;

    while (s[c] != ',') {
        temp = temp + s[c];
        c++;
    }
    end.x = std::stoi(temp);
    temp = "";
    c++;

    while (c<s.length()) {
        temp = temp + s[c];
        c++;
    }
    end.y = std::stoi(temp);

    return line {start, end};
}

void drawLine(int *field, line l, int fieldMaxX, int *overlaps) {
    // Determine slope
    int slopeX = (l.start.x == l.end.x) ? 0 : (l.start.x > l.end.x) ? -1 : 1;
    int slopeY = (l.start.y == l.end.y) ? 0 : (l.start.y > l.end.y) ? -1 : 1;

    int x = l.start.x;
    int y = l.start.y;

    // Draw line in field and count overlaps
    while (x != l.end.x || y != l.end.y) {
        field[y*fieldMaxX + x]++;
        if (field[y*fieldMaxX + x] == 2) { (*overlaps)++; }
        x += slopeX;
        y += slopeY;
    }

    // Set the last field
    field[y*fieldMaxX + x]++;
    if (field[y*fieldMaxX + x] == 2) { (*overlaps)++; }
}

int task1() {
    std::ifstream is("input");

    // Read input
    std::vector<line> lines;
    int sizeX = 0;
    int sizeY = 0;

    for(std::string str; std::getline(is, str);) {
        line l = stringToLine(str);
        if (l.start.x == l.end.x || l.start.y == l.end.y) {
            lines.push_back(l);
            // Set new bounds for field if needed
            int maxX = std::max(l.end.x, l.start.x);
            int maxY = std::max(l.end.y, l.start.y);
            sizeX = (maxX > sizeX) ? maxX : sizeX;
            sizeY = (maxY > sizeY) ? maxY : sizeY;
        }
    }

    int *field = new int[sizeX * sizeY];
    for (int i = 0; i < sizeX * sizeY; i++) { field[i] = 0; }

    int overlaps = 0;
    for (line l : lines) {
        drawLine(field, l, sizeX, &overlaps);
    }

    return overlaps;
}

int task2() {
    std::ifstream is("input");

    // Read input
    std::vector<line> lines;
    int sizeX = 0;
    int sizeY = 0;

    for(std::string str; std::getline(is, str);) {
        lines.push_back(stringToLine(str));
        int maxX = std::max(lines.back().end.x, lines.back().start.x);
        int maxY = std::max(lines.back().end.y, lines.back().start.y);
        sizeX = (maxX > sizeX) ? maxX : sizeX;
        sizeY = (maxY > sizeY) ? maxY : sizeY;
    }

    int *field = new int[sizeX * sizeY];
    for (int i = 0; i < sizeX * sizeY; i++) { field[i] = 0; }

    int overlaps = 0;
    for (line l : lines) {
        drawLine(field, l, sizeX, &overlaps);
    }

    return overlaps;
}

int main() {
    std::cout << "Task 1: " << task1() << std::endl;
    std::cout << "Task 2: " << task2() << std::endl;
    return 0;
}