#include <iostream>
#include <fstream>
#include <vector>

struct bingoCard
{
    int card[5][5];
    int cardEdit[5][5];
};

/**
 * @brief Reads a string with char-seperated integer values and stores them in a int vector
 * 
 * @param str String with seperated integer values
 * @param sep Seperator between values
 * @return std::vector<int> List of integer values
 */
std::vector<int> readSeperatedValues(std::string str, char sep) {
    std::vector<int> numbers;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] != sep) {
            std::string sub = "";
            sub = sub + str[i];
            i++;
            while (str[i] != sep && i < str.length()) {
                sub = sub + str[i];
                i++;
            }
            numbers.push_back(std::stoi(sub));
        }
    }
    return numbers;
}

/**
 * @brief Checks if a card has won.
 * 
 * @param c The card
 * @param row Row of the last changed number
 * @param col Column of the last changed number
 */
bool cardWon(bingoCard* c, int row, int col) {
    // Check col
    bool colCheck = true;
    for (size_t x = 0; x < 5; x++) {
        if (c->cardEdit[x][col] != -1) {
            colCheck = false;
            break;
        }
    }

    if (colCheck) { return true; }

    // Check row
    for (size_t x = 0; x < 5; x++) {
        if (c->cardEdit[row][x] != -1) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Calculates the score of a given card c with the last changed number.
 */
int calculateScore(bingoCard* c, int number) {
    int score = 0;
    for (size_t x = 0; x < 5; x++) {
        for (size_t y = 0; y < 5; y++) {
            if (c->cardEdit[x][y] != -1) {
                score += c->card[x][y];
            }
        }
    }

    return score * number;
}

/** 
 * Marks a number on a bingo card and checks if the game is won
 * If the game is won it returns the winning score.
 */
int markNumber(bingoCard* c, int number) {
    for (size_t x = 0; x < 5; x++) {
        for (size_t y = 0; y < 5; y++) {
            if (c->card[x][y] == number) {
                c->cardEdit[x][y] = -1;
                if (cardWon(c, x, y)) {
                    return calculateScore(c, number);
                } else {
                    return -1;
                }
            }
        }
    }

    return -1;
}

/**
 * @brief Reads all bingo cards from the input
 * 
 * @param is Points on a ifstream associated to the input file
 * @return std::vector<bingoCard> List of bingo cards
 */
std::vector<bingoCard> getBingoCards(std::ifstream* is) {
    int ctr = 0;
    std::vector<bingoCard> bingoCards;
    bool notAtEnd = true;
    std::string str;

    while (notAtEnd) {
        bingoCard c;
        for (size_t i = 0; i < 5; i++) {
            if (!std::getline(*is, str)) {
                notAtEnd = false;
                break;
            }
            std::vector<int> row = readSeperatedValues(str, ' ');
            for (size_t z = 0; z < 5; z++) {
                c.card[i][z] = row[z];
                c.cardEdit[i][z] = row[z];
            }
        }
        if (notAtEnd) {
            bingoCards.push_back(c);
        }
        std::getline(*is, str);
    }

    return bingoCards;
}

int task1() {
    std::ifstream is("input");

    std::string str;
    std::getline(is, str);

    // First get the bingo numbers
    std::vector<int> numbers = readSeperatedValues(str, ',');

    // Next line is always empty
    std::getline(is, str);

    // Then get each bingo card
    std::vector<bingoCard> bingoCards = getBingoCards(&is);
    

    // Analyze each bingo card
    bool cardWon = false;
    int winningCard = -1, score = -1;

    // For every number, mark every card and check if a card wins.
    // If it wins, exit the loop and print the score.
    for (size_t i = 0; i < numbers.size() && !cardWon; i++) {
        for (size_t x = 0; x < bingoCards.size(); x++) {
            int s = markNumber(&bingoCards[x], numbers[i]);
            if (s != -1) {
                winningCard = x;
                score = s;
                cardWon = true;
                break;
            }
        }
    }

    std::cout << "First Winning Card: " << winningCard << " Score: " << score << std::endl;

    return 0;
}

int task2() {
    std::ifstream is("input");

    std::string str;
    std::getline(is, str);

    // First get the bingo numbers
    std::vector<int> numbers = readSeperatedValues(str, ',');

    // Next line is always empty
    std::getline(is, str);

    // Then get each bingo card
    std::vector<bingoCard> bingoCards = getBingoCards(&is);

    // Analyze each bingo card
    bool cardWon = false;
    int winningCard = -1, score = -1;

    // Fill in numbers until the last card wins. 
    // Then return the score of the card.
    for (size_t i = 0; i < numbers.size() && !cardWon; i++) {
        for (size_t x = 0; x < bingoCards.size(); x++) {
            int s = markNumber(&bingoCards[x], numbers[i]);
            if (s != -1) {
                if (bingoCards.size() == 1) {
                    winningCard = x;
                    score = s;
                    cardWon = true;
                    break;
                } else {
                    bingoCards.erase(bingoCards.begin() + x);
                    x--;
                }
            }
        }
    }

    std::cout << "Last Winning Card Score: " << score << std::endl;

    return 0;
}

int main() {
    task1();
    task2();
    return 0;
}