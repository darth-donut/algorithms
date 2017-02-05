package struct.graph.bst;

import struct.node.BiNode;

import java.lang.reflect.Field;
import java.util.Random;

import org.junit.Test;
import static org.junit.Assert.*;

public class BinarySearchTreeTest {

    private BinarySearchTree<String> tree;
    private boolean activeTree;
    private boolean filledTree;
    private final static int SEED = 12130;

    private String[] dummyStrings = {
        "Hello world!",
        "Trandom Strings traversing trees",
        "Moby dick",
        "Alice in wonderland",
        "Typist speed",
        "Again!",
        "No repeats allowed",
        "apples",
        "Randomstrings"
    };


    private void initializeTree() {
        tree = new BinarySearchTree<>();
        activeTree = true;
    }

    @Test
    public void add() {
        if (!activeTree) initializeTree();
        for (String str : dummyStrings)
            tree.add(str);
        filledTree = true;
    }

    @Test
    public void search() {
        if (!filledTree) add();

        // testing for presence (of addition)
        for (String str : dummyStrings)
            assertTrue(tree.search(str));

        // Testing for case-sensitivity
        for (String str: dummyStrings) {
            if (str.equals("apples"))
                assertTrue(tree.search(str.toLowerCase()));
            else
                assertFalse(tree.search(str.toLowerCase()));
        }
    }

    @Test
    public void get() {
        if (!activeTree) add();
        for (String str : dummyStrings)
            assertEquals(str, tree.get(str));
    }

    @Test
    @SuppressWarnings("unchecked")
    public void pop() {
        BinarySearchTree<String> bst = new BinarySearchTree<>();
        for (String str : fisherYatesShuffle(dummyStrings, SEED))
            bst.add(str);
        Field  rootNode;
        try {
            rootNode = BinarySearchTree.class.getDeclaredField("rootNode");
            rootNode.setAccessible(true);
            BiNode<String> root = (BiNode<String>) rootNode.get(bst);

            for (String str : fisherYatesShuffle(dummyStrings, SEED)) {
                assertEquals(str, bst.pop(str));
                root = (BiNode<String>) rootNode.get(bst);
                traverse(root);
                assertNull(bst.pop(str));
            }

        } catch (NoSuchFieldException | IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    @Test
    @SuppressWarnings("unchecked")
    public void remove() {
        BinarySearchTree<String> bst = new BinarySearchTree<>();

        for (String str : fisherYatesShuffle(dummyStrings, SEED))
            bst.add(str);

        Field  rootNode;
        try {
            rootNode = BinarySearchTree.class.getDeclaredField("rootNode");
            rootNode.setAccessible(true);
            BiNode<String> root = (BiNode<String>) rootNode.get(bst);

            for (String str : fisherYatesShuffle(dummyStrings, SEED)) {
                assertTrue(bst.remove(str));
                root = (BiNode<String>) rootNode.get(bst);
                traverse(root);
                assertFalse(bst.remove(str));
            }

        } catch (NoSuchFieldException | IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    @Test
    @SuppressWarnings("unchecked")
    public void popEdge2() {
        BinarySearchTree<String> bst = new BinarySearchTree<>();
        bst.add("Hello");
        bst.add("Apple");
        bst.add("Zebra");
        Field rootNode;
        try {
            rootNode = BinarySearchTree.class.getDeclaredField("rootNode");
            rootNode.setAccessible(true);
            BiNode<String> node = (BiNode<String>) rootNode.get(bst);
            assertEquals("Hello", bst.pop("Hello"));
            assertNull(bst.pop("Hello"));
            node = (BiNode<String>) rootNode.get(bst);
            traverse(node);

        } catch (IllegalAccessException | NoSuchFieldException e) {
            e.printStackTrace();
        }
    }

    private void traverse(BiNode<String> node) {
        if (node != null) {
            if (node.getLeftNode() != null) {
                assertTrue(node.getLeftNode().getData().compareTo(node.getData()) < 0);
                traverse(node.getLeftNode());
            }
            if (node.getRightNode() != null) {
                assertTrue(node.getRightNode().getData().compareTo(node.getData()) > 0);
                traverse(node.getRightNode());
            }
        }
    }


    private String[] fisherYatesShuffle(String[] strings, int seed) {
        Random rnd = new Random(seed);
        String[] copyStrings = strings.clone();
        for (int i = strings.length - 1; i > 0; i--) {
            int index = rnd.nextInt(i + 1);
            String str = copyStrings[index];
            copyStrings[index] = copyStrings[i];
            copyStrings[i] = str;
        }
        return copyStrings;
    }
}
