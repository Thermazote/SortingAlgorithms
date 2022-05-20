#pragma once
#include <vector>

class Sorter
{
private:
	void heapify(std::vector<int>* vector, int n, int i);
public:
	void selection_sort(std::vector<int>* vector, int first, int last);
	void insertion_sort(std::vector<int>* vector, int first, int last);
	void merge_sort(std::vector<int>* vector, int first, int last);
	void heap_sort(std::vector<int>* vector, int first, int last);
	void quick_sort(std::vector<int>* vector, int first, int last);
	void bucket_sort(std::vector<int>* vector, int first, int last);
	void bubble_sort(std::vector<int>* vector, int first, int last);
	void counting_sort(std::vector<int>* vector, int first, int last);
	void radix_sort(std::vector<int>* vector, int first, int last);
};

