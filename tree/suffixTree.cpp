//
// Created by Xue,Chengyun on 2017/5/1.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

struct Node {
    unordered_map<string, Node*> children;
    bool exist = false;
};

class SuffixTree1 {
public:
    SuffixTree1(string s) {
        root = new Node();
        for (int i = 0; i < s.length(); ++i) {
            insert(s, i);
        }
    }

    ~SuffixTree1() {
        deleteNode(root);
    }

    // check the suffix's prefix, such as in banana
    // "an" is prefix of "ana" and "anana",
    // which are the suffix of "banana"
    bool hasSubstring(string s) {
        return getSubstringNode(s) != NULL;
    }

    // "banana" has two substring "na"
    int countSubstring(string s) {
        Node* node = getSubstringNode(s);
        if (node == NULL) {
            return 0;
        }
        int ct = 0;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            node = q.front();
            q.pop();
            if (node->children.empty()) {
                ++ct;
                continue;
            }
            for (unordered_map<string, Node*>::iterator it = node->children.begin();
                 it != node->children.end(); ++it) {
                q.push(it->second);
            }
        }
        return ct;
    }

    // "ana" is the longest substring that appears at least twice in "banana'
    vector<string> longestRepeatedSubstring() {
        if (root->children.empty()) {
            return vector<string>();
        }
        Node* node = root;
        string s = "";
        unordered_set<string> ans_set;
        ans_set.insert(s);
        queue<pair<string, Node*>> q;
        q.push(make_pair(s, node));
        while (!q.empty()) {
            s = q.front().first;
            node = q.front().second;
            q.pop();

            bool hasIternalChildNode = false;
            for (unordered_map<string, Node*>::iterator it = node->children.begin();
                 it != node->children.end(); ++it) {
                if (!it->second->children.empty()) {
                    hasIternalChildNode = true;
                    q.push(make_pair(s + it->first, it->second));
                    ans_set.insert(s + it->first);
                }
            }
            if (hasIternalChildNode) {
                ans_set.erase(s);
            }
        }

        vector<string> ans;
        int maxLen = 0;
        for (unordered_set<string>::iterator it = ans_set.begin(); it != ans_set.end(); ++it) {
            if ((*it).length() >= maxLen) {
                if ((*it).length() > maxLen) {
                    ans.clear();
                    maxLen = (*it).length();
                }
                ans.push_back(*it);
            }
        }
        return ans;
    }

private:
    void insert(string s, int pos) {
        // end with $, in case suffix1 is a prefix of suffix2, such as in banana,
        // "na" is a prefix of "nana", "ana" is a prefix of "anana"
        s = s.substr(pos) + "$"; // end with $

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

    Node* getSubstringNode(string s) {
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
            } else if (i != len) {
                // (abc, ac)->(false)
                // (abc, abd)->(false)
                // (abc, abde)->(false)
                return NULL;
            } else {
                s = s.substr(i);
                node = next_node;
                it = node->children.begin();
            }
        }
        return (s.length() == 0) ? node : NULL;
    }

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

void testSuffixTree1() {
    string s = "banananbnana";
    SuffixTree1 tree(s);
    cout << "# 1: " << s << endl;
    cout << "nan exists: " << tree.hasSubstring("nan") << endl;
    cout << "a exists: " << tree.hasSubstring("a") << endl;
    cout << "nanan exists: " << tree.hasSubstring("nanan") << endl;

    cout << "a counts: " << tree.countSubstring("a") << endl;
    cout << "na counts: " << tree.countSubstring("na") << endl;
    cout << "an counts: " << tree.countSubstring("an") << endl;
    cout << "ana counts: " << tree.countSubstring("ana") << endl;
    cout << "nan counts: " << tree.countSubstring("nan") << endl;
    cout << "anan counts: " << tree.countSubstring("anan") << endl;
    cout << "nana counts: " << tree.countSubstring("nana") << endl;
    cout << "nanann counts: " << tree.countSubstring("nanann") << endl;

    cout << "longest repeated substring:";
    vector<string> ans = tree.longestRepeatedSubstring();
    for (int i = 0; i < ans.size(); ++i) {
        cout << " " << ans[i];
    }
    cout << endl;
}
int main() {
    testSuffixTree1();
}