#include "../src/Trie.h"

#define BOOST_TEST_MODULE TrieTest
#include <boost/test/unit_test.hpp>


using std::string;      using std::cout;
using ds::Trie;         using std::endl;

BOOST_AUTO_TEST_CASE(trie_basic_test) {
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
        BOOST_CHECK(!trie.has(s));

    int index = 0;
    for (auto s : arr)
        trie.add(s, new int(++index));


    for (auto s: arr)
        BOOST_CHECK(trie.get(s) != nullptr);

    for (auto s: arr)
        BOOST_CHECK(trie.has(s));

    trie.add("test", new int(100));
    BOOST_CHECK(*trie.get("test") == 100);

    for (auto s: arr)
        BOOST_CHECK(trie.get(s) != nullptr);

    for (auto s: arr)
        BOOST_CHECK(trie.has(s));
}