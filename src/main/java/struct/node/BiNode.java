/**
 * Created by JiaHong on 25/12/2016.
 */
package struct.node;

/**
 * A node that has 2 outgoing edges
 */
public class BiNode <T> extends Node<T> {

    private BiNode<T> leftNode;
    private BiNode<T> rightNode;
    private Node<T> parentNode;

    public BiNode(T data) {
        super(data);
        parentNode = leftNode = rightNode = null;
    }

    /**
     * Sets parent node to the specified BiNode<T>
     * @param parentNode set BiNode object
     */
    @Override
    public void setParentNode(Node<T> parentNode) {
        this.parentNode = parentNode;
    }

    /**
     * Returns the parent node as a BiNode object
     * @return return BiNode object
     */
    @Override
    public BiNode<T> getParentNode() {
        return (BiNode<T>) parentNode;
    }

    /**
     * Returns the leftNode of this BiNode as a BiNode<T> reference
     * @return left node (Type BiNode<T>)
     */
    public BiNode<T> getLeftNode() {
        return leftNode;
    }

    /**
     * Returns the rightNode of this BiNode as a BiNode<T> reference
     * @return right node (Type BiNode<T>)
     */
    public BiNode<T> getRightNode() {
        return rightNode;
    }

    /**
     * Sets the leftNode of this BiNode
     * @param node to be inserted as the leftNode
     */
    public void setLeftNode(BiNode<T> node) {
        this.leftNode = node;
    }

    /**
     * Sets the rightNode of this BiNode
     * @param node to be inserted as the right
     */
    public void setRightNode(BiNode<T> node) {
        this.rightNode = node;
    }

    /**
     * Check if this node is a left child
     * @return true if is a left node
     */
    public boolean isLeftNode() throws NotAChildNodeException {
        if (isRootNode()) return false;
        if (getParentNode().getLeftNode() == null) return false;
        boolean out = getParentNode().getLeftNode().equals(this);
        if (!out) {
            if (!getParentNode().getRightNode().equals(this))
                throw new NotAChildNodeException("Node's parent isn't pointing to this node, fatal error");
        }
        return out;
    }

    /**
     * Check if this node is a right child
     * @return true if is a right child
     */
    public boolean isRightNode() throws NotAChildNodeException {
        if (isRootNode()) return false;
        if (getParentNode().getRightNode() == null) return false;
        boolean out = getParentNode().getRightNode().equals(this);
        if (!out) {
            if (!getParentNode().getLeftNode().equals(this))
                throw new NotAChildNodeException("Node's parent isn't pointing to this node, fatal error");
        }
        return out;
    }


    /**
     * Returns true if parentNode == null
     * @return true if is a rootNode
     */
    public boolean isRootNode() {
        return parentNode == null;
    }

    /**
     * Other object is only equal if it has all the same attributes, and is of the same reference
     * @param other Other compared object
     * @return True if equals
     */
    @Override
    public boolean equals(Object other) {
        if (other == null) return false;
        if (other.getClass() != getClass()) return false;
        BiNode<T> cother = (BiNode<T>)other;
        return cother == this &&
                cother.data == this.data &&
                this.leftNode == cother.leftNode &&
                this.rightNode == cother.rightNode &&
                this.parentNode == cother.parentNode;
    }
}
