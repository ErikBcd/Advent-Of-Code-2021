#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

ulong fishSim(int days) {
    std::ifstream is("input");

    std::string str;
    std::getline(is, str);
    std::stringstream s(str);

    // Setup an array that only contains how many fishes are being born at one day
    ulong fishes1[9] = {0,0,0,0,0,0,0,0,0};
    ulong fishes2[9] = {0,0,0,0,0,0,0,0,0};
    bool clk = true;
    while(s.good()) {
        std::getline(s, str, ',');
        fishes1[std::stoi(str)]++;
    }

    // Algorithm: For i!=6: fishY[i] = fishX[i+1]
    //            For i =6: fishY[6] = fishX[7] + fishX[0]
    // e.g: Rotate all former values to position i-1 and set i=6 to the new fish + fi
    for (size_t x = 0; x < (days+1); x++) {
        if (clk) {
            for (int i = 0; i < 8; i++) {
                fishes2[i] = fishes1[i+1];
            }
            fishes2[6] += fishes1[0];
            fishes2[8]  = fishes1[0];
        } else {
            for (int i = 0; i < 8; i++) {
                fishes1[i] = fishes2[i+1];
            }
            fishes1[6] += fishes2[0];
            fishes1[8]  = fishes2[0];
        }
        clk = !clk;
    }

    ulong fishes = 0;
    for (size_t i = 0; i < 8; i++) {
        fishes += (clk) ? fishes1[i] : fishes2[i];
    }

    return fishes;
}

int main() {
    std::cout << "Task 1: " << fishSim(80) << "\nTask 2: " << fishSim(256);
    return 0;
}