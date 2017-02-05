//
// Created by jiahong on 22/01/17.
//

#include <cassert>
#include <fstream>
#include "Trie.h"

using std::string;
using ds::Trie;

void stress_test();

int
main() {
    Trie<int> trie;
    string arr[] = {
            "hello",
            "world",
            "testing",
            "cases",
            "for",
            "trie",
            "case",
            "test"
    };

    for (auto s: arr)
        assert(!trie.has(s));

    int index = 0;
    for (auto s : arr)
        trie.add(s, new int(++index));


    for (auto s: arr)
        assert(trie.get(s) != nullptr);

    for (auto s: arr)
        assert(trie.has(s));

    trie.add("test", new int(100));
    assert(*trie.get("test") == 100);

    for (auto s: arr)
        assert(trie.get(s) != nullptr);

    for (auto s: arr)
        assert(trie.has(s));

    int *res = trie.remove("test");

    assert(*res == 100);

    delete res;

    res = trie.remove("testing");

    assert(*res == 3);

    delete res;

//    stress_test();
    std::cout << "All tests passed" << std::endl;
}

void
stress_test() {
    std::ifstream in("/home/jiahong/comp/comp_10002/ass2/pg2600.txt");
    string buffer;
    Trie<int> trie;
    int index = 0;
    int ch;
    while ((ch = in.get()) != EOF) {
        buffer.push_back((char)ch);
        if (trie.has(buffer)) continue;
        trie.add(buffer, new int(++index));
        buffer.clear();
    }
}
