/* complete
 * grade: 100/100
 */

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Store the return of this function as an unsigned long!
unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash;
}

class HashItem { // object containing each string and check for occupancy
	public:
		HashItem() {
			this->HashString = "";
			this->taken = false;
		}

		HashItem(string input, bool occupancy) {
			this->HashString = input;
			this->taken = occupancy;
		}

		string HashString;
		bool taken;
		vector<int> lineNumbers;
		HashItem operator=(HashItem rhs) {
			this->HashString = rhs.HashString;
			this->taken = rhs.taken;
			return *this;
		}
};

class HashTable { // class object to store words
	private:
		vector<HashItem> HashTableArray;
		int size;
		string hashMeth;
		int a;
		int total;
		int unique;
		int collision;
	public:
		HashTable() {
			this->size = 1;
			this->hashMeth = "dummy";
			this->a = 1;
			this->HashTableArray.resize(1);
			total = 0;
			unique = 0;
			collision = 0;
		}

		HashTable(int sizeA, string hashMethA, int h2A = 1) {
			this->size = sizeA;
			this->hashMeth = hashMethA;
			this->a = h2A;
			this->HashTableArray.resize(this->size);
			total = 0;
			unique = 0;
			collision = 0;
		}

		void scan();
		void index(int index);
		void get();
		void seth2A(int a);
		int insert(HashItem obj, int line); // insert item into table with proper probing method
		int findInternal(string obj); // find item from table
		int findExternal(string obj);
		friend bool ReadnInsert(ifstream & inputStream, HashTable & inputTable, string hashMeth);
};

void HashTable::scan() {
	/*
	for (int i = 0; i < this->HashTableArray.size(); i++) {
		cout << i << ": " << this->HashTableArray.at(i).HashString << " [";
		for (int j = 0; j < this->HashTableArray.at(i).lineNumbers.size(); j++) {
			cout << this->HashTableArray.at(i).lineNumbers.at(j) << " ";
		}
		cout << "]" << endl;
	}
	*/
	cout << "The number of words found in the file was " << this->total << endl;
	cout << "The number of unique words found in the file was " << this->unique << endl;
	cout << "The number of collisions was " << this->collision << endl;
	cout << endl;
	return;
}

void HashTable::index(int index) {
	cout << this->HashTableArray.size() << endl;
	cout << index << ": ";
	cout << this->HashTableArray.at(index).HashString << endl;
	cout << this->HashTableArray.at(index).taken << endl;
	return;
}

void HashTable::get() {
	cout << "Hash table size: " << this->size << endl;
	cout << "Hashing method: " << this->hashMeth << endl;
	cout << "Hash multiple (used if \"dh\"): ";
	if (this->hashMeth == "dh") {
		cout << this->a << endl;
	}
	else {
		cout << "null" << endl;
	}
	return;
}

void HashTable::seth2A(int a) {
	this->a = a;
	return;
}

int HashTable::insert(HashItem obj, int line) {
	//cout << "soup" << endl;
	int early = this->findInternal(obj.HashString);
	if (early != -1) {
		this->HashTableArray.at(early).lineNumbers.push_back(line);
		return 2;
	}
	//cout << "banana" << endl;
	bool insert = false;
	int iterations = 0;
	int offset = 0;
	int h1 = djb2(obj.HashString) % this->size;
	int h2 = this->a - (djb2(obj.HashString) % this->a);
	if (this->hashMeth == "lp") { // linear probing
		do {
			if (this->HashTableArray.at((h1 + offset) % this->size).taken == true) { // if index is already taken
				//cout << "failed to insert " << obj.HashString << " at " << (h1 + offset) % this->size << endl;
				this->collision++;
				//cout << this->collision << endl;
				iterations++;
				offset++;
			}
			else { // insert 
				this->HashTableArray.at((h1 + offset) % this->size) = obj;
				this->HashTableArray.at((h1 + offset) % this->size).lineNumbers.push_back(line);
				//cout << "inserted " << obj.HashString << " at " << (h1 + offset) % this->size << endl;
				insert = true;
				return 1;
			}
		} while (insert == false && iterations < this->HashTableArray.size());
	}
	else if (this->hashMeth == "qp") { // quadratic probing
		do {
			if (this->HashTableArray.at((h1 + (offset * offset)) % this->size).taken == true) { // if index is already taken
				//cout << "failed to insert " << obj.HashString << " at " << (h1 + (offset * offset)) % this->size << endl;
				this->collision++;
				//cout << this->collision << endl;
				iterations++;
				offset++;
			}
			else { // insert 
				this->HashTableArray.at((h1 + (offset * offset)) % this->size) = obj;
				this->HashTableArray.at((h1 + (offset * offset)) % this->size).lineNumbers.push_back(line);
				//cout << "inserted " << obj.HashString << " at " << (h1 + (offset * offset)) % this->size << endl;
				insert = true;
				return 1;
			}
		} while (insert == false && iterations < this->HashTableArray.size());
	}
	else if (this->hashMeth == "dh") { // double hashing
		do {
			if (this->HashTableArray.at((h1 + (h2 * offset)) % this->size).taken == true) { // if index is already taken
				//cout << "failed to insert " << obj.HashString << " at " << (h1 + (h2 * offset)) % this->size << endl;
				this->collision++;
				//cout << this->collision << endl;
				iterations++;
				offset++;
			}
			else { // insert 
				this->HashTableArray.at((h1 + (h2 * offset)) % this->size) = obj;
				this->HashTableArray.at((h1 + (h2 * offset)) % this->size).lineNumbers.push_back(line);
				//cout << "inserted " << obj.HashString << " at " << (h1 + (h2 * offset)) % this->size << endl;
				insert = true;
				return 1;
			}
		} while (insert == false && iterations < this->HashTableArray.size());
	}
	else {
		cout << "????" << endl;
	}
	return 0;
}

