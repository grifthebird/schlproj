/*
 * Name: Jayden White
 * Email: jtwhite18@crimson.ua.edu
 * Course Section: Spring 25 CS 201
 * Homework #: 0
 * Instructions to Compile: g++ hw0.cpp
 * Instructions to Execute: ./a.out [input_file] 
 */

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <bits/stdc++.h> // required to use sort on remote server

class movie {
	// classs for holding movie attributes
	public:
		std::string title;
		int year;
		std::vector<std::string> cast;
		movie() {
			this->title = "tbd";
			this->year = -1;
		}
		void setTitle(std::string title);
		void setYear(int year);
		void addCast(std::string member);
		void getYear();
		void reset();
};

// class methods
void movie::setTitle(std::string title) {
	this->title = title;
	return;
}

void movie::setYear(int year) {
	this->year = year;
	return;
}

void movie::addCast(std::string member) {
	this->cast.push_back(member);
	return;
}

void movie::getYear() {
	std::string buffer;
	int begin, end;
	for (int i = 0; i < this->title.size(); i++) {
		if (this->title.at(i) == '(') { begin = i; }
		if (this->title.at(i) == ')') { end = i; }
	}
	buffer = this->title.substr(begin + 1, (end - begin) - 1);
	this->year = std::stoi(buffer);
	return;
}

void movie::reset() {
	this->title = "tbd";
	this->year = -1;
	this->cast.clear();
	return;
}

// comparators for std::sort
bool compTitle(movie a, movie b) {
	if (a.title == b.title) {
		return a.year < b.year;
	}
	return a.title < b.title;
}

bool compYear(movie a, movie b) {
	if (a.year == b.year) {
		return a.title < b.title;
	}
	return a.year < b.year;
}

// sort functions
void sortByTitle(std::vector<movie> & input) {
	std::sort(input.begin(), input.end(), compTitle);
	return;
}

void sortByDate(std::vector<movie> & input) {
	std::sort(input.begin(), input.end(), compYear);
	return;
}

// print output files
void printFile(std::ofstream & output, std::vector<movie> movies) {
	for (int i = 0; i < movies.size(); i++) {
		output << movies.at(i).title << "/";
		for (int j = 0; j < movies.at(i).cast.size(); j++) {
			if (j == movies.at(i).cast.size() - 1) {
				output << movies.at(i).cast.at(j);
			}
			else {
				output << movies.at(i).cast.at(j) << "/";
			}
		}
		output << std::endl;
	}
	return;
}

std::string getFilename(std::string input) {
	std::string filename = input;
	int extention;
	for (int i = 0; i < filename.size(); i++) {
		if (filename.at(i) == '.') {
			extention = i;
			break;
		}
	}
	filename = filename.substr(0, extention);
	return filename;
}

int main(int argc, char ** argv) {
	std::chrono::time_point<std::chrono::system_clock> listStart, listEnd, nameStart, nameEnd, yearStart, yearEnd;
	movie currMovie;
	std::string buffer;
	std::string curr;
	std::vector<movie> movieList;
	std::string filename = getFilename(argv[1]);
	std::ifstream in(argv[1]);
	std::stringstream out;

	listStart = std::chrono::system_clock::now();
	while (getline(in, buffer)) {
		out << buffer;
		while (getline(out, curr, '/')) {
			//std::cout << curr << std::endl;
			if (curr.find("(") != std::string::npos && curr.find(")") != std::string::npos) {
				currMovie.reset();
				currMovie.title = curr;
				currMovie.getYear();
			}
			else { currMovie.cast.push_back(curr); }

		}
		movieList.push_back(currMovie);
		out.clear();
	}
	movieList.erase(movieList.end() - 1);
	listEnd = std::chrono::system_clock::now();

	std::ofstream byName(filename + "ByName.txt");
	std::ofstream byYear(filename + "ByYear.txt");
	nameStart = std::chrono::system_clock::now();
	sortByTitle(movieList);
	printFile(byName, movieList);
	nameEnd = std::chrono::system_clock::now();
	yearStart = std::chrono::system_clock::now();
	sortByDate(movieList);
	printFile(byYear, movieList);
	yearEnd = std::chrono::system_clock::now();

	std::chrono::duration<double> listTime, nameTime, yearTime;
	listTime = listEnd - listStart;
	nameTime = nameEnd - nameStart;
	yearTime = yearEnd - yearStart;

	std::cout << "Time Taken:" << std::endl
		<< "List Creation, " << listTime.count() << "s" << std::endl
		<< "Sort by name, " << nameTime.count() << "s" << std::endl
		<< "Sort by year, " << yearTime.count() << "s" << std::endl
		<< "Total, " << listTime.count() + nameTime.count() + yearTime.count() << "s" << std::endl;

	byName.close();
	byYear.close();
	std::cout << "Total movies: " << movieList.size() << std::endl;
	return 0;

}
