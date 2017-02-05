/**
 * Created by JiaHong on 24/12/2016.
 */
package struct.heap;

import struct.DataStructure;

import java.util.ArrayList;
import java.util.Collections;

/**
 * Creates a heap data structure capable of inserting and deleting at O(log(n)),
 *  Heapify in O(nlog(n)) and searching in O(n), where n is the number of elements in
 *  the heap. This heap data structure supports O(1) retrieval of max item
 * TODO: Add a function that displays the heap tree structure graphically
 *
 * @param <T> Data type for items to be inserted into the heap
 */
public class Heap <T extends Comparable<? super T>> implements DataStructure<T> {
    ArrayList<T> array;
    static final int DEFAULT_ARRAY_SIZE = 10;
    // Maximum characters to display when printHeap is called
    // private static final int MAX_DISP_LENGTH = 10;

    public Heap(int size) {
        array = new ArrayList<>(size);
    }

    public Heap() {
        this(DEFAULT_ARRAY_SIZE);
    }

    public Heap(T[] arr) {
        array = new ArrayList<>(arr.length);
        Collections.addAll(array, arr);
        heapify();
    }

    /**
     * Inserts an item into the heap, and maintains the heap structure afterwards
     * @param item Item of type T to be inserted into the heap
     */
    public void add(T item) {
        array.add(item);
        sieveUp(array.size()-1);
    }

    /**
     * Returns true/false to indicate the presence of item of type T in the heap
     * @param item Item to be queried from the heap
     * @return true/false
     */
    public boolean search(T item) {
        return array.indexOf(item) != -1;
    }

    /**
     * Returns the first occurrence of item within the heap
     * @param item Item to be queried and returned from the heap
     * @return A reference to the first occurrence of the item in the heap
     */
    public T get(T item) {
        return array.get(array.indexOf(item));
    }

    /**
     * Returns true/false depending on the success of removing item T
     * @param item Item to be removed
     * @return True if successfully remove, false otherwise
     */
    public boolean remove(T item) {
        // index of the item about to be removed, used to calculate the point of sieve
        int index = array.indexOf(item);
        if (index != -1) {
            /* the "smallest" item is now in heap[index], and the item to be removed is
             * at the last index */
            swap(index, array.size()-1);
            array.remove(array.size()-1);
            /* since the item in heap[index] is currently the smallest item in the heap,
             * we will most definitely need to swap this 'parent' with its child recursively
             * to maintain the heap property */
            sieveDown(index);
        }
        return index != -1;
    }

    /**
     * Returns the item itself from the heap, and removes it
     * @param item Item to be removed and returned
     * @return the item T from the heap
     */
    public T pop(T item) {
        int index = array.indexOf(item);
        if (index != -1) {
            // we swap the item to be deleted with the last child
            swap(index, array.size()-1);
            T deletedItem = array.remove(array.size()-1);
            /* since the small child node is at heap[index], we need to maintain the heap
             * property again */
            sieveDown(index);
            return deletedItem;
        } else {
            return null;
        }
    }

    /**
     * Returns a reference to the root of the heap
     * @return reference to the root of the heap (be it min/max)
     */
    public T getRoot() {
        return array.get(0);
    }

    /** Returns a reference to the root of the heap, and also removes it from the heap
     * It's essentially calling heap.pop(0)
     * @return the head of the heap (be it min/max)
     */
    // TODO: prevent popping non-existing items ie:
    // while ((item = heap.popRoot()) != null) { ... } to work
    public T popRoot() {
        if (array.size() > 0)
            return this.pop(array.get(0));
        return null;
    }

    /**
     * O(nlogn) operation to re-heapify the whole array
     */
    public void heapify() {
        int lastIndex = array.size()-1;
        int lastParentIndex = (lastIndex-1)/2;
        for (int i = lastParentIndex; i >= 0; i--)
            sieveDown(i);
    }


    /**
     * Sieves upwards until parent is no longer smaller than the child node.
     * Note, this doesn't compare the other sibling node to node[childIndex] i.e.
     * node[childIndex+1]. Hence, it assumes a heap-ready state when sieving upwards
     *
     * @param childIndex current index of the child node that will be compared against the
     *                   parent node
     */
    void sieveUp(int childIndex) {
        int parent = (childIndex-1)/2;
        if (parent >= 0) {
            if (array.get(parent).compareTo(array.get(childIndex)) < 0) {
                swap(parent, childIndex);
                sieveUp(parent);
            }
        }
    }

    /**
     * Sieves downwards after each swap at parentIndex check.
     * If parent is smaller than either one of the child, it is swapped with
     * the larger one of them, and then recursively called downwards to maintain the
     * heap property
     *
     * @param parentIndex starting index for sieveDown to begin, all subsequent swaps with
     *                    child index will automatically call sieveDown(childIndex)
     */
    void sieveDown(int parentIndex) {
        int child = parentIndex * 2 + 1;
        if (child < array.size()) {
            /* if the second child exists and is larger than the first child,
             * we use the second */
            if ((child + 1) < array.size()
                    && array.get(child).compareTo(array.get(child + 1)) < 0)
                child++;

            if (array.get(parentIndex).compareTo(array.get(child)) < 0) {
                swap(parentIndex, child);
            }
            sieveDown(child);
        }
    }

    void swap(int indexOne, int indexTwo) {
        T temp = array.get(indexOne);
        array.set(indexOne, array.get(indexTwo));
        array.set(indexTwo, temp);
    }

}
