#include <iostream>
#include <vector>

void insert(std::vector<int> & arr) { // in-class implementatiion of insertion sort
	int size = arr.size();
	for (int j = 1; j < size; j++) { // init j to 1 since first loop is already sorted
		int key = arr[j]; // current value to be sorted
		int i = j - 1; // upper bound of sorted portion
		while (i >= 0 && arr[i] > key) { // move key to proper position in sorted portioq
			arr[i + 1] = arr[i];
			i = i - 1;
	}
		arr[i + 1] = key;
	}
	return;
}

int main() {
	std::vector<int> input = {5, 2, 3, 4, 1};
	// print before and after
	for (int a : input) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
	insert(input);
	for (int a : input) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
	return 0;
}
