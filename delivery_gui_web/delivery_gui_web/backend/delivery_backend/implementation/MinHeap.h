


#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <iostream>

// Templated MinHeap class
template <typename T>
class MinHeap {
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
    MinHeap() {}

    // Insert a new element into the heap
    void insert(T value);

    // Extract the minimum element from the heap
    T extractMin();

    // Get the minimum element without removing it
    T peekMin();

    // Check if the heap is empty
    bool isEmpty() const;

    // Get the size of the heap
    int size() const;
};

#endif // MINHEAP_H


