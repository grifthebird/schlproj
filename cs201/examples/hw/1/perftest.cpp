/*
   Sample program to test the performance of sort algorithm.
   To Compile: g++ -std=c++17 perftest.cpp
   To Run: ./a.out
*/

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include "hw1.cpp"

int main(int argc, char *argv[]) {
	std::chrono::duration<double> timetaken[3][3];
	std::cout << "Problem Size\tTime Taken (seconds)" << std::endl;
	std::cout << "\t\tCase 1\tCase 2\tCase 3" << std::endl;
	for (int size = 10; size <= 100000000; size *= 10) {
	
		int *a = new int[size];

		// repeat each case for three times 
		for (int i = 0; i < 3; i++) {
			std::generate(a, a+size, std::rand);

			/* Case 1: sorting random values */
			auto starttime = std::chrono::steady_clock::now();
			quicksort(a, a+size);
			auto endtime = std::chrono::steady_clock::now();
			timetaken[i][0] = endtime - starttime;

			/* Case 2: sorting data that is already sorted */
			starttime = std::chrono::steady_clock::now();
			quicksort(a, a+size);
			endtime = std::chrono::steady_clock::now();
			timetaken[i][1] = endtime - starttime;

			/* Case 3: sorting data that is in reverse sorted order */
			std::reverse(a, a+size);
			starttime = std::chrono::steady_clock::now();
			quicksort(a, a+size);
			endtime = std::chrono::steady_clock::now();
			timetaken[i][2] = endtime - starttime;
		}

		// print the average time of three runs
		std::cout << size << "\t\t";
		std::cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count())/3.0 << "\t";
		std::cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count())/3.0 << "\t";
		std::cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count())/3.0 << std::endl;

		delete[] a;
	}

	return 0;
}


