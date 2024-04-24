/// Short, Justin
// CECS 325-02
// Program 3: Bubble Sort
// Due Date: 03/12/2024
//
// I certify that this program is my own original work. I did not copy this 
// program from any other source. I further certify that I typed each and every
// line of code in this program.

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

void bubble(int * numbers, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < (len - (i+1)); j++) {
            if (numbers[j] > numbers[j+1]) {
                int temp = numbers[j+1];
                numbers[j+1] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
}



int main(int argc, char *argv[]) {
    std::ifstream inputFile(argv[1]);
    std::string line;
    int lineCount = 0;

    while (std::getline(inputFile, line)) {
        lineCount++;
    }
    inputFile.close();

    int numbers[lineCount];

    std::ifstream inputText(argv[1]);
    int n = 0;
    while (std::getline(inputText, line)) {
        numbers[n] = stoi(line);
        n++;
    }
    inputText.close();

    bubble(numbers, lineCount);

    std::ofstream outputFile;
    outputFile.open(argv[2]);
    for (int i = 0; i < lineCount; i++) {
        outputFile << numbers[i] << std::endl;
    }
    outputFile.close();

    return 0;
}
