// g++ -std=c++11 -o heapsort heapsort.cpp
// ./heapsort

#include <iostream>
#include <vector>

int Left(int i){
    return 2*i;
}

int Right(int i){
    return 2*i+1;
}

void maxHeapify(std::vector<int>& A, int i, int heap_size){
    int l = Left(i);
    int r = Right(i);
    int largest = i;
    // if left child is larger than root.
    if(l <= heap_size && A[l] > A[i]){
        largest = l;
    }
    // If right child is larger than largest so far.
    if(r <= heap_size && A[r] > A[largest])
        largest = r;

    //if largest is not root
    if(largest != i){
        // swap the root with the largest item
        std::swap(A[i], A[largest]);
        maxHeapify(A, largest, heap_size);
    }
}

void buildMaxHeap(std::vector<int>& A){
    int heap_size = A.size() - 1;
    for(int i = heap_size/2; i>=1; i--){
        maxHeapify(A, i, heap_size);
    }
}

void heapsort(std::vector<int>& A){
    buildMaxHeap(A);
    int heap_size = A.size()-1;
    for(int i = heap_size; i >= 2; i--){
        std::swap(A[1], A[i]);
        heap_size--;
        maxHeapify(A, 1, heap_size);
    }
}

void printArray(const std::vector<int>& A){
    for(int i = 1; i < A.size(); i++){
        std::cout << A[i] << " ";
    }
    std::cout << std:: endl;
}

int main(){

    std::vector<int> A = {0, 12, 11, 13, 5, 6, 7};

    std::cout << "Original Array: ";
    printArray(A);

    heapsort(A);

    std::cout << "Sorted Array: ";
    printArray(A);

    return 0;
}
