#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>

using namespace std;
// import quick and merge from zybooks
// quick for ints, merge for strings
// todo: adapt to work with project
int Partition(string array[], int i, int k) {
   int l;
   int h;
   int midpoint;
   string pivot;
   string temp;
   bool done;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = array[midpoint];
   
   done = false;
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while (array[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < array[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = array[l];
         array[l] = array[h];
         array[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort(string array[], int i, int k) {
   int j;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(array, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort(array, i, j);
   Quicksort(array, j + 1, k);
}

void Merge(string array[], int i, int j, int k) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   string* mergedStrings = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedStrings = new string[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (stoi(array[leftPos]) < stoi(array[rightPos])) {
         mergedStrings[mergePos] = array[leftPos];
         ++leftPos;
      }
      else {
         mergedStrings[mergePos] = array[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedStrings[mergePos] = array[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedStrings[mergePos] = array[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      array[i + mergePos] = mergedStrings[mergePos];
   }
   delete[] mergedStrings;
}

void MergeSort(string array[], int i, int k) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(array, i, j);
      MergeSort(array, j + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(array, i, j, k);
   }
}

int main(int argc, char ** argv) {
	enum sortType {Merge, Quick};
	int sort;
	ifstream input1, input2;
	string Matches[40000]; // memory of all printed strings
	string Duplicates[40000];
	string arrayLeft[40000], arrayRight[40000];
	string buffer;
	int count1 = 0;
	int count2 = 0;
	int printcount = 0;
	int dupcount = 0;
	bool unique = true;
	// get sort type from cmd
	if (0 == strcmp(argv[1], "i")) { // integer sorting
		sort = Merge;
		//cout << "merge selected" << endl;
	}
	else if (0 == strcmp(argv[1], "s")) { // string sorting
		sort = Quick;
		//cout << "quick selected" << endl;
	}
	else {
		cout << "invalid input for sorting" << endl;
	}

	input1.open(argv[2]);
	input2.open(argv[3]);
	if (!input1.is_open() || !input2.is_open()) {
		cout << "unable to open one or more input files" << endl;
		return -1;
	}

	// todo: call merge or quick with proper params to sort data
	while (input1 >> buffer) {
		//cout << buffer << endl;
		arrayLeft[count1] = buffer;
		count1++;
	}
	
	if (sort) {
		Quicksort(arrayLeft, 0, count1 - 1);
	}
	else {
		MergeSort(arrayLeft, 0, count1 - 1);
	}

	for (int i = 0 ; i < count1; i++) {
		//cout << i << ": " << arrayLeft[i] << endl;
	}
	//cout << endl;
	
	while (input2 >> buffer) {
		//cout << buffer << endl;
		arrayRight[count2] = buffer;
		count2++;
	}
	
	if (sort) {
		Quicksort(arrayRight, 0, count2 - 1);
	}
	else {
		MergeSort(arrayRight, 0, count2 - 1);
	}

	for (int i = 0; i < count2; i++) {
		//cout << i << ": " << arrayRight[i] << endl;
	}
	//cout << endl;
	
	// find and print union of arrays
	for (int i = 0; i < count1; i++) {
		for (int j = 0; j < count2; j++) {
			if (arrayLeft[i] == arrayRight[j]) {
				Matches[printcount] = arrayLeft[i];
				//cout << printcount << ": " << Matches[printcount] << endl;
				printcount++;
			}
		}
	}

	//cout << printcount << endl;
	for (int i = 0; i < printcount; i++) {
		if (Matches[i] == "") { continue; }
		for (int j = 0; j < dupcount; j++) {
			if (Matches[i] == Duplicates[j]) {
				unique = false;
			}
		}
		if (unique) {
			cout << Matches[i] << endl;
		}
		Duplicates[i] = Matches[i];
		dupcount++;
		unique = true;
	}

	input1.close();
	input2.close();
	return 0;
}
