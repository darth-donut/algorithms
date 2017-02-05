package struct.trie;

import org.junit.Test;
import struct.node.NotAChildNodeException;

import java.util.ArrayList;
import java.util.Collections;

import static org.junit.Assert.*;

public class TrieTest {
    public static ArrayList<String> strings = new ArrayList<>();
    private static boolean active;
    private static String[] strs = {
            "hello",
            "world!",
            "Random ",
            "Strings\n",
            "aksldjas",
            "Strings\n",
            "S",
            "A",
            "Str",
            "Str",
            "aksldja",
            "aks",
            "a",
            "Aa",
            "aA"
    };

    // TODO: Try tabbed strings (non-ascii?)

    @Test
    public void add() {
        Trie<Integer> t = new Trie<>(Trie.ASCII);
        Collections.shuffle(strings);
        populateTree(t, true);
    }

    @Test
    public void search() {
        Trie<Integer> t = new Trie<>(Trie.ASCII);
        for (String i: strings) {
            assertFalse(t.search(i));
        }
        populateTree(t, true);
        for (String i : strings) {
            assertTrue(t.search(i));
        }
    }

    @Test
    public void searchFrequencyCount() {
        Trie<Integer> t = new Trie<>(Trie.ASCII);
        for (String i : strings) {
            assertEquals(0, t.frequency(i));
        }

        populateTree(t, true);
        for (String i : strings) {
            assertEquals(Collections.frequency(strings, i), t.frequency(i));
        }
    }

    @Test
    public void remove() {
        Trie<Integer> t = new Trie<>(Trie.ASCII);
        for (String i : strings) {
            assertFalse(t.remove(i));
        }

        populateTree(t, true);
        for (String i : strings) {
            int freq = t.frequency(i);
            assertTrue(t.remove(i));
            assertEquals(freq -1, t.frequency(i));
        }

    }

    @Test
    public void pop() {
        Trie<Integer> t = new Trie<>(Trie.ASCII);
        for (String i  : strings)
            assertNull(t.pop(i));
        populateTree(t, true);
        for (String i : strings) {
            int freq = t.frequency(i);
            assertNotNull(t.pop(i));
            assertEquals(freq -1, t.frequency(i));
        }
    }

    private void populateTree(Trie<Integer> t, boolean shuffle) {
        if (!active) {
            Collections.addAll(strings, strs);
            active = true;
        }

        if (shuffle)
            Collections.shuffle(strings);

        for (String i : strings) {
            t.add(i, 1);
        }
    }

}
