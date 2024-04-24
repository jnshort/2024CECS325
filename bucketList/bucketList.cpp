// 
//
//
//
//
#include <ostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include<iostream>

int GLOBAL_SWAP_COUNT = 0;

class Bucket {
    private:
        std::vector<int> v;
    public:
        void generate(int, int, int);
        void sort();
        int size();
        int atIndex(int);
        void merge(Bucket);
};

void Bucket::generate(int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        int num = min + (std::rand() % (max-min+1));
        v.push_back(num);
    }
}

void Bucket::sort() {
    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < (this->size() - (i+1)); j++) {
            if (this->v[j] > this->v[j+1]) {
                int temp = this->v[j+1];
                this->v[j+1] = this->v[j];
                this->v[j] = temp;
                GLOBAL_SWAP_COUNT++;
            }
        }
    }
}

int Bucket::size() {
    return v.size();
}

int Bucket::atIndex(int index) {
    return v[index];
}

void Bucket::merge(Bucket b) {
    int i_max = this->size();
    int j_max = b.size();
    int i = 0;
    int j = 0;
    std::vector<int> temp;
    while (i < i_max && j < j_max) {
        if (this->atIndex(i) <= b.atIndex(j)) {
            temp.push_back(this->atIndex(i++));
        } else {
            temp.push_back(b.atIndex(j++));
        }
    }
    while (i < i_max) {
        temp.push_back(this->atIndex(i++));
    }
    while (j < j_max) {
        temp.push_back(b.atIndex(j++));
    }
    this->v = temp;
}

// usage: $ bucketList 100 100 1000000 9000000
// bucketList bucketCount bucketSize min max
int main(int argc, char *argv[]) {
    srand(time(0));

    int bucketCount = std::stoi(argv[1]);
    int bucketSize = std::stoi(argv[2]);
    int bucketMin = std::stoi(argv[3]);
    int bucketMax = std::stoi(argv[4]);
    std::cout << "Bucket Count:" << bucketCount << std::endl;
    std::cout << "Bucket Size:" << bucketSize << std::endl;
    std::cout << "Bucket Min Value:" << bucketMin << std::endl;
    std::cout << "Bucket Max value:" << bucketMax <<std::endl;

    std::vector<Bucket> list;  // create empty Bucket vector Bucket *bptr;
    Bucket *bptr;

    for (int i = 0; i < bucketCount; i++) {  // creating bucketCount Buckets
        bptr = new Bucket;          // allocating new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax);  //Bucket::generate(int,int,int,int)

        list.push_back(*bptr);  // pushing Bucket onto list
    }

    for (auto it = list.begin(); it != list.end(); it++) {
        it->sort();  // Bucket::sort
    }

    Bucket endGame;                // create empty Bucket to merge ALL buckets
    while (list.size() > 0) {      // vector<Bucket>::size()
        endGame.merge(list[0]);    // merge first bucket in list into
        list.erase(list.begin());  // erase the first bucket in the list
    }

    // write all the numbers in endGame bucket to a file
    std::fstream out("bucketList.out", std::ios::out);
    for (int i=0; i < endGame.size(); i++)       // Bucket::size()
        out << endGame.atIndex(i) << std::endl;  // Bucket::atIndex(int)
    std::cout << "Global Swap Count:"<< GLOBAL_SWAP_COUNT << std::endl;
    std::cout << "\nbucketList.out has " << bucketCount * bucketSize << " sorted numbers\n";
    return 0;
}

