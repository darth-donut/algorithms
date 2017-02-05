/*
 * Created by jiahong on 14/01/17.
 * data_structures::struct.trie.charfreq
 */
package struct.trie;


public class CharFreq {
     char chr;
     int freq;
     CharFreq(char chr, int freq) {
        this.chr = chr;
        this.freq = freq;
    }

     int offsetStr(int charSet) {
        int outChar = 0;
        switch (charSet) {
            case Trie.ASCII:
                if (chr == '\n')
                    outChar = Trie.ASCII-1;
                else
                    outChar = chr - ' ';
                break;
            case Trie.KEY:
                outChar = (int)chr;
                break;
        }
        return outChar;
    }
}
