


#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "MinHeap.h"
#include "MaxHeap.h"
#include <stdexcept>

// Templated PriorityQueue class
// This class can be configured to act as a min-priority queue or a max-priority queue
// based on the HeapType enum.
enum HeapType {
    MIN_HEAP,
    MAX_HEAP
};

template <typename T>
class PriorityQueue {
public:
    const std::vector<T>& getInternalData() const {
        return (type == MIN_HEAP) ? minHeap.getHeap() : maxHeap.getHeap();
    }
private:
    MinHeap<T> minHeap;
    MaxHeap<T> maxHeap;
    HeapType type;

public:
    // Constructor: specify whether it's a min-priority queue or max-priority queue
    PriorityQueue(HeapType heapType) : type(heapType) {}

    // Insert an element into the priority queue
    void enqueue(T value) {
        if (type == MIN_HEAP) {
            minHeap.insert(value);
        } else {
            maxHeap.insert(value);
        }
    }

    // Remove and return the highest priority element
    T dequeue() {
        if (type == MIN_HEAP) {
            return minHeap.extractMin();
        } else {
            return maxHeap.extractMax();
        }
    }

    // Return the highest priority element without removing it
    T peek() {
        if (type == MIN_HEAP) {
            return minHeap.peekMin();
        } else {
            return maxHeap.peekMax();
        }
    }

    // Check if the priority queue is empty
    bool isEmpty() const {
        if (type == MIN_HEAP) {
            return minHeap.isEmpty();
        } else {
            return maxHeap.isEmpty();
        }
    }

    // Get the size of the priority queue
    int size() const {
        if (type == MIN_HEAP) {
            return minHeap.size();
        } else {
            return maxHeap.size();
        }
    }
};

#endif // PRIORITY_QUEUE_H


