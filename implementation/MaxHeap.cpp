


#include "MaxHeap.h"
#include <algorithm> // For std::swap
#include <stdexcept> // For std::out_of_range
#include "Delivery.h" // Include Delivery.h for explicit instantiation

template <typename T>
void MaxHeap<T>::heapifyDown(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < heap.size() && heap[l] > heap[largest]) {
        largest = l;
    }

    if (r < heap.size() && heap[r] > heap[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        heapifyDown(largest);
    }
}

template <typename T>
void MaxHeap<T>::heapifyUp(int i) {
    while (i != 0 && heap[parent(i)] < heap[i]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

template <typename T>
void MaxHeap<T>::insert(T value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template <typename T>
T MaxHeap<T>::extractMax() {
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
T MaxHeap<T>::peekMax() {
    if (isEmpty()) {
        throw std::out_of_range("Heap is empty");
    }
    return heap[0];
}

template <typename T>
bool MaxHeap<T>::isEmpty() const {
    return heap.empty();
}

template <typename T>
int MaxHeap<T>::size() const {
    return heap.size();
}

// Explicit template instantiation for common types (e.g., int, double)
// template class MaxHeap<int>;
// template class MaxHeap<double>;







template class MaxHeap<Delivery>;


