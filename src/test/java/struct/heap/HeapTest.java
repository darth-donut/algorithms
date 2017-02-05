package struct.heap;

import org.junit.Test;
import static org.junit.Assert.*;
import java.util.Arrays;
import java.util.Collections;
import struct.heap.Heap;


public class HeapTest {
    String[] strings = {
            "Hello", "test", "Apple", "Lorem", "ipsum", "bacon", "Cheese"
    };

    @Test
    public void add() {
        Heap<String> heap = new Heap<>();
        for (int i = 0; i < 100000; i++)
            for (String str : strings)
                heap.add(str);
    }

    @Test
    public void search() {
        Heap<String> heap = new Heap<>();
        for (String str : strings)
            heap.add(str);
        String[] stringsCopy = strings.clone();

        // this is a max heap
        for (String str : stringsCopy)
            assertTrue(heap.search(str));
    }

    @Test
    public void get() {
        Heap<String> heap = new Heap<>();
        for (String str : strings)
            heap.add(str);
        String[] stringsCopy = strings.clone();

        // this is a max heap
        for (String str : stringsCopy)
            assertEquals(str, heap.get(str));

    }

    @Test
    public void remove() {
        Heap<String> heap = new Heap<>();
        for (String str : strings)
            heap.add(str);
        String[] stringsCopy = strings.clone();

        // this is a max heap
        for (String str : stringsCopy)
            assertTrue(heap.remove(str));

    }

    @Test
    public void pop() {
        Heap<String> heap = new Heap<>();
        for (String str : strings)
            heap.add(str);
        String[] stringsCopy = strings.clone();
        for (String str : stringsCopy)
            assertEquals(str, heap.pop(str));
    }

    @Test
    public void getRoot() {
        Heap<String> heap = new Heap<>();
        for (String str : strings)
            heap.add(str);
        String[] stringsCopy = strings.clone();
        Arrays.sort(stringsCopy, Collections.reverseOrder());

        // this is a max heap
        for (String str : stringsCopy) {
            assertEquals(str, heap.getRoot());
            heap.remove(str);
        }
    }

    @Test
    public void popRoot() {
        Heap<String> heap = new Heap<>();
        for (String str : strings)
            heap.add(str);
        String[] stringsCopy = strings.clone();
        Arrays.sort(stringsCopy, Collections.reverseOrder());

        // this is a max heap
        for (String str : stringsCopy) {
            assertEquals(str, heap.popRoot());
        }

    }

    @Test
    public void heapify() {

    }

    @Test
    public void sieveUp() {

    }

    @Test
    public void sieveDown() {

    }

    @Test
    public void swap() {

    }

}
