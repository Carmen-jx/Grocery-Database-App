
#include <fstream>
#include <iostream>
#include "PosApp.h"
void resetDataFile();
void displayfileContent();
int main() {
    resetDataFile();
    displayfileContent();
    sdds::PosApp pos("posdata.csv");
    pos.run();
    displayfileContent();
    return 0;
}
void resetDataFile() {
    char ch{};
    std::ofstream outfile("posdata.csv");
    std::ifstream infile("posdataOrigin.csv");
    while(infile.get(ch)) {
        outfile.put(ch);
    }
}
void displayfileContent() {
    std::cout << "Data file:\n------------------\n";
    char ch{};
    std::ifstream infile("posdata.csv");
    while(infile.get(ch)) {
        std::cout.put(ch);
    }
    std::cout << "------------------\n";
}
