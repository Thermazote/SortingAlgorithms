#include "Sorter.hpp"
#include <vector>
#include <algorithm>
#include <cassert>
#include <list>


void Sorter::selection_sort(std::vector<int>* vector, int first, int last)
{
    // find index of minimal element and swap current element with selected minimal element
    for (int i = first; i < last - 1; i++) {
        int index_of_min = i;

        for (int j = i + 1; j < last; j++) {
            if ((*vector)[j] < (*vector)[index_of_min]) {
                index_of_min = j;
            }
        }

        if (index_of_min != i) {
            std::swap((*vector)[i], (*vector)[index_of_min]);
        }
    }
}


void Sorter::insertion_sort(std::vector<int>* vector, int first, int last)
{
    // for each element search place in left part of array to insert current element
    for (int i = first + 1; i < last; i++) {
        int j = i;

        while ((j > 0) && ((*vector)[j - 1] > (*vector)[j]))
        {
            std::swap((*vector)[j - 1], (*vector)[j]);
            j--;
        }
    }
}


void Sorter::merge_sort(std::vector<int>* vector, int first, int last)
{
    if ((last - first) <= 1) {
        return;
    }

    // sort left and right part of vector
    auto vector_copy = *vector;
    int middle = (first + last) / 2;
    merge_sort(&vector_copy, first, middle);
    merge_sort(&vector_copy, middle, last);

    // merging two parts
    int left_pos = first;
    int right_pos = middle;
    int result_pos = first;

    while (left_pos != middle || right_pos != last) {
        if (left_pos == middle) {
            (*vector)[result_pos++] = vector_copy[right_pos++];
        }
        else if (right_pos == last) {
            (*vector)[result_pos++] = vector_copy[left_pos++];
        }
        else {
            if (vector_copy[left_pos] < vector_copy[right_pos]) {
                (*vector)[result_pos++] = vector_copy[left_pos++];
            }
            else {
                (*vector)[result_pos++] = vector_copy[right_pos++];
            }
        }
    }
}

void Sorter::heapify(std::vector<int> *vector, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && (*vector)[l] > (*vector)[largest])
        largest = l;

    if (r < n && (*vector)[r] >(*vector)[largest])
        largest = r;

    if (largest != i)
    {
        std::swap((*vector)[i], (*vector)[largest]);
        heapify(vector, n, largest);
    }
}

void Sorter::heap_sort(std::vector<int>* vector, int first, int last)
{
    for (int i = last / 2 - 1; i >= first; i--) {
        heapify(vector, last, i);
    }

    for (int i = last - 1; i >= first; i--)
    {
        std::swap((*vector)[0], (*vector)[i]);

        heapify(vector, i, first);
    }
}


void Sorter::quick_sort(std::vector<int>* vector, int first, int last)
{
    if (last - first <= 1) {
        return;
    }

    // swap random pivot with last element
    int pivot_index = std::rand() % (last - first) + first;
    std::swap((*vector)[pivot_index], (*vector)[last - 1]);
    
    // split vector into two parts (less than pivot and more than pivot)
    int i = first;
    for (int j = first; j < last - 1; j++) {
        if ((*vector)[j] < (*vector)[last - 1]) {
            std::swap((*vector)[i++], (*vector)[j]);
        }
    }
    std::swap((*vector)[i], (*vector)[last - 1]);

    // sort left and right part of vector
    quick_sort(vector, first, i - 1);
    quick_sort(vector, i + 1, last);
}


void Sorter::bucket_sort(std::vector<int>* vector, int first, int last)
{
    // create buckets
    int max = *std::max_element(vector->begin() + first, vector->begin() + last);
    int min = *std::min_element(vector->begin() + first, vector->begin() + last);
    int buckets_count = int(sqrt(last - first));
    std::vector<std::list<int>> buckets(buckets_count);


    // fill buckets
    for (int i = first; i < last; i++) {
        int bucket_index = int(round((((*vector)[i] - min) / (max - min)) * (buckets_count - 1)));
        buckets[bucket_index].push_back((*vector)[i]);
    }

    // sort buckets and write it sequentally in vector
    int pos = first;
    for (auto bucket : buckets) {
        bucket.sort();
        for (auto el : bucket) {
            (*vector)[pos++] = el;
        }
    }
}


void Sorter::bubble_sort(std::vector<int>* vector, int first, int last)
{
    // on each step pairwise compare all elements so on each step the greatest element will surface end of array
    bool is_sorted = true;
    for (int i = first; i < last - 1; i++) {
        for (int j = first; j < last - i - 1; j++) {
            if ((*vector)[j] > (*vector)[j + 1]) {
                std::swap((*vector)[j], (*vector)[j + 1]);
                is_sorted = false;
            }
        }

        if (is_sorted) {
            break;
        }
    }
}


void Sorter::counting_sort(std::vector<int>* vector, int first, int last)
{
    // create vector for saving the number of occurrences for each number in origianal vector 
    int max = *std::max_element(vector->begin() + first, vector->begin() + last);
    std::vector<int> occurrences_vector(max + 1, 0);

    // count occurrences of each number
    for (int i = first; i < last; i++) {
        occurrences_vector[(*vector)[i]]++;
    }

    // write each number found number of times
    int pos = first;
    for (int value = 0; value < occurrences_vector.size(); value++) {
        for (int k = 0; k < occurrences_vector[value]; k++) {
            (*vector)[pos++] = value;
        }
    }
}


void Sorter::radix_sort(std::vector<int>* vector, int first, int last)
{
    std::vector<int> elements_bit_0(last - first);
    std::vector<int> elements_bit_1(last - first);

    for (int bit = 0; bit < 8 * sizeof(int); bit++) {
        int elements_bit_0_pos = 0;
        int elements_bit_1_pos = 0;

        // sort elements by current bit 
        for (int i = first; i < last; i++) {
            if ((*vector)[i] & (int)pow(2, bit)) {
                elements_bit_1[elements_bit_1_pos++] = (*vector)[i];
            }
            else {
                elements_bit_0[elements_bit_0_pos++] = (*vector)[i];
            }
        }

        // sequentially write zero bit elements then one bit elements to original array
        for (int i = 0; i < elements_bit_0_pos; i++) {
            (*vector)[first + i] = elements_bit_0[i];
        }

        for (int i = 0; i < elements_bit_1_pos; i++) {
            (*vector)[first + elements_bit_0_pos + i] = elements_bit_1[i];
        }
    }
}
