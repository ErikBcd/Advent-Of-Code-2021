#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

/**
 * @brief Calculates the cost to move the crabs to a given position
 * 
 * @param positions Positions of the crabs
 * @param position Destination
 * @param fuelCalc Lambda for fuel calculation
 * @return int Fuel cost
 */
int fuelCostCalc(std::vector<int> *positions, int position, std::function<int (int, int)> fuelCalc) {
    int fuel = 0;
    for (int p : *positions) {
        fuel += fuelCalc(p, position);
    }
    return fuel;
}

int task(int maxPos, std::vector<int> *position, std::function<int (int, int)> fuelCalc) {
    // Find the minimal fuel cost.
    // There are many super optimized algorithms for this, and I chose the slowest one.
    // Deal with it 8)
    int fuelCostMin = INT_MAX;
    int chosenPosition = -1;

    for (int pos = 0; pos <= maxPos; pos++) {
        int f = fuelCostCalc(position, pos, fuelCalc);
        if (f < fuelCostMin) {
            chosenPosition = pos;
            fuelCostMin = f;
        }
    }
    return fuelCostMin;
}


int main() {
    // Read input
    std::ifstream is("input");
    std::string str;
    std::getline(is, str);
    std::stringstream s(str);

    std::vector<int> position;
    int maxPos = -1;
    while(s.good()) {
        std::getline(s, str, ',');
        position.push_back(std::stoi(str));
        if (position.back() > maxPos) {
            maxPos = position.back();
        }
    }

    // Lambdas for the fuel calculation of task 1 and 2
    auto fuelCalcTask1 = [](int a, int b) {
        return abs(a-b);
    };

    auto fuelCalcTask2 = [](int a, int b) {
        int d = abs(a-b);
        return (int) ((0.5 * (double) d) * (d+1));
    };

    std::cout <<   "Task 1: " << task(maxPos, &position, fuelCalcTask1) 
              << "\nTask 2: " << task(maxPos, &position, fuelCalcTask2);
    return 0;
}