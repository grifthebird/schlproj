#include <iostream>
#include <string>
#include <vector>

int fib(int n, std::vector<int> * arr, int * count) {
	if (arr->at(n) >= 65535) {
		(*count)++;
		arr->at(n) = fib(n - 1, arr, count) + fib(n - 2, arr, count);
		return arr->at(n); 
	}
	else {
		(*count)++;
		return arr->at(n);
	}
}

int fib2(int n, int * count) {
	if (n == 0) { (*count)++; return 0; }
	else if (n == 1) { (*count)++; return 1; }
	else { (*count)++; return fib2(n - 1, count) + fib2(n - 2, count); }
}

int main(int argc, char ** argv) {
	int input = std::stoi(argv[1]);
	std::vector<int> arr;
	for (int i = 0; i < input + 1; i++) {
		if (i == 0) { arr.push_back(0); }
		else if (i == 1) { arr.push_back(1); }
		else { arr.push_back(65535); }
	}
	int * count = new int;
	int * count2 = new int;
	(*count) = 0;
	(*count2) = 0;
	fib2(input, count2);
	std::cout << "fib(input) = " << fib(input, &arr, count) << std::endl <<
		"with memoization: " << *count << std::endl <<
		"without memoization: " << *count2 << std::endl;
	delete count;
	delete count2;
	return 0;
}
