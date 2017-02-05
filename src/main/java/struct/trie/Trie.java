/*
 * Created by jiahong on 7/01/17.
 * data_structures::struct.graph.bst
 */
package struct.trie;
import struct.MapDataStructure;

import java.nio.charset.UnsupportedCharsetException;

public class Trie<V> implements MapDataStructure<String, V> {

    /**
     * from space to ~ i.e. (('~'-' ')+1)+1
     */
    public static final int ASCII = ('~' - ' ' + 1 + 1);   // ' ' to ~ , and newline
    /**
     * All printable characters from the keyboard
     */
    public static final int KEY = 256;  // all kinds of printable stuff on your keyboard

    final int CHAR_SET;
    private Node<V> root;



    public Trie() throws UnsupportedCharsetException {
        this(ASCII);
    }

    public Trie(int char_set) throws UnsupportedCharsetException {
        this.CHAR_SET = char_set;
        root = new Node<>(new CharFreq(Character.MIN_VALUE, 0), char_set, null);
        switch (char_set) {
            case ASCII:
            case KEY:
            break;
            default:
                throw new UnsupportedCharsetException("Charset is not supported");

        }
    }

    /**
     * Adds item into the trie
     * @param item String:Item to be added
     */
    public void add(String item, V data) {
        if (item.length() == 0) {
            root.character.freq++;
            return;
        }
        Node<V> node = recursiveAdd(root.getChild(item.charAt(0)), item, 0, data);
        root.setChild(node);
    }


    /**
     * Searches for the item in the trie, returns true/false
     * @param item Item to be searched for
     * @return boolean
     */
    @Override
    public boolean search(String item) {
        if (item.length() == 0) return root.character.freq != 0;
        return recursiveSearch(root.getChild(item.charAt(0)), item, 0) != null;
    }

    /**
     * Returns the frequency of this item in the trie
     * @param item Item to be searched for
     * @return int
     */
    public int frequency(String item) {
        if (item.length() == 0) return root.character.freq;
        Node<V> tmp;
        if ((tmp = recursiveSearch(root.getChild(item.charAt(0)), item, 0)) != null) {
            return tmp.character.freq;
        } else {
            return 0;
        }
    }

    /**
     * If item exists in the trie, returns the data stored in the node (a reference)
     * @param item Item to be searched in the tree
     * @return Type T, else null if doesn't exist in the trie
     */
    @Override
    public V get(String item) {
        Node<V> tmp;
        if ((tmp = recursiveSearch(root.getChild(item.charAt(0)), item, 0)) != null)
            return tmp.data;
        return null;
    }

    /**
     * Removes item specified in the argument, and returns true or false depending whether
     * or not the item is found
     * @param item Item to be removed
     * @return true if found, false otherwise
     */
    @Override
    public boolean remove(String item) {
        return recursiveRemove(root.getChild(item.charAt(0)), item, 0) != null;
    }

    /**
     * Pops the item specified in the argument, null otherwise
     * @param item String to be popped from the trie
     * @return String (the same string that came from the parameter), null otherwise
     */
    @Override
    public V pop(String item) {
        return recursiveRemove(root.getChild(item.charAt(0)), item, 0);
    }

    private void trimUpwards(Node<V> root) {
        if (root != null && root.isLeaf() && root.character.freq == 0) {
            root.parent.childrenNodes[root.character.offsetStr(root.character.chr)] = null;
            trimUpwards(root.parent);
        }
    }


    private V recursiveRemove(Node<V> root, String key, int index) {
        if (root == null) return null;
        if (index == key.length()-1) {
            root.character.freq--;
            // if this node is a leaf node, erase it immediately
            if (root.character.freq == 0 && root.isLeaf()) {
                root.parent.childrenNodes[root.character.offsetStr(root.character.chr)] = null;
                trimUpwards(root.parent);
            }
            return root.data;
        } else {
            return recursiveRemove(root.getChild(key.charAt(index+1)), key, index+1);
        }
    }

    private Node<V> recursiveSearch(Node<V> root, String key, int index) {
        if (root == null) return null;
        if (index == key.length()-1)
            return root;
        return recursiveSearch(root.getChild(key.charAt(index+1)), key, index+1);

    }

    private Node<V> recursiveAdd(Node<V> root, String key, int index, V data) {
        if (root == null) {
            if (key.length()-1 == index) {
                return new Node<>(new CharFreq(key.charAt(index), 1), CHAR_SET, data);
            } else {
                Node<V> n = new Node<>(new CharFreq(key.charAt(index), 0), CHAR_SET, null);
                n.setChild(recursiveAdd(n.getChild(key.charAt(index+1)), key, index+1, data));
                return n;
            }
        } else {
            if (key.length()-1 == index) {
                root.data = data;
                root.character.freq++;
                return root;
            } else {
                Node<V> n = recursiveAdd(root.getChild(key.charAt(index+1)), key, index+1, data);
                root.setChild(n);
                return root;
            }
        }
    }
}
