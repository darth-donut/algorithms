/**
 * Created by jiahong on 7/01/17.
 */
package struct.node;

import java.util.LinkedList;

public class MultiNode<T> extends Node<T> {
    private Node<T> parentNode;
    private LinkedList<MultiNode<T>> children;
    private T data;

    /**
     * Initializes a node with data
     * @param data data to be stored
     */
    public MultiNode(T data) {
        children = new LinkedList<>();
    }

    /**
     * Initializes node with data as null
     */
    public MultiNode() {
        this(null);
    }

    /**
     * Returns a reference to internal data stored
     * @return T
     */
    public T getData() {
        return data;
    }

    /**
     * Sets the internal data to the newly provided value in @param
     * @param data new data to be stored
     */
    public void setData(T data) {
        this.data = data;
    }

    /**
     * Returns true if any child node has the same data
     * @param data the data to look for within child nodes
     * @return boolean
     */
    public boolean hasChildWithData(T data) {
        for (MultiNode<T> n : children) {
            if (n.getData().equals(data))
                return true;
        }
        return false;
    }

    /**
     * To be considered equal, they need to have the <b>same</b>
     * <ul>
     *     <li>reference</li>
     *     <li>child nodes (including number of child, and similar child objects - it calls their equals() method
     *     </li>
     *     <li>internal data</li>
     * </ul>
     * @param other other object to be compared to
     * @return boolean
     */
    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object other) {
        if (other == null) return false;
        if (other.getClass() != getClass()) return false;
        MultiNode<T> castedOther = (MultiNode<T>)other;
        return castedOther == this &&
                castedOther.children.equals(this.children) &&
                this.data.equals(castedOther.data);

    }

    /**
     * Sets the parent Node to the specified Node
     * @param parentNode node to be set as parentNode
     */
    @Override
    public void setParentNode(Node<T> parentNode) {
        this.parentNode = parentNode;
    }

    /**
     * Returns a reference to the parentNode of this calling object
     * @return MultiNode:T
     */
    @Override
    public MultiNode<T> getParentNode() {
        return (MultiNode<T>) this.parentNode;
    }
}
