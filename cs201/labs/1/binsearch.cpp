/* 
   Program to perform binary search using iterators 

   To Compile: g++ -Wall -std=c++20 -o binarysearch.exe binarysearch.cpp
   To Run: ./binarysearch.exe 
           <enter a number to search or Control-D to end> 
*/
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

template< class RandomIt >
void print(RandomIt start, RandomIt end) {
	while (start != end) {
		std::cout << *start << " ";
		++start;
	}
	std::cout << std::endl;
}


template< class ForwardIt, class T >
constexpr bool binarysearch( ForwardIt first, ForwardIt last,
                const T& value ) {
        auto low = first;
        auto high = last-1;
        while (low <= high) {
                auto mid = low + std::distance(low, high)/2;
                std::cout << *low << " " << *mid << " " << *high << std::endl;

                if (*mid < value)
                   low = mid + 1;
                else if (*mid > value)
                   high = mid - 1;
                else
                   return true;
        }
        return false;
}


template< class ForwardIt, class T >
constexpr bool recursive_binarysearch( ForwardIt first, ForwardIt last, 
					const T& value ) {
        auto low = first;
        auto high = last-1;
	if (low <= high) {
		auto mid = low + std::distance(low, high)/2;
		std::cout << *low << " " << *mid << " " << *high << std::endl;

		if (*mid < value) 
		   return recursive_binarysearch(mid + 1, last, value);
		else if (*mid > value) 
		   return recursive_binarysearch(first, mid, value);
		else
		   return true;
	} else 
		return false;
}


int main(int argc, char *argv[]) {
	std::array<int, 12> a1 = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	print(a1.begin(), a1.end());

	std::sort(a1.begin(), a1.end());
	print(a1.begin(), a1.end());

	std::cout << "Enter an integer: ";
	int value = 0;
	while (std::cin >> value) {
		if (binarysearch(a1.begin(), a1.end(), value)) 
		   std::cout << value << " found!" << std::endl;
		else
		   std::cout << value << " not found!" << std::endl;

		if (recursive_binarysearch(a1.begin(), a1.end(), value)) 
		   std::cout << value << " found!" << std::endl;
		else
		   std::cout << value << " not found!" << std::endl;

		std::cout << "Enter an integer: ";
	}

	return 0;
}


