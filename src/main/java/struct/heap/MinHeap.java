/**
 * Created by JiaHong on 24/12/2016.
 */
package struct.heap;

/**
 * Creates a min-heap instead of a max-heap.
 * @see 'Heap.java'
 * @param <T> Type of item to be inserted into MinHeap
 */
public class MinHeap <T extends Comparable<? super T>> extends Heap<T> {

    public MinHeap(int size) {
        super(size);
    }

    public MinHeap() {
        this(DEFAULT_ARRAY_SIZE);
    }

    @Override
    void sieveDown(int parentIndex) {
        int child = parentIndex * 2 + 1;
        if (child < array.size()) {
            /* if the second child exists and is larger than the first child,
             * we use the second */
            if ((child + 1) < array.size()
                    && array.get(child).compareTo(array.get(child + 1)) > 0)
                child++;

            if (array.get(parentIndex).compareTo(array.get(child)) > 0) {
                swap(parentIndex, child);
            }
            sieveDown(child);
        }
    }

    @Override
    void sieveUp(int childIndex) {
        int parent = (childIndex-1)/2;
        if (parent >= 0) {
            if (array.get(parent).compareTo(array.get(childIndex)) > 0) {
                swap(parent, childIndex);
                sieveUp(parent);
            }
        }
    }
}