int HashTable::findInternal(string obj) {
	int h1 = djb2(obj) % this->size;
	int h2 = this->a - (djb2(obj) % this->a);
	int offset = 0;
	int iterations = 0;
	int collisions = 0;
	//cout << "fans" << endl;
	while (iterations < this->HashTableArray.size()) {
		if (this->hashMeth == "lp") {
			if (this->HashTableArray.at((h1 + offset) % this->size).HashString == obj) {
				this->collision = this->collision + collisions;
				return (h1 + offset) % this->size;
			}
			else if (this->HashTableArray.at((h1 + offset) % this->size).HashString == "") {
				//cout << obj << ": hit empty index" << endl;
				return -1;
			}
			else {
				collisions++;
				offset++;
				iterations++;
			}
		}
		else if (this->hashMeth == "qp") {
			if (this->HashTableArray.at((h1 + (offset * offset)) % this->size).HashString == obj) {
				this->collision = this->collision + collisions;
				return (h1 + (offset * offset)) % this->size;
			}
			else if (this->HashTableArray.at((h1 + (offset * offset)) % this->size).HashString == "") {
				//cout << obj << ": hit empty index" << endl;
				return -1;
			}
			else {
				collisions++;
				offset++;
				iterations++;
			}
		}
		else if (this->hashMeth == "dh") {
			if (this->HashTableArray.at((h1 + (h2 * offset)) % this->size).HashString == obj) {
				this->collision = this->collision + collisions;
				return (h1 + (h2 * offset)) % this->size;
			}
			else if (this->HashTableArray.at((h1 + (h2 * offset)) % this->size).HashString == "") {
				//cout << obj << ": hit empty index" << endl;
				return -1;
			}
			else {
				collisions++;
				offset++;
				iterations++;
			}
		}
	}
	//cout << obj << ": iterated through array" << endl;
	return -1;
}

int HashTable::findExternal(string obj) {
	int h1 = djb2(obj) % this->size;
	int h2 = this->a - (djb2(obj) % this->a);
	int offset = 0;
	int iterations = 0;
	int collisions = 0;
	int buffer = 0;
	//cout << "fans" << endl;
	while (iterations < this->HashTableArray.size()) {
		if (this->hashMeth == "lp") {
			if (this->HashTableArray.at((h1 + offset) % this->size).HashString == obj) {
				cout << obj << " appears on lines [";
				for (int i = 0; i < this->HashTableArray.at((h1 + offset) % this->size).lineNumbers.size(); i++) {
					if (this->HashTableArray.at((h1 + offset) % this->size).lineNumbers.at(i) == buffer) {
						continue;
					}
					cout << this->HashTableArray.at((h1 + offset) % this->size).lineNumbers.at(i);
					if (i + 1 != this->HashTableArray.at((h1 + offset) % this->size).lineNumbers.size()) {
						cout << ",";
					}
					buffer = this->HashTableArray.at((h1 + offset) % this->size).lineNumbers.at(i);
				}
				cout << "]" << endl;
				cout << "The search had " << collisions << " collisions" << endl;
				return 0;
			}
			else if (this->HashTableArray.at((h1 + offset) % this->size).HashString == "") {
				cout << obj << " appears on lines []" << endl;
				cout << "The search had " << collisions << " collisions" << endl;
				return -1;
			}
			else {
				collisions++;
				offset++;
				iterations++;
			}
		}
		else if (this->hashMeth == "qp") {
			if (this->HashTableArray.at((h1 + (offset * offset)) % this->size).HashString == obj) {
				cout << obj << " appears on lines [";
				for (int i = 0; i < this->HashTableArray.at((h1 + (offset * offset)) % this->size).lineNumbers.size(); i++) {
					if (this->HashTableArray.at((h1 + (offset * offset)) % this->size).lineNumbers.at(i) == buffer) {
						continue;
					}
					cout << this->HashTableArray.at((h1 + (offset * offset)) % this->size).lineNumbers.at(i);
					if (i + 1 != this->HashTableArray.at((h1 + (offset * offset)) % this->size).lineNumbers.size()) {
						cout << ",";
					}
					buffer = this->HashTableArray.at((h1 + (offset * offset)) % this->size).lineNumbers.at(i);
				}
				cout << "]" << endl;
				cout << "The search had " << collisions << " collisions" << endl;
				return 0;
			}
			else if (this->HashTableArray.at((h1 + (offset * offset)) % this->size).HashString == "") {
				cout << obj << " appears on lines []" << endl;
				cout << "The search had " << collisions << " collisions" << endl;
				return -1;
			}
			else {
				collisions++;
				offset++;
				iterations++;
			}
		}
		else if (this->hashMeth == "dh") {
			if (this->HashTableArray.at((h1 + (h2 * offset)) % this->size).HashString == obj) {
				cout << obj << " appears on lines [";
				for (int i = 0; i < this->HashTableArray.at((h1 + (h2 * offset)) % this->size).lineNumbers.size(); i++) {
					if (this->HashTableArray.at((h1 + (h2 * offset)) % this->size).lineNumbers.at(i) == buffer) {
						continue;
					}
					cout << this->HashTableArray.at((h1 + (h2 * offset)) % this->size).lineNumbers.at(i);
					if (i + 1 != this->HashTableArray.at((h1 + (h2 * offset)) % this->size).lineNumbers.size()) {
						cout << ",";
					}
					buffer = this->HashTableArray.at((h1 + (h2 * offset)) % this->size).lineNumbers.at(i);
				}
				cout << "]" << endl;
				cout << "The search had " << collisions << " collisions" << endl;
				return 0;
			}
			else if (this->HashTableArray.at((h1 + (h2 * offset)) % this->size).HashString == "") {
				cout << obj << " appears on lines []" << endl;
				cout << "The search had " << collisions << " collisions" << endl;
				return -1;
			}
			else {
				collisions++;
				offset++;
				iterations++;
			}
		}
	}
	//cout << obj << ": iterated through array" << endl;
	return -1;
}
bool ReadnInsert(ifstream & inputStream, HashTable & inputTable, string hashMeth) {
	/* this function will probably end up doing a multitude of things.
	 * for now, the main goals are to 1: properly parse the inputs from
	 * the input stream, 2: take the inputs, then hash and insert into
	 * table, *3: maybe also keep up with the number of unique words
	 * inserted somehow as well, but first two thing are manditory*/
	
	// parse input
	int status;
	int lineNumber = 1;
	HashItem tmp;
	string buffer;
	string input;
	int first = 0; 
	int last = 0;
	while (getline(inputStream, buffer)) {
		if (buffer == "") {
			continue;
		}
		//cout << "line " << lineNumber << ": " << buffer << endl;
		first = 0;
		last = 0;
		//cout << buffer.length() << endl;
		while (first < buffer.length() && last < buffer.length()) {
			while (first < buffer.length() && !(isalpha(buffer.at(first)))) { // find start of valid input
				first++;
			}
			last = first;
			while (last + 1 < buffer.length() && isalpha(buffer.at(last + 1))) { // find end of valid input
				//cout << last << endl;
				last++;
			}
			input = buffer.substr(first, (last - first) + 1);
			for (int i = 0; i < input.length(); i++) {
				input.at(i) = tolower(input.at(i));
			}
			if (input == "") break;
			//cout << '(' << first << " , " << last << "): " << input << endl;
			tmp.HashString = input;
			tmp.taken = true;
			//cout << "egg" << endl;
			status = inputTable.insert(tmp, lineNumber);
			if (status == 0) {
				cout << "array is full" << endl;
				return false;
			}
			else if (status == 1) {
				inputTable.unique++;
			}
			inputTable.total++;
			first = last + 1;
		}
		lineNumber++;
	}
	return true;
}

int main(int argc,char ** argv) {
	/* todo:
	 * implement find function
	 * check that insert function works
	 * start on output section
	 */
	// create table
	
	HashTable store(atoi(argv[3]), argv[4]);
	if (argc == 6) {
		store.seth2A(atoi(argv[5]));
	}

	//store.index(85);
	//store.get();

	//read inputs
	//bool read;
	ifstream input;
	ifstream cmp;
	string search;
	string next;
	input.open(argv[1]);
	cmp.open(argv[2]);
	ReadnInsert(input, store, argv[4]);
	store.scan();
	/*
	if (read) {
		cout << "all good" << endl;
	}
	*/
	cmp >> next;
	while (!cmp.eof()) {
		search = next;
		store.findExternal(search);
		cmp >> next;
		if (!cmp.eof()) {
			cout << endl;
		}
	}

	input.close();
	cmp.close();
	return 0;
}
