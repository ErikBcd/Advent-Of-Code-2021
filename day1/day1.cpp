#include <iostream>
#include <fstream>
#include <vector>

int partOne() {
    std::ifstream is("input");
    int y = -1;
    int incCtr = 0;
    for (std::string str; std::getline(is, str);) {
        int x = std::stoi(str);
        if (y != -1 && x > y) { incCtr++; }
        y = x;
    }

    return incCtr;
}

int partTwo() {
    std::ifstream is("input");
    int incCtr = 0;

    std::vector<int> n;

    for (std::string str; std::getline(is, str);) {
        n.push_back(std::stoi(str));
    }

    int ai = 1;
    int bi = 2;

    while (n.size() - 1 > bi) {
        int a = n[ai-1] + n[ai] + n[ai+1];
        int b = n[bi-1] + n[bi] + n[bi+1];
        if (a<b) { incCtr++; }
        ai++;
        bi++;
    }

    return incCtr;
}

int main() {
    std::cout << "Part 1: " << partOne() << " increases.\n";
    std::cout << "Part 2: " << partTwo() << " increases.\n";
    return 0;
}