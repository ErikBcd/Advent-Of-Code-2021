#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

// Length of every input number
#define LENGTH 12

int task1() {
    std::ifstream is("input");
    int oneCount[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int lines = 0;

    for (std::string str; std::getline(is, str);) {
        for (size_t i = 0; i < LENGTH; i++) {
            if (str.at(i) == '1') { 
                oneCount[i]++; 
            }
        }
        lines++;
    }
    std::bitset<LENGTH> g(0);
    for (size_t i = 0; i < LENGTH; i++) {
        if (oneCount[i] > (lines - oneCount[i])) {
            g.set((LENGTH-1)-i, 1);
        }
    }

    std::bitset<LENGTH> e(g);
    e.flip();
    return ((int) (g.to_ulong() * e.to_ulong()));
}

/** Finds the common bit in a vector of bitsets at a given position */
bool commonBit(std::vector<std::bitset<LENGTH>> numbers, int position) {
    int ones = 0;
    int zeroes = 0;
    for (int i=0; i < numbers.size(); i++) {
        if (numbers[i][position] == 1) { ones++; }
        else { zeroes++; }
    }
    return (ones >= zeroes);
}

int task2() {
    std::ifstream is("input");
    std::vector<std::bitset<LENGTH>> oxNumbers;
    std::vector<std::bitset<LENGTH>> scNumbers;

    for (std::string str; std::getline(is, str);) {
        oxNumbers.push_back(std::bitset<LENGTH>(str));
        scNumbers.push_back(std::bitset<LENGTH>(str));
    }   

    // OXYGEN
    int pos = LENGTH-1;
    while (oxNumbers.size() != 1 && pos >= 0) {
        bool bitCriteria = commonBit(oxNumbers, pos);

        // Remove all entries that don't fit the criteria
        for (size_t i=0; i < oxNumbers.size(); i++) {
            if (oxNumbers[i][pos] != bitCriteria) {
                oxNumbers.erase(oxNumbers.begin() + i);
                i--;
            }
        }
        pos--;
    }

    // Reset pos
    pos = LENGTH-1;

    // CO2 SCRUBBER
    while (scNumbers.size() != 1 && pos >= 0) {
        bool bitCriteria = commonBit(scNumbers, pos);

        // Remove all entries that don't fit the criteria
        // The criteria is inverted in this case!
        for (size_t i=0; i < scNumbers.size(); i++) {
            if (scNumbers[i][pos] == bitCriteria) {
                scNumbers.erase(scNumbers.begin() + i);
                i--;
            }
        }
        pos--;
    }

    return ((int)oxNumbers[0].to_ulong() * scNumbers[0].to_ulong());
}

int main() {
    std::cout << "Task 1: " << task1() << " Task 2: " << task2() << std::endl;
    return 0;
}