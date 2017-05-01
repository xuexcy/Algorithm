//
// Created by Xue,Chengyun on 2017/4/27.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <codecvt>

using namespace std;

std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

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

// 数组存储子节点
// 试用范围:字符范围小,例如,只有英文大写字符或只有英文小写字符
struct Node1 {
    Node1(int size) {
        children = vector<Node1*>(size, NULL);
    }
    vector<Node1*> children;
    bool exist = false;
};

// hash表存储子节点
// 适用范围:字符范围大,例如,unicode中的各种英文、日语、汉字等字符
struct Node2 {
    unordered_map<char32_t, Node2*> children;
    bool exist = false;
};


// 有序数组存储子节点
// 适用范围:字符范围大但常用字符值稀疏,例如,使用英文、汉字的unicode值代替字符
struct Node3 {
    // sort the children by the code of the character
    vector<pair<int, Node3*>> children;
    bool exist = false;
};

class Trie1{
public:
    Trie1(int minNum, int maxNum): minNum(minNum), total(maxNum-minNum+1) {
        if (total > 0) {
            root = new Node1(total);
        }
    }

    ~Trie1() {
        deleteNode(root);
    }

    void insert(const vector<string>& dict) {
        for (int i = 0; i < dict.size(); ++i) {
            insert(dict[i]);
        }
    }

    bool insert(string s) {
        if (!valid(s)) {
            return false;
        }
        Node1* node = root;
        for (int i = 0; i < s.length(); ++i) {
            int index = s[i] - minNum;
            if (node->children[index] == NULL) {
                node->children[index] = new Node1(total);
            }
            node = node->children[index];
        }
        node->exist = true;
        return true;
    }

    bool isExist(string s) {
        if (!valid(s)) {
            return false;
        }
        Node1* node = root;
        for (int i = 0; i < s.length(); ++i) {
            int index = s[i] - minNum;
            if (node->children[index] == NULL) {
                return false;
            }
            node = node->children[index];
        }
        return node->exist;
    }

private:
    Trie1() {} /// 禁止无参数构造函数

    bool valid(string s) {
        for (int i = 0; i < s.length(); ++i) {
            int index = s[i] - minNum;
            if (index < 0 || index >= total) {
                return false;
            }
        }
        return true;
    }

    void deleteNode(Node1* node) {
        if (node == NULL) {
            return ;
        }
        for (int i = 0; i < total; ++i) {
            deleteNode(node->children[i]);
        }
        delete node;
    }

private:
    // char: [minNum, minNum+total)
    int minNum;
    int total;
    Node1* root;
};



class Trie2 {
public:
    Trie2() {
        root = new Node2();
    }

    ~Trie2() {
        deleteNode(root);
    }

    void insert(const vector<string>& dict) {
        for (int i = 0; i < dict.size(); ++i) {
            insert(dict[i]);
        }
    }

    void insert(string s) {
        u32string str = converter.from_bytes(s);
        Node2* node = root;
        for (int i = 0; i < str.length(); ++i) {
            if (node->children.find(str[i]) == node->children.end()) {
                node->children[str[i]] = new Node2();
            }
            node = node->children[str[i]];
        }
        node->exist = true;
    }

    bool isExist(string s) {
        u32string str = converter.from_bytes(s);
        Node2* node = root;
        for (int i = 0; i < str.length(); ++i) {
            if (node->children.find(str[i]) == node->children.end()) {
                return false;
            }
            node = node->children[str[i]];
        }
        return node->exist;
    }

private:
    void deleteNode(Node2* node) {
        for (unordered_map<char32_t, Node2*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
            deleteNode(it->second);
        }
        delete node;
    }
private:
    Node2* root;
};

class Trie3 {
public:
    Trie3() {
        root = new Node3();
    }

    ~Trie3() {
        deleteNode(root);
    }

    void insert(const vector<string>& dict) {
        for (int i = 0; i < dict.size(); ++i) {
            insert(dict[i]);
        }
    }
    void insert(string s) {
        u32string str = converter.from_bytes(s);
        Node3* node = root;
        vector<pair<int, Node3*>>::iterator it;
        for (int i = 0; i < str.length(); ++i) {
            int num = str[i];
            it = std::lower_bound(node->children.begin(),
                                  node->children.end(),
                                  make_pair(num, (Node3*)NULL),
                                  [](const pair<int, Node3*>& p1, const pair<int, Node3*>& p2) {
                                      return p1.first < p2.first;
                                  }
            );
            int index = it - node->children.begin();
            if (it == node->children.end() || it->first != num) {
                node->children.insert(it, make_pair(num, new Node3()));

            }
            // you can't use "node = it->second", after insertion,
            // the address of the vector("node->children") may change
            node = node->children[index].second;
        }
        node->exist = true;
    }

    bool isExist(string s) {
        u32string str = converter.from_bytes(s);
        Node3* node = root;
        vector<pair<int, Node3*>>::iterator it;
        for (int i = 0; i < str.length(); ++i) {
            int num = str[i];
            it = std::lower_bound(node->children.begin(),
                                  node->children.end(),
                                  make_pair(num, (Node3*)NULL),
                                  [](const pair<int, Node3*>& p1, const pair<int, Node3*>& p2) {
                                      return p1.first < p2.first;
                                  }
            );
            if (it == node->children.end() || it->first != num) {
                return false;
            }
            node = it->second;
        }
        return node->exist;
    }

private:
    void deleteNode(Node3* node) {
        for (int i = 0; i < node->children.size(); ++i) {
            deleteNode(node->children[i].second);
        }
        delete node;
    }
private:
    Node3* root;
};

void testTrie1() {
    vector<string> dict{"bear", "bell", "bid", "bull", "buy", "sell", "stock", "stop"};
    Trie1 trie('a', 'z');
    trie.insert(dict);
    cout << "# 1: " << dictToString(dict) << endl;
    cout << "bell " << trie.isExist("bell") << endl;
    cout << "stock " << trie.isExist("stock") << endl;
    cout << "bu " << trie.isExist("bu") << endl;
    cout << "insert \"bu\"" << endl;
    trie.insert("bu");
    cout << "bu " << trie.isExist("bu") << endl << endl;
}


void testTrie2() {
    vector<string> dict{"beaR", "bEll好", "Bid", "bull", "BUy", "sell", "Stock", "stop"};
    Trie2 trie;
    trie.insert(dict);
    cout << "# 2: " << dictToString(dict) << endl;
    cout << "bEll好 " << trie.isExist("bEll好") << endl;
    cout << "Stock " << trie.isExist("Stock") << endl;
    cout << "b么么哒u " << trie.isExist("b么么哒u") << endl;
    cout << "insert \"b么么哒u\"" << endl;
    trie.insert("b么么哒u");
    cout << "b么么哒u " << trie.isExist("b么么哒u") << endl << endl;
}

void testTrie3() {
    vector<string> dict{"beaR", "bEll好", "Bid", "bull", "BUy", "sell", "Stock", "stop"};
    Trie3 trie;
    trie.insert(dict);
    cout << "# 3: " << dictToString(dict) << endl;
    cout << "bEll好 " << trie.isExist("bEll好") << endl;
    cout << "Stock " << trie.isExist("Stock") << endl;
    cout << "b么么哒u " << trie.isExist("b么么哒u") << endl;
    cout << "insert \"b么么哒u\"" << endl;
    trie.insert("b么么哒u");
    cout << "b么么哒u " << trie.isExist("b么么哒u") << endl << endl;
}


int main() {
    testTrie1();
    testTrie2();
    testTrie3();
}