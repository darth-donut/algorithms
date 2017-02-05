/**
 * Created by JiaHong on 25/12/2016.
 */
package struct.graph.bst;

import struct.DataStructure;
import struct.node.BiNode;
import struct.node.NotAChildNodeException;

public class BinarySearchTree <T extends Comparable<? super T>> implements DataStructure<T> {

    private BiNode<T> rootNode;

    public BinarySearchTree() {
        rootNode = null;
    }

    @Override
    public void add(T item) {
        rootNode = recursiveAdd(rootNode, item);
    }

    @Override
    public boolean search(T item) {
        return recursiveSearch(rootNode, item);
    }

    @Override
    public T get(T item) {
        return recursiveGet(rootNode, item).getData();
    }

    private void handleLeftSuccessor(BiNode<T> candidateNode, BiNode<T> root) {
        /*
            1) set candidate's rightNode to root's rightNode, and update root's rightNode to reflect lineage
                i.e. root's old rightNode's parent to candidate node
            2) if candidate's leftNode is not null, we assign candidate's leftNode to candidate's parent as a
                rightNode, reflect lineage, assign null otherwise
            3) candidate's leftNode is now root's leftNode, and reflect the lineage
            4) candidate's parentNode is now root's parentNode, reflect the lineage
         */
        // Step 1
        candidateNode.setRightNode(root.getRightNode());
        if (root.getRightNode() != null)
            root.getRightNode().setParentNode(candidateNode);

        // Step 2
        candidateNode.getParentNode().setRightNode(candidateNode.getLeftNode());
        if (candidateNode.getLeftNode() != null)
            candidateNode.getLeftNode().setParentNode(candidateNode.getParentNode());

        // Step 3
        candidateNode.setLeftNode(root.getLeftNode());
        if (root.getLeftNode() != null)
            root.getLeftNode().setParentNode(candidateNode);

        try {
            // Step 4
            candidateNode.setParentNode(root.getParentNode());
            if (root.isLeftNode())
                root.getParentNode().setLeftNode(candidateNode);
            else if (root.isRightNode())
                root.getParentNode().setRightNode(candidateNode);
                // else root is a rootNode in tree
            else
                rootNode = candidateNode;
        } catch (NotAChildNodeException e) {
            e.printStackTrace();
        }

    }

    private void handleRightSuccessor(BiNode<T> candidateNode, BiNode<T> root) {
        /*
            1) set candidate's leftNode to root's leftNode (since candidate has no left child (smallest)
            2) set root's leftNode parent to candidate

            3) set candidate's parent to root's parent
            4) make root's parent point to candidate (left/right depends on root's orientation)

            5) if candidate has right child, assign rightNode to candidate's old parent node as the left node
             (since they are all smaller than candidate's parent)
            6) and update candidate's parent leftNode to the new childNode (candidate's rightNode) null otherwise

            7) candidate's rightNode is now root's rightNode (update both nodes!)
         */

        // steps 5,6
        candidateNode.getParentNode().setLeftNode(candidateNode.getRightNode());
        if (candidateNode.getRightNode() != null)
            candidateNode.getRightNode().setParentNode(candidateNode.getParentNode());

        // step 7
        candidateNode.setRightNode(root.getRightNode());
        if (root.getRightNode() != null)
            root.getRightNode().setParentNode(candidateNode);

        // step 3, 4
        candidateNode.setParentNode(root.getParentNode());
        try {
            if (root.isLeftNode())
                root.getParentNode().setLeftNode(candidateNode);
                // don't use else here, root might be the tree's rootNode
            else if (root.isRightNode())
                root.getParentNode().setRightNode(candidateNode);
            else
                rootNode = candidateNode;
        } catch (NotAChildNodeException e) {
            e.printStackTrace();
        }

        // step 1, 2
        candidateNode.setLeftNode(root.getLeftNode());
        if (root.getLeftNode() != null)
            root.getLeftNode().setParentNode(candidateNode);
    }

