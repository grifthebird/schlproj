#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

template < class RandomIt >
constexpr void heapify(RandomIt curr, RandomIt first, RandomIt last) {
	RandomIt greatest;
	RandomIt left;
	RandomIt right;

	left = curr;
	left++;
	std::advance(left, (left - first));
	left--;

	right = curr;
	right++;
	std::advance(right, (right - first));

	if ((left - last < 0) && *left > *curr) {
		greatest = left;
	}
	else {
		greatest = curr;
	}

	if ((right - last < 0) && *right > *greatest) {
		greatest = right;
	}

	if (greatest != curr) {
		std::swap(*greatest, *curr);
		heapify(greatest, first, last);
	}
	return;
}

template < class RandomIt>
constexpr void heapsort(RandomIt first, RandomIt last) {
	int size = last - first;
	RandomIt curr = first + (size / 2);
	// build max heap
	for (int i = size / 2; i >= 0; i--) {
		heapify(curr, first, last);
		curr--;
	}

	for (int i = size; i > 1; i--) {
		// remove max value
		std::swap(*first, *(last - 1));
		last--;
		// rebuild heap
		heapify(first, first, last);
	}
	/* print output
	for (int i = 0; i < size; i++) {
		std::cout << *(first + i) << " ";
	}
	std::cout << std::endl;
	*/

	return;
}

template < class RandomIt >
constexpr int partition(RandomIt first, RandomIt last) {
	RandomIt pivot = last - 1;
	int i = -1;
	for (int j = 0; j < (last - first) - 1; j++) {
		if (*(first + j) <= *pivot) {
			i++;
			std::swap(*(first + i), *(first + j));
		}
	}
	std::swap(*(first + (i + 1)), *pivot);
	return i + 1;
}

template < class RandomIt >
constexpr void quicksort(RandomIt first, RandomIt last) {
	if (last - first > 1) {
		RandomIt p = first + (std::distance(first, last) / 2);
		std::swap(*p, *(last - 1));
		int q = partition(first, last);
		quicksort(first, first + q);
		quicksort(first + (q + 1), last);
	}
	return;
}

/*
int main() {
	std::vector<int> arr = {4,76,23,6,256,345,23,1};
	std::vector<int>::iterator first = arr.begin();
	std::vector<int>::iterator last = arr.end();
	int size = last - first;
	//heapsort(first, last);
	quicksort(first, last);
	//std::sort(first, last);
	// print output
	for (int i = 0; i < size; i++) {
		std::cout << *(first + i) << " ";
	}
	std::cout << std::endl;
	return 0;
}
*/



