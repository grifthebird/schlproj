/*
 * Name: Jayden White
 * Email: jtwhite18@crimson.ua.edu
 * Course Section: Spring 2025 CS 201
 * Homework #: 3
 * Instructions to Compile: g++ hw3.cpp -std=c++17
 * Instructions to Execure: ./a.out [dbfile] [query_file]
 */

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <chrono>
//#include <bits/stdc++.h> // required to use sort on remote server

class movie {
	// classs for holding movie attributes
	public:
		std::string title;
		std::unordered_map<int, std::string> cast;
		movie() {
			this->title = "tbd";
		}
		void setTitle(std::string title);
		void addCast(std::string member);
		static int hash(std::string input);
		void reset();
};

// class methods
void movie::setTitle(std::string title) {
	this->title = title;
	return;
}

int movie::hash(std::string input) {
	int hash = 0;
	for (int i  = 0; i < input.size(); i++) {
		hash += input.at(i);
	}
	hash *= input.size();
	return hash;
}

void movie::addCast(std::string member) {
	this->cast[hash(member)] = member;
	return;
}

void movie::reset() {
	this->title = "tbd";
	this->cast.clear();
	return;
}

void search(std::vector<movie> input, std::string query) {
	bool success = false;
	if (query.find("(") == std::string::npos && query.find(")") == std::string::npos) {
		// search query is an actor
		for (int i = 0; i < input.size(); i++) {
			if (input.at(i).cast[movie::hash(query)] == query) {
				std::cout << input.at(i).title << std::endl;
				success = true;
			}
		}
		if (success == false) {
			std::cout << "Actor not found" << std::endl;
		}
	}
	else {
		// search query is a movieif 
		for (int i = 0; i < input.size(); i++) {
			if (input.at(i).title == query) {
				for (auto it = input.at(i).cast.begin(); it != input.at(i).cast.end(); it++)
					std::cout << it->second << std::endl;
				success = true;
			}
		}
		if (success == false) {
			std::cout << "Movie not found" << std::endl;
		}
	}
	return;
}

int main(int argc, char ** argv) {
	/* todo:
	 * parse input file (using methods from hw0)
	 * create appropriate data structure to contain data
	 * implemnent new methods to search data
	 */

	// read data from input file into data structure
	int count = 0;
	std::chrono::time_point<std::chrono::system_clock> listStart, listEnd, searchStart, searchEnd;
	std::chrono::duration<double> listTime, searchTime, totalTime;
	std::string line, cast;
	std::stringstream out;
	std::ifstream input(argv[1]);
	std::vector<movie> movieList;
	std::ifstream queryInput(argv[2]);
	std::vector<std::string> queryList;
	movie currMovie;

	listStart = std::chrono::system_clock::now();
	while (getline(input, line)) {
		out << line;
		while (getline(out, cast, '/')) {
			//std::cout << cast << std::endl;
			if (cast.find("(") != std::string::npos && cast.find(")") != std::string::npos) {
				currMovie.reset();
				currMovie.title = cast;
			}
			else { currMovie.addCast(cast); }		
		}
		movieList.push_back(currMovie);
		count++;
		out.clear();
	}
	movieList.erase(movieList.end() - 1);
	input.close();
	listEnd = std::chrono::system_clock::now();

	while (getline(queryInput, line)) {
		queryList.push_back(line);
	}
	queryInput.close();

	searchStart = std::chrono::system_clock::now();
	for (int i = 0; i < queryList.size(); i++) {
		std::cout << "Results for " << queryList.at(i) << ":" << std::endl;
		search(movieList, queryList.at(i));
		std::cout << std::endl;
	}
	searchEnd = std::chrono::system_clock::now();

	listTime = listEnd - listStart;
	searchTime = searchEnd - searchStart;
	totalTime = listTime + searchTime;

	std::cout << 
		"records: " << count <<
		" list: " << listTime.count() << 
		" search: " << searchTime.count() << 
		" total: " << totalTime.count() << 
	std::endl;
	return 0;
}
