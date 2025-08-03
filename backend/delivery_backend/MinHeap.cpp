#include "MinHeap.h"
#include <algorithm> // For std::swap
#include <stdexcept> // For std::out_of_range
#include "Delivery.h" // Include Delivery.h for explicit instantiation

template <typename T>
void MinHeap<T>::heapifyDown(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap.size() && heap[l] < heap[smallest]) {
        smallest = l;
    }

    if (r < heap.size() && heap[r] < heap[smallest]) {
        smallest = r;
    }

    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

template <typename T>
void MinHeap<T>::heapifyUp(int i) {
    while (i != 0 && heap[parent(i)] > heap[i]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

template <typename T>
void MinHeap<T>::insert(T value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template <typename T>
T MinHeap<T>::extractMin() {
    if (isEmpty()) {
        throw std::out_of_range("Heap is empty");
    }
    T root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return root;
}

template <typename T>
T MinHeap<T>::peekMin() {
    if (isEmpty()) {
        throw std::out_of_range("Heap is empty");
    }
    return heap[0];
}

template <typename T>
bool MinHeap<T>::isEmpty() const {
    return heap.empty();
}

template <typename T>
int MinHeap<T>::size() const {
    return heap.size();
}

// Explicit template instantiation for Delivery type
template class MinHeap<Delivery>;


