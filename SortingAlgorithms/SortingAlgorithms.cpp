#include <iostream>
#include "Sorter.hpp"
#include <vector>
#include <ctime>
#include <fstream>


struct method_t {
    std::string name = "";
    void (Sorter::*function)(std::vector<int>*, int, int) = NULL;
};

void fill_vector(std::vector<int>* vector, int range)
{
    for (auto elem = (*vector).begin(); elem < (*vector).end(); elem++) {
        *elem = std::rand() % range;
    }
}

int main()
{
    Sorter sorter;
    std::srand(std::time(NULL));
    const int range = 1000;

    // generating different sized vectors with random values
    std::cout << "Generating vectors..." << std::endl;
    std::vector<std::vector<int>*> test_vectors;
    for (int i = 100; i <= 100000; i *= 10) {
        for (int size = i; size < i * 10; size += i) {
            std::vector<int> *test_vector = new std::vector<int>(size);
            fill_vector(test_vector, range);
            test_vectors.push_back(test_vector);
        }
    }
    
    // add methods that will be tested
    std::vector<method_t> methods(1);
    methods[0].name = "Selection sort";
    methods[0].function = &Sorter::selection_sort;

    // open the file the results will be written to
    std::fstream file;
    file.open("results.txt", 'w');

    // start tests
    std::cout << "Testing..." << std::endl;
    for (auto method: methods) {
        file << "Method: " << method.name << std::endl;
        for (auto test_vector: test_vectors) {
            std::vector<int> vector_copy = *test_vector;
            time_t start = std::clock();
            (sorter.*method.function)(&vector_copy, 0, vector_copy.size());
            time_t end = std::clock();
            file << "-------------------------" << std::endl
                 << "Size: " << test_vector->size() << std::endl
                 << "Elapsed time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
        }
        file << std::endl;
    }

    // delete alocated memory
    for (auto test_vector: test_vectors) {
        delete test_vector;
    }

    return 0;
}