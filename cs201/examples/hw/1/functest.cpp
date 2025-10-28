/* 
   Sample program to test std::sort with different containers.
   To Compile: g++ -std=c++17 functest.cpp
   To Run: ./a.out
*/

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "hw1.cpp"

template< class RandomIt >
void print(RandomIt start, RandomIt end) {
	while (start != end) {
		std::cout << *start << " ";
		++start;
	}
	std::cout << std::endl;
}


int main(int argc, char *argv[]) {
	int a0[] = {56, 23, 11, 64, 43};
	std::array<int, 5> a1 = {5, 4, 3, 2, 1};
	std::array<std::string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
	std::vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};

	quicksort(a0, a0+5);
	print(a0, a0+5);

	quicksort(&a0[0], &a0[5]);
	print(&a0[0], &a0[5]);

	quicksort(a1.begin(), a1.end());
	print(a1.begin(), a1.end());

	quicksort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	/*
	std::reverse(a2.begin(), a2.end());
	print(a2.begin(), a2.end());
	*/

	quicksort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	quicksort(v.begin(), v.end());
	print(v.begin(), v.end());

	return 0;
}


