/*
 * Name: Jayden White
 * Email: jtwhite18@crimson.ia.edu
 * Course Section: Spring 2025 CS 201
 * Homework #: 2
 * Instructions to Compile: g++ STsort.cpp -std=c++17
 * Instructions to Execute: ./a.out [input_file]
 */

#include <fstream>
#include <chrono>
#include <iostream>
#include <vector>
#include <regex>
#include "ST.hpp"

void parsetext(std::ifstream & input) {
   std::ofstream formatted;
   std::string text;
   std::vector<std::string> tokens;
   const std::regex delim("\\s+"); 

   formatted.open("buffer.txt");
   while (input >> text) {
      auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = std::sregex_token_iterator();
      for (std::sregex_token_iterator word = begin; word != end; word++) {
         tokens.push_back(*word);
      }
   }

   for(const auto & str : tokens)
      formatted << str << std::endl;

   formatted.close();
}

int main(int argc, char ** argv) {
	if (argc != 2) { return -1; } // incorrect argument count
	std::chrono::time_point<std::chrono::system_clock> begin, end;
	std::chrono::duration<double> time;
	ST<std::string, int> words;
	std::vector<std::pair<std::string, int> > vectoroutput;
	std::ifstream input(argv[1]);
	std::string curr;
	begin = std::chrono::system_clock::now();
	parsetext(input);
	input.close();
	input.open("buffer.txt");
	while (!input.eof()) {
		input >> curr;
		words[curr]++;
	}
	end = std::chrono::system_clock::now();
	words.display();
	vectoroutput = words.toVector();
	time = end - begin;
	std::cout << "time taken: " << time.count() << std::endl;
	std::cout << "unique words: " << vectoroutput.size() << std::endl;
	input.close();
	return 0;
}
