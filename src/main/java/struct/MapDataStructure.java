/*
 * Created by jiahong on 17/01/17.
 * data_structures::PACKAGE_NAME
 */
package struct;

public interface MapDataStructure<K, V> {

    void add(K key, V data);

    boolean search(K key);

    V get(K key);

    boolean remove(K key);

    V pop(K item);

}
