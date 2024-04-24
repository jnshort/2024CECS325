/// Short, Justin
// CECS 325-02
// Program 4: Sortrace With Pthreads
// Due Date: 03/26/2024
//
// I certify that this program is my own original work. I did not copy this 
// program from any other source. I further certify that I typed each and every
// line of code in this program.

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <pthread.h>

// Struct to pass args into bubble() 
struct bubble_args {
    int * bin;
    int bin_size;
};

// Function to bubble sort an array in place
void *bubble(void *ptr) {
    bubble_args *arg = (bubble_args *) ptr;
    int len = arg->bin_size;
    int * numbers = arg->bin;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < (len - (i+1)); j++) {
            if (numbers[j] > numbers[j+1]) {
                int temp = numbers[j+1];
                numbers[j+1] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
    return NULL;
}

// Function to merge 2 subarrays in an array
// Arguments assume equal sized subarrays
void merge(int numbers[], int start, int bin_size) {

    // Initialize temp arrays
    int *tempbin1 = new int[bin_size];
    int *tempbin2 = new int[bin_size];

    // Populate temp arrays
    for (int i = 0; i < bin_size; i++) {
        tempbin1[i] = numbers[i];
        tempbin2[i] = numbers[i+bin_size];
    }


    // Indexes of respective arrays
    int index_bin_1 = 0;
    int index_bin_2 = 0;
    int index_merged = start;

    // Overwrite original array with sorted values from subarrays
    while (index_bin_1 < bin_size && index_bin_2 < bin_size) {
        if (tempbin1[index_bin_1] <= tempbin2[index_bin_2]) {
            numbers[index_merged] = tempbin1[index_bin_1];
            index_bin_1++;
        } else {
            numbers[index_merged] = tempbin2[index_bin_2];
            index_bin_2++;
        }
        index_merged++;
    }
    while (index_bin_1 < bin_size) {
        numbers[index_merged] = tempbin1[index_bin_1];
        index_bin_1++;
        index_merged++;
    }
    while (index_bin_2 < bin_size) {
         numbers[index_merged] = tempbin2[index_bin_2];
         index_bin_2++;
         index_merged++;
    }
}


int main(int argc, char *argv[]) {
    std::ifstream inputFile(argv[1]);
    std::string line;
    int lineCount = 0;

    // Determine size of input
    while (std::getline(inputFile, line)) {
        lineCount++;
    }
    inputFile.close();

    int numbers[lineCount];

    // Take file and store numbers in an array
    std::ifstream inputText(argv[1]);
    int n = 0;
    while (std::getline(inputText, line)) {
        numbers[n] = stoi(line);
        n++;
    }
    inputText.close();


    // Determine splie size
    // Create pointers to subarrays
    int split_size = lineCount/8;

    int * bin0 = &numbers[0];
    int * bin1 = &numbers[1*split_size];
    int * bin2 = &numbers[2*split_size];
    int * bin3 = &numbers[3*split_size];
    int * bin4 = &numbers[4*split_size];
    int * bin5 = &numbers[5*split_size];
    int * bin6 = &numbers[6*split_size];
    int * bin7 = &numbers[7*split_size];

    // Create argument objects to call bubble() on subarrays
    bubble_args b0;
    b0.bin = bin0;
    b0.bin_size = split_size;

    bubble_args b1;
    b1.bin = bin1;
    b1.bin_size = split_size;

    bubble_args b2;
    b2.bin = bin2;
    b2.bin_size = split_size;

    bubble_args b3;
    b3.bin = bin3;
    b3.bin_size = split_size;

    bubble_args b4;
    b4.bin = bin4;
    b4.bin_size = split_size;

    bubble_args b5;
    b5.bin = bin5;
    b5.bin_size = split_size;

    bubble_args b6;
    b6.bin = bin6;
    b6.bin_size = split_size;

    bubble_args b7;
    b7.bin = bin2;
    b7.bin_size = split_size;

    // Initialize threads and ints to store pthread_create return values
    pthread_t thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7;

    int iret0, iret1, iret2, iret3, iret4, iret5, iret6, iret7;

    // Create the threads and pass them function and values
    iret0 = pthread_create(&thread0, NULL, bubble, (void *) &b0);
    iret1 = pthread_create(&thread1, NULL, bubble, (void *) &b1);
    iret2 = pthread_create(&thread2, NULL, bubble, (void *) &b2);
    iret3 = pthread_create(&thread3, NULL, bubble, (void *) &b3);
    iret4 = pthread_create(&thread4, NULL, bubble, (void *) &b4);
    iret5 = pthread_create(&thread5, NULL, bubble, (void *) &b5);
    iret6 = pthread_create(&thread6, NULL, bubble, (void *) &b6);
    iret7 = pthread_create(&thread7, NULL, bubble, (void *) &b7);

    // Wait for all threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);

    // Merge the arrays in place
    for (int i = 0; i < 8; i=i+2) {
        merge(numbers, split_size*i, split_size);
    }
    for (int i = 0; i <8; i=i+4) {
        merge(numbers, split_size*i, split_size*2);
    }
    merge(numbers, 0, split_size*4);



    // Write outputs to output file
    std::ofstream outputFile;
    outputFile.open(argv[2]);
    for (int i = 0; i < lineCount; i++) {
        outputFile << numbers[i] << std::endl;
    }
    outputFile.close();

    return 0;
}
