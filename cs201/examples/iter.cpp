#include <iostream>
#include <vector>
#include <iterator>

// insertion sort algorithm with iterators
std::vector<int> insert(std::vector<int> &input) {
	std::vector<int>::iterator cmp = input.begin();
	int sorted = 1;
	cmp+=sorted;
	int buffer;
	while (cmp != input.end()) {
		while (cmp != input.begin()) {
			if (*cmp < *(cmp - 1)) {
				buffer = *cmp;
				*cmp = *(cmp - 1);
				*(cmp - 1) = buffer;
				cmp--;
			}
			else {
				break;
			}
		}
		sorted++;
		cmp = input.begin() + sorted;
	}
	return input;
}

int main() {
	std::vector<int> arr = {56,6,457,5,5,74,1,65,46};
	std::vector<int>::iterator curr = arr.begin();
	while (curr != arr.end()) {
		std::cout << *curr << " ";
		curr++;
	}
	std::cout << std::endl;
	insert(arr);
	curr = arr.begin();
	while (curr != arr.end()) {
		std::cout << *curr << " ";
		curr++;
	}
	std::cout << std::endl;
	return 0;
}
