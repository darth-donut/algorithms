/**
 * Created by JiaHong on 25/12/2016.
 */
package struct.node;

/**
 * Provides the basic functionality for bi/tri/multi-Node classes
 * @param <T> Type of data stored in node
 */
public abstract class Node <T> {

    protected T data;

    public Node(T data) {
        this.data = data;
    }

    public Node() {
        this(null);
    }

    public void setData(T data) {
        this.data = data;
    }

    public T getData() {
        return data;
    }

    public abstract void setParentNode(Node<T> parentNode);

    public abstract Node<T> getParentNode();

}
