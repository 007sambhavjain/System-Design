#include <iostream>
#include <bits/stdc++.h>
using namespace std;

using hashFunction = std::function<size_t(std::string const &)>;

class BloomFilter{

    public:
    int numberOfCells;
    std::vector<bool>cells;
    std::vector<hashFunction>hashFunctions;

    BloomFilter(int numberOfCells_,std::vector<hashFunction>hashFunctions_ ):
    numberOfCells(numberOfCells_),
    hashFunctions(hashFunctions_)
    {
      cells.resize(numberOfCells,false);
    }

    void addElements(const std::string &str ){
        for(auto hash:hashFunctions){
            cells[hash(str)%numberOfCells]=true;
        }
    }

    bool searchElements(const std::string &str ){
        bool check= true;

         for(auto hash:hashFunctions){
            if(cells[hash(str)%numberOfCells]==false){
                check=false;
                break;
            }
        }

       return check;
    }

      ~BloomFilter() {
        cells.clear();
    }

};

size_t djb2(const std::string &str) {
    size_t hash = 5381;

    for (auto iter : str) {
        hash = ((hash << 5) + hash) + iter;
    }

    return hash;
}

size_t sdbm(const std::string &str) {
    size_t hash = 0;

    for (auto iter : str) {
        hash = ((hash << 6) + (hash << 16) - hash) + iter;
    }

    return hash;
}

int main(){

    std::vector <hashFunction> hashFunctions;
    hashFunctions.push_back(sdbm);
    hashFunctions.push_back(djb2);

    BloomFilter bf(1024,hashFunctions);

    std::vector<std::string> setOfStrings({
        "Hello World!",
        "sweet potato",
        "C++",
        "alpha",
        "beta",
        "gamma"
    });


    std::cout << "Bloom filter created." << std::endl;
    std::cout << "Bloom filter tests for the following set of strings:" << std::endl;

    for (auto iter : setOfStrings) {
        bf.addElements(iter);
        std::cout << "\t" + iter << std::endl;
    }

    // testing a set of strings against the bloom filter
    std::vector<std::string> testSetOfStrings({
        "Hello World!",
        "sweet potato",
        "C++",
        "alpha",
        "beta",
        "gamma",
        "delta",
        "where am i?",
        "foo",
        "bar"
    });

    std::cout << "Testing set inclusion for the following strings:" << std::endl;
    std::cout << std::boolalpha;

    for (auto iter : testSetOfStrings) {
        std::cout << "\t" + iter + ": " << bf.searchElements(iter) << std::endl;
    }

}