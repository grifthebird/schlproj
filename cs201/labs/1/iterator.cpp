/* 
   Sample C++ program to illustrate the use of C++ iterators and containers

   To Compile: g++ -Wall -std=c++20 -o sample2.exe sample2.cpp
   To Run: ./sample2.exe
*/
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

template< class RandomIt > // using a template to print an array of a generic type
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

	std::sort(a0, a0+5);
	print(a0, a0+5);

	std::sort(&a0[0], &a0[5]);
	print(&a0[0], &a0[5]);

	std::sort(a1.begin(), a1.end());
	print(a1.begin(), a1.end());

	std::sort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	std::reverse(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	std::sort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	std::sort(v.begin(), v.end());
	print(v.begin(), v.end());

	return 0;
}


