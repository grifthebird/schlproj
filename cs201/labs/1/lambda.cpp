/*
   Sample program to illustrate the use of std::sort and lambda functions

   To Compile: g++ -Wall -std=c++20 -o sample1.exe sample1.cpp
   To Run: ./sample1.exe
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
	std::vector<std::string> a = {"lion", "dog", "cat", "fox", "pig"};

	auto print = [&a](std::string_view const comment) {
		for (auto item : a)
			std::cout << item << " ";
		std::cout << " : " << comment << std::endl;
	};

	std::sort(a.begin(), a.end());
	print("with default < operator");

	std::sort(a.begin(), a.end(), std::greater<std::string>());
	print("with std::greater<>()");

	std::sort(a.begin(), a.end(), std::less<std::string>());
	print("with std::less<>()");

	std::reverse(a.begin(), a.end());
	print("after reverse");



	std::sort(a.begin(), a.end(), [](std::string a, std::string b) {
			return  a > b;
		});
	print("with lambda expression");

	return 0;
}


