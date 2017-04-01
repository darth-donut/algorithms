#ifndef _DATA_STRUCTURE_HEAP_H_
#define _DATA_STRUCTURE_HEAP_H_

#include <vector>
#include <algorithm>

template<class T>
class Heap {
public:
    typedef typename std::vector<T>::size_type size_type;
    typedef char heap_type;
    static constexpr heap_type MIN = 1;
    static constexpr heap_type MAX = 2;
    explicit Heap(heap_type type = MAX) : type(type) { }
    Heap(std::vector<T>& array, heap_type type = MAX) 
        : heap(array), type(type) { 
        heapify();
    }
    Heap<T>& add(const T&);
    T remove(const T&);
    const T *get(const T&) const;
    T *get(const T&);
    const T &root() const;
    T &root();
    const size_type size() const { return heap.size(); }

private:
    std::vector<T> heap;
    heap_type type;
    void heapify();
    void sieve_up(size_type child);
    void sieve_down(size_type parent);
    bool require_swap(size_type, size_type) const;
};

template<class T>
inline T&
Heap<T>::root() {
    return heap[0];
}

template<class T>
inline const T&
Heap<T>::root() const {
    return heap[0];
}

template<class T>
Heap<T>&
Heap<T>::add(const T& data) {
    // add to last element (leaf node)
    heap.push_back(data);
    // might invalidate the heap property, need to sieve upwards
    sieve_up(heap.size()-1);
    return *this;
}

template<class T>
T
Heap<T>::remove(const T &key) {
    auto it = std::find(heap.cbegin(), heap.cend(), key);
    if (it == heap.cend()) return nullptr;
    size_type index = static_cast<size_type>(std::distance(heap.cbegin(), it));
    std::swap(heap[index], heap[heap.size()-1]);
    T data = heap[heap.size()-1];
    heap.pop_back();
    sieve_down(index);
    return data;
}

template<class T>
const T*
Heap<T>::get(const T& key) const {
    auto it = std::find(heap.cbegin(), heap.cend(), key);
    if (it == heap.cend()) return nullptr;
    size_type index = static_cast<size_type>(std::distance(heap.cbegin(), it));
    return &heap[index];
}

template<class T>
T*
Heap<T>::get(const T& key) {
    auto it = std::find(heap.cbegin(), heap.cend(), key);
    if (it == heap.cend()) return nullptr;
    size_type index = static_cast<size_type>(std::distance(heap.cbegin(), it));
    return &heap[index];
}

template<class T>
void
Heap<T>::heapify() {
    if (heap.size() == 1) return;
    // loop invariant: parent is set to the last possible parent in the heap
    for (auto parent = heap.size()/2-1; parent >= 0; --parent) {
        sieve_down(parent);
        if (parent == 0) break; // --parent when parent is 0 with unsigned is disasterous
    }
}

template<class T>
void
Heap<T>::sieve_up(size_type child) {
    if (child == 0) return;
    size_type parent = (child-1)/2;
    if (require_swap(parent, child)) {
        std::swap(heap[parent], heap[child]);
        sieve_up(parent);
    }
}

template<class T>
void
Heap<T>::sieve_down(size_type parent) {
    // get the first child's index
    size_type child = parent*2+1;
    // make sure the child is within limits
    if (child < heap.size()) {
        // if it is, compare against its sibling and find the larger/smaller one before
        // comparing to parent
        if (child + 1 < heap.size() && require_swap(child, child+1)) {
            ++child;
        }
        if (require_swap(parent, child)) {
            std::swap(heap[child], heap[parent]);
            sieve_down(child);
        }
    }
}

template<class T>
bool
Heap<T>::require_swap(size_type index1, size_type index2) const {
    if (type == MIN)
        return heap[index2] < heap[index1];
    return !(heap[index2] <= heap[index1]);
}

#endif
