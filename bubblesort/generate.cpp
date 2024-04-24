/// Short, Justin
// CECS 325-02
// Program 3: Bubble Sort
// Due Date: 03/12/2024
//
// I certify that this program is my own original work. I did not copy this
// program from any other source. I further certify that I typed each and every
// line of code in this program.

#include <fstream>
#include <string>
#include <ctime>

int main(int argc, char *argv[]) {
    int count = std::stoi(argv[1]);
    int min = std::stoi(argv[2]);
    int max = std::stoi(argv[3]);

    srand(time(0));


    std::ofstream numbers;
    numbers.open("numbers.dat");

    int n = 0;

    while (n < count) {
        numbers << min + (std::rand() % (max-min+1)) << std::endl;
        n++;
    }
    numbers.close();

    return 0;
}
