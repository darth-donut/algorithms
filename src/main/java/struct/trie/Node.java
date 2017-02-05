/*
 * Created by jiahong on 14/01/17.
 * data_structures::struct.trie.node
 */
package struct.trie;

import java.nio.charset.UnsupportedCharsetException;

class Node<T> {
     Node<T>[] childrenNodes;
     CharFreq character;
     Node<T> parent;
     private int charset;
     T data;

     @SuppressWarnings("unchecked")
     Node(CharFreq character, int charset, T data) {
        this.parent = null;
        this.character = character;
        this.childrenNodes = (Node<T>[]) new Node<?>[charset];
        this.charset = charset;
        this.data = data;
    }

     Node() {  this(null, Trie.ASCII, null); }

     Node<T> getChild(CharFreq c) {
        return childrenNodes[c.offsetStr(charset)];
    }

     T getData() {
         return data;
     }

     Node<T> getChild(char c) throws UnsupportedCharsetException {
        CharFreq temp = new CharFreq(c, 0);
        return childrenNodes[temp.offsetStr(charset)];
     }

     void setChild(Node<T> child) {
        CharFreq tmp = new CharFreq(child.character.chr, 0);
        childrenNodes[tmp.offsetStr(charset)] = child;
        child.parent = this;
     }

     boolean isLeaf() {
         for (Node<T> n : childrenNodes)
             if (n != null)
                 return false;
         return true;
     }

}
