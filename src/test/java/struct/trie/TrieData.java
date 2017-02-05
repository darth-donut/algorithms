/*
 * Created by jiahong on 14/01/17.
 * data_structures::struct.trie
 */
package struct.trie;

public class TrieData implements StringPackage {
    String string;

    TrieData(String str) {
        this.string = str;
    }

    @Override
    public String getString() {
        return string;
    }

    @Override
    public boolean equals(Object other) {
        if (other == null) return false;
        if (other.getClass() != getClass()) return false;
        TrieData cother = (TrieData)other;
        return cother.string == string;
    }
}
