package struct;

import struct.node.NotAChildNodeException;

/**
 * All data structures support addition(insertion), deletion, and searching
 * @param <T> Type of item stored in any data structure
 */
public interface DataStructure<T> {
    // inserting functionality
    void add(T item);

    // searching and getting functionality (presence and return)
    boolean search(T item);
    T get(T item);

    // removal capabilities (presence and return)
    boolean remove(T item) throws NotAChildNodeException;
    T pop(T item) throws NotAChildNodeException;
}