    @Override
    public T pop(T item) {
        // you either go right branch's left most node (i.e. next smallest large item) -> left branch maintains
        // and right branch maintains because the right branch is still larger than the smallest old right branch
        BiNode<T> root = recursiveGet(rootNode, item);
        if (root == null) return null;
        BiNode<T> candidateNode;
        if (root.getLeftNode() != null) {
            // find the candidate node (in this case, largest of the left branch)
            candidateNode = getLargest(root.getLeftNode());
            if (!candidateNode.equals(root.getLeftNode())) {
                handleLeftSuccessor(candidateNode, root);
            } else if (root.getRightNode() != null) {
                // avoid sticky situation by delegating this to the right node
                candidateNode = getSmallest(root.getRightNode());
                if (candidateNode.equals(root.getRightNode())) {
                    // alright, we cannot avoid this no more, we need to deal with immediate candidate nodes
                    try {
                        if (root.getParentNode() != null) {
                            if (root.isLeftNode())
                                root.getParentNode().setLeftNode(candidateNode);
                            else if (root.isRightNode())
                                root.getParentNode().setRightNode(candidateNode);
                        }
                        candidateNode.setParentNode(root.getParentNode());
                        if (root.isRootNode()) rootNode = candidateNode;
                        root.getLeftNode().setParentNode(candidateNode);
                        candidateNode.setLeftNode(root.getLeftNode());

                    } catch (NotAChildNodeException e) {
                        e.printStackTrace();
                    }
                } else {
                    handleRightSuccessor(candidateNode, root);
                }
            } else {
                /* at this stage, we can safely assign the grandparentNode to candidate because
                    root has no right node, and since candidate is its immediate child, we just delete the
                    root (intermediate between grandparentNode and candidateNode)
                 */
                try {
                    if (root.isLeftNode())
                        root.getParentNode().setLeftNode(candidateNode);
                    else if (root.isRightNode())
                        root.getParentNode().setRightNode(candidateNode);
                    else
                        rootNode = candidateNode;
                    candidateNode.setParentNode(root.getParentNode());
                } catch (NotAChildNodeException e) {
                    e.printStackTrace();
                }
            }
        } else if (root.getRightNode() != null) {
            // find the candidate node (smallest of the right branch)
            candidateNode = getSmallest(root.getRightNode());
            if (!candidateNode.equals(root.getRightNode())) {
                handleRightSuccessor(candidateNode, root);
            } else {
                /* at this stage, we can safely assign the grandparentNode to candidate because
                    root has no left node, and since candidate is its immediate child, we just delete the
                    root (intermediate between grandparentNode and candidateNode)
                 */
                try {
                    if (root.isLeftNode())
                        root.getParentNode().setLeftNode(candidateNode);
                    else if (root.isRightNode())
                        root.getParentNode().setRightNode(candidateNode);
                    else
                        rootNode = candidateNode;
                    candidateNode.setParentNode(root.getParentNode());
                } catch (NotAChildNodeException e) {
                    e.printStackTrace();
                }
            }
        } else {
            try {
                if (root.isLeftNode())
                    root.getParentNode().setLeftNode(null);
                else if (root.isRightNode())
                    root.getParentNode().setRightNode(null);
                else
                    // rootNode is the ONLY node
                    rootNode = null;

            } catch (NotAChildNodeException e) {
                e.printStackTrace();
            }
        }
        return root.getData();
    }

    @Override
    public boolean remove(T item) {
        return pop(item) != null;
    }

    private BiNode<T> getSmallest(BiNode<T> root) {
        if (root.getLeftNode() != null)
            return getSmallest(root.getLeftNode());
        return root;
    }

    private BiNode<T> getLargest(BiNode<T> root) {
        if (root.getRightNode() != null)
            return getLargest(root.getRightNode());
        return root;
    }

    private BiNode<T> recursiveGet(BiNode<T> node, T key) {
        if (node == null)
            return null;
        int cmp = node.getData().compareTo(key);
        if (cmp == 0) {
            return node;
        } else if (cmp < 0) {
            return recursiveGet(node.getRightNode(), key);
        } else {
            return recursiveGet(node.getLeftNode(), key);
        }
    }

    private BiNode<T> recursiveAdd(BiNode<T> node, T key) {
        if (node == null)
            return new BiNode<>(key);

        int res = node.getData().compareTo(key);

        if (res < 0) {
            node.setRightNode(recursiveAdd(node.getRightNode(), key));
            node.getRightNode().setParentNode(node);
        } else if (res > 0) {
            node.setLeftNode(recursiveAdd(node.getLeftNode(), key));
            node.getLeftNode().setParentNode(node);
        }
        // else; nothing(we treat duplicates as one)
        return node;
    }

    private boolean recursiveSearch(BiNode<T> node, T key) {
        if (node == null)
            return false;

        int cmp = node.getData().compareTo(key);
        if (cmp == 0)
            return true;
        else if (cmp < 0)
            return recursiveSearch(node.getRightNode(), key);
        else
            return recursiveSearch(node.getLeftNode(), key);
    }
}
