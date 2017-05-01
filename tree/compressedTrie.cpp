//
// Created by Xue,Chengyun on 2017/5/1.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// "{word1, word2, word3, ...}"
string dictToString(const vector<string>& dict) {
    string s = "{";
    if (!dict.empty()) {
        for (int i = 0; i < dict.size()-1; ++i) {
            s += dict[i] + ", ";
        }
        s += dict.back();
    }
    s += "}";
    return s;
}

struct Node {
    unordered_map<string, Node*> children;
    bool exist = false;
};

class CompressedTrie {
public:
    CompressedTrie() {
        root = new Node();
    }

    ~CompressedTrie() {
        deleteNode(root);
    }

    void insert(const vector<string>& dict) {
        for (int i = 0; i < dict.size(); ++i) {
            insert(dict[i]);
        }
    }

    void insert(string s) {
        Node* node = root;
        for (unordered_map<string, Node*>::iterator it = node->children.begin();
             it != node->children.end() && s.length() != 0;) {
            string next_str = it->first;
            Node* next_node = it->second;
            int len = min(next_str.length(), s.length());

            // get common prefix string len
            // pre_len("abc", "abda") = 2
            int i;
            for (i = 0; i < len && next_str[i] == s[i]; ++i);

            string prefix_str = next_str.substr(0, i);
            if (i == 0) {
                ++it;
                continue;
            } else if (i == len) {
                // (next_str, s)
                // (abc, ab)->(ab_TRUE(c))
                // (abc, abc)->(abc_TRUE)
                // (abc, abcdef)->(abc(def))
                if  (next_str.length() > s.length()) {
                    Node* inserted_node = node->children[prefix_str] = new Node();
                    inserted_node->children[next_str.substr(i)] = next_node;
                    node->children.erase(next_str);
                    next_node = inserted_node;
                }
            } else {
                // (next_str, s)
                // (abc, abd)->(ab(c, d_TRUE))
                // (abc, ac)->(a(bc, c_TRUE))
                // (abc, abdef)->(ab(c, def_TRUE))
                Node* inserted_node = node->children[prefix_str] = new Node();
                inserted_node->children[next_str.substr(i)] = next_node;
                inserted_node->children[s.substr(i)] = new Node();
                node->children.erase(next_str);
                next_node = inserted_node;
            }
            s = s.substr(i);
            node = next_node;
            it = node->children.begin();
        }

        if (s.length() != 0) { // insert a new node as a leaf
            node = node->children[s] = new Node();
        }
        node->exist = true;
    }

    bool isExist(string s) {
        Node* node = root;
        for (unordered_map<string, Node*>::iterator it = node->children.begin();
             it != node->children.end() && s.length() != 0;) {
            string next_str = it->first;
            Node* next_node = it->second;
            int len = min(next_str.length(), s.length());

            // get common prefix string len
            // pre_len("abc", "abda") = 2
            int i;
            for (i = 0; i < len && next_str[i] == s[i]; ++i);

            if (i == 0) {
                ++it;
                continue;
            } else if (i < next_str.length()) {
                // (abc, ab)->(false)
                // (abc, abd)->(false)
                return false;
            } else {
                s = s.substr(i);
                node = next_node;
                it = node->children.begin();
            }
        }
        return (s.length() == 0) ? node->exist : false;
    }

private:
    void deleteNode(Node* node) {
        for (unordered_map<string, Node*>::iterator it = node->children.begin();
             it != node->children.end();
             ++it) {
            deleteNode(it->second);
        }
        delete node;
    }

private:
    Node* root;
};

void testCompressedTrie() {
    vector<string> dict{"beaR", "bEll好", "Bid", "bull", "BUy", "sell", "Stock", "stop"};
    CompressedTrie trie;
    trie.insert(dict);
    cout << "# 1: " << dictToString(dict) << endl;
    cout << "bEll好 " << trie.isExist("bEll好") << endl;
    cout << "Stock " << trie.isExist("Stock") << endl;
    cout << "b么么哒u " << trie.isExist("b么么哒u") << endl;
    cout << "insert \"b么么哒u\"" << endl;
    trie.insert("b么么哒u");
    cout << "b么么哒u " << trie.isExist("b么么哒u") << endl << endl;
}

int main() {
    testCompressedTrie();
}