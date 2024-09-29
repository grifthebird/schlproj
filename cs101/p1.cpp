#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/* current score: 96/100
 * status: "complete"
 */

string * nextinput(string args[]) { // read args for output
	for (int i = 0; i < 3; i++) { // clear previous inputs
		args[i] = "";
	}
	string userInput;
	string userbuffer;
	getline(cin, userInput);
	istringstream userstream(userInput);
	for (int d = 0; d < 3; d++) {
		getline(userstream, userbuffer, ' ');
		if (userbuffer[0] == '"') { // handling single arguments with multiple words
			userbuffer.erase(0, 1);
			if (userbuffer[userbuffer.size() - 1] == '"') { // if quoted string is one word
				userbuffer.erase(userbuffer.size() - 1);
				args[d] = userbuffer;
				continue;
			}
			args[d] += userbuffer;
			while (getline(userstream, userbuffer, ' ')) {
				if (userbuffer[userbuffer.size() - 1] == '"') {
					userbuffer.erase(userbuffer.size() - 1, 1);
					args[d] += " ";
					args[d] += userbuffer;
					break;
				}
				args[d] += userbuffer;
			}
			continue;
		}
		args[d] = userbuffer;
		//cout << miniargs[d] << endl;
	}
	return args;
}

int numcols(string file) {
	ifstream openFile(file);
	int i = 0;
	string buffer;
	getline(openFile, buffer);
	istringstream curr(buffer);
	string token;
	while (getline(curr, token, ',')) {
		i++;
	}
	openFile.close();
	return i;
}

void help() {
	cout << "command list" << endl;
	cout << "\tprint" << endl;
	cout << "\tcols" << endl;
	cout << "\tsearch *|col_name val" << endl;
	cout << "\tmin col_name" << endl;
	cout << "\tmax col_name" << endl;
	cout << "\tavg col_name" << endl;
	return;
}

int main(int argc, char ** argv) {
	// check cmd args
	if (argc != 3) {
		cout << "Usage: ./a database.csv #col_width" << endl;
		return -1;
	}

	// read data
	int numAttr = numcols(argv[1]);
	//cout << numAttr << endl;
	string dataTable[5001][numAttr];
	int i = 0;
	int j = 0;
	ifstream readFrom(argv[1]);
	if (!readFrom.is_open()) { // if file can't be opened
		cout << "Failed to open " << "\"" << argv[1] << "\"" << endl;
		return -1;
	}
	string buffer;
	while (getline(readFrom, buffer)) {
		istringstream curr(buffer);
		string token;
		while (getline(curr, token, ',')) {
			dataTable[i][j] = token;
			j++; // number of attributes / columns
		}
		j = 0;
		i++; // number of entries / rows
	}

	/*
	// output all formatted
	for (int a = 0; a < i; a++) { 
		for (int b = 0; b < numAttr; b++) {
			cout << setw(atoi(argv[2])) << right << dataTable[a][b];
		}
		cout << endl;
	}
	*/

	// read initial input
	cout << "Enter a command or \"help\" for a command list:" << endl;
	string miniargs[3];
	nextinput(miniargs);
	int desiredCol;
	bool failcheck = false;
	bool empty = true;
	bool filler = true;
	int q = 1;

	while (miniargs[0] != "quit") {
		for (int ii = 0; ii < 3; ii++) {
			//cout << miniargs[ii] << endl;
		}

		// implement project functionality
		//cout << "looping" << endl;
		if (miniargs[0] == "help") { // print commands
			help();
		}

		else if (miniargs[0] == "print") { // print all table values
			for (int a = 0; a < i; a++) { 
				for (int b = 0; b < numAttr; b++) {
				cout << setw(atoi(argv[2])) << right << dataTable[a][b];
				}
			cout << endl;
			}
		}

		else if (miniargs[0] == "cols") { // print headers of each column
			for (int c = 0; c < numAttr; c++) {
				cout << dataTable[0][c] << endl;
			}
		}

		else if (miniargs[0] == "search") { 
			desiredCol = 0;
			int findcount = 0;
			for (int e = 0; e < numAttr; e++) { // find column to check
				if (dataTable[0][e] == miniargs[1] || miniargs[1] == "*") {
					desiredCol = e;
					failcheck = true;
				}
			}

			if (failcheck) {
				for (int e = 0; e < numAttr; e++) { // print header row
					cout << setw(atoi(argv[2])) << right << dataTable[0][e];
				}
				cout << endl;
		
				for (int e = 1; e < i; e++) {
					if (dataTable[e][desiredCol] == miniargs[2] && miniargs[1] != "*") { // print entries that fit search
						for (int c = 0; c < numAttr; c++) {
							cout << setw(atoi(argv[2])) << right << dataTable[e][c];
							findcount++;
						}
					cout << endl;
					}
				}

				if (miniargs[1] == "*") { // wildcard search
					bool printed = false;
					for (int e = 1; e < i; e++) { // loop through array
						for (int f = 0; f < numAttr; f++) {
							if (dataTable[e][f] == miniargs[2] && !printed) {
								for (int g = 0; g < numAttr; g++) { // print entry
									cout << setw(atoi(argv[2])) << dataTable[e][g];
									findcount++;
								}
							cout << endl;
							printed = true;
							}
						}
					printed = false;
					}
				}
			
				if (findcount == 0) { 
					cout << "No results" << endl;
				}
			failcheck = false;
			}
			else {
				cout << "Invalid column \"" << miniargs[1] << "\"" << endl;
			}
		}

		else if (miniargs[0] == "min") { // find min value of col
			double min;
			for (int g = 0; g < numAttr; g++) { // find column to minimize
				if (dataTable[0][g] == miniargs[1]) {
					desiredCol = g;
					failcheck = true;
				}
			}
			

				for (int h = 1; h < i; h++) {
					if (dataTable[h][desiredCol] != "") {
						empty = false;
					}	
				}

			if (failcheck && !empty) {
				while (filler) {
					if (dataTable[q][desiredCol] != "") {
						min = stof(dataTable[q][desiredCol]);
						filler = false;
					}
					q++;
				}
				//cout << min << endl;
				for (int h = 1; h < i; h++) {
					if (dataTable[h][desiredCol] != "") {
						if (stof(dataTable[h][desiredCol]) < min) {
							min = stof(dataTable[h][desiredCol]);
						}
					}	
				}
				
				cout << "The min for col \"" << dataTable[0][desiredCol] << "\" = " << min << endl;
			}

			else if (failcheck && empty) {
				cout << "The min for col \"" << dataTable[0][desiredCol] << "\" = N/A" << endl;
			}

			else {
				cout << "Invalid column \"" << miniargs[1] << "\"" << endl;
			}
		failcheck = false;
		empty = true;
		filler = true;
		q = 1;
		}


		else if (miniargs[0] == "max") { // find min value of col
			double max;
			for (int g = 0; g < numAttr; g++) { // find column to minimize
				if (dataTable[0][g] == miniargs[1]) {
					desiredCol = g;
					failcheck = true;
				}
			}
			
			for (int h = 1; h < i; h++) {
				if (dataTable[h][desiredCol] != "") {
						empty = false;
				}
			}

			if (failcheck && !empty) {
				while (filler) {
					if (dataTable[q][desiredCol] != "") {
						max = stof(dataTable[q][desiredCol]);
						filler = false;
					}
					q++;
				}
				//cout << max << endl;
				for (int h = 1; h < i; h++) {
					if (dataTable[h][desiredCol] != "") {
						if (stof(dataTable[h][desiredCol]) > max) {
							max = stof(dataTable[h][desiredCol]);
						}
					}
				}	
				cout << "The max for col \"" << dataTable[0][desiredCol] << "\" = " << max << endl;
			}

			else if (failcheck && empty) {
				cout << "The max for col \"" << dataTable[0][desiredCol] << "\" = N/A" << endl;
			}

			else {
				cout << "Invalid column \"" << miniargs[1] << "\"" << endl;
			}
			failcheck = false;
			empty = true;
			q = 1;
			filler = true;
		}

		else if (miniargs[0] == "avg") {
			double total = 0;
			int count = 0;
			for (int l = 0; l < numAttr; l++) { // find column to average
				if (dataTable[0][l] == miniargs[1]) {
					desiredCol = l;
					failcheck = true;
				}
			}

			if (failcheck) {
				for (int m = 1; m < i; m++) { // add nums together
					if (dataTable[m][desiredCol] == "") { // catch empty entries
						//count++;
						continue;
					}
					total += stof(dataTable[m][desiredCol]);
					//cout << total << endl;
					count++;
				}

				if (count > 0) {
						cout << "The avg for col \"" << dataTable[0][desiredCol] << "\" = " << total / (double)count << endl;
				}
				else {
						cout << "The avg for col \"" << dataTable[0][desiredCol] << "\" = N/A" << endl;
				}
			}
			else {
					cout << "Invalid column \"" << miniargs[2] << "\"" << endl;
			}
		}

		else { // invalid command entered
			cout << "Invalid command" << endl;
		}

		nextinput(miniargs);
		//cout << endl;

	}

	/* old / extra code below, not part of final project code */

	// output all data
	/*
	for (int j = 0; j < i; j++) { 
		cout << setw(atoi(argv[2])) << right << 
	}
	*/

	/*
	string arr[128]; // 
	int i = 0;
	ifstream read;
	read.open(argv[1]);
	string line;
	while (getline(read, line)) {
		istringstream iss(line);
		string token;
		while (getline(iss, token, ',')) { // ',' separates inputs
			cout << token << endl;
			arr[i] = token;
			i++;
		}
	}
	for (int i = 0; i < 16; i++) {
		if (i % 4 == 3) {
			cout << arr[i] << endl;
		}
	}
	read.close();
	*/
	return 0;
}
