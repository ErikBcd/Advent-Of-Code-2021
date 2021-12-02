#include <iostream>
#include <fstream>

int task1() {
    std::ifstream is("input");

    // Horizontal, Depth
    int position[] = {0,0};
    
    for (std::string str; std::getline(is, str);) {
        if (str.rfind("forward", 0) == 0) {
            int x = std::stoi(str.substr(7, str.length() - 7));
            position[0] += x;
        } else if (str.rfind("up", 0) == 0) {
            int x = std::stoi(str.substr(2, str.length() - 2));
            position[1] -= x;
        } else if (str.rfind("down", 0) == 0) {
            int x = std::stoi(str.substr(4, str.length() - 4));
            position[1] += x;
        } else {
            std::cout << "Error!\n";
        }
    }

    return position[0] * position[1];
}

int task2() {
    std::ifstream is("input");

    // Aim, Horizontal, Depth
    int position[] = {0,0,0};

    for (std::string str; std::getline(is, str);) {
        if (str.rfind("forward", 0) == 0) {
            int x = std::stoi(str.substr(7, str.length() - 7));
            position[1] += x;
            position[2] += position[0] * x;
        } else if (str.rfind("up", 0) == 0) {
            int x = std::stoi(str.substr(2, str.length() - 2));
            position[0] -= x;
        } else if (str.rfind("down", 0) == 0) {
            int x = std::stoi(str.substr(4, str.length() - 4));
            position[0] += x;
        } else {
            std::cout << "Error!\n";
        }
    }

    return position[1] * position[2];
}

int main() {
    std::cout << "Solution Task 1: " << task1() << " Task 2: " << task2() << std::endl;
    return 0;
}