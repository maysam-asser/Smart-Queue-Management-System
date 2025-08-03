


#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <iostream>

// Templated MaxHeap class
template <typename T>
class MaxHeap {
private:
    std::vector<T> heap;

    // Helper functions to get parent, left child, and right child indices
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    // Heapify down to maintain the heap property from a given node
    void heapifyDown(int i);

    // Heapify up to maintain the heap property from a given node
    void heapifyUp(int i);

public:
    const std::vector<T>& getHeap() const { return heap; }
    // Constructor
    MaxHeap() {}

    // Insert a new element into the heap
    void insert(T value);

    // Extract the maximum element from the heap
    T extractMax();

    // Get the maximum element without removing it
    T peekMax();

    // Check if the heap is empty
    bool isEmpty() const;

    // Get the size of the heap
    int size() const;
};

#endif // MAXHEAP_H


