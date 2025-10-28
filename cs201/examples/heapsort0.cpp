// g++ -std=c++11 -o heapsort heapsort.cpp
// ./heapsort

#include <iostream>
#include <vector>

void MaxHeapify(std::vector<int>& A, int i, int heap_size) {
    // 2
    int l = 2 * i + 1; // Left child
    int r = 2 * i + 2; // Right child
    int largest;

    if (l < heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;

    if (r < heap_size && A[r] > A[largest])
        largest = r;

    if (largest != i) {
        std::swap(A[i], A[largest]);
        MaxHeapify(A, largest, heap_size);
    }
}

void BuildMaxHeap(std::vector<int>& A) {
    int heap_size = A.size(); // 3
    for (int i = A.size() / 2 - 1; i >= 0; i--)
        MaxHeapify(A, i, heap_size);
}

void Heapsort(std::vector<int>& A) {
    BuildMaxHeap(A);  // 5
    int heap_size = A.size();
    for (int i = A.size() - 1; i >= 1; i--) {
        std::swap(A[0], A[i]);
        heap_size--;
        MaxHeapify(A, 0, heap_size);
    }
}

int main() {
    std::vector<int> A = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    
    std::cout << "Original array:\n";
    for (int num : A)
        std::cout << num << " ";
    std::cout << "\n";

    Heapsort(A);

    std::cout << "Sorted array:\n";
    for (int num : A)
        std::cout << num << " ";
    std::cout << "\n";

    return 0;
}

