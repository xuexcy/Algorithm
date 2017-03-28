#include <vector>
#include <set>
#include <bitset>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

#define Children unordered_map<int, Node*>

const double ENTROPY_INF = numeric_limits<double>::max();

struct Node {
    int type;
    Children children;
};

class ID3Tree {
public:
    int dimensionality;
    ID3Tree(const vector<vector<int>>& datas) : datas(datas) {
        root = new Node();
        root->type = -1;
        root->children.clear();
        if (datas.size() == 0 || datas[0].size() <= 1) {
            return;
        }
        dimensionality = datas[0].size() - 1;
    }

    void build() {
        set<int> datas_index; // datas in use
        for (int i = 0; i <datas.size(); ++i) {
            datas_index.insert(i);
        }
        set<int> dimensions_index; // dimensions in use
        for (int i = 0; i < dimensionality; ++i) {
            dimensions_index.insert(i);
        }
        _build(root, datas_index, dimensions_index);
    }

    ~ID3Tree() {
        _clear(root);
    }

    int predicate(const vector<int>& data) {
        return data.size() == dimensionality ? _predicate(root, data) : -1;
    }
private:
    void _clear(Node* node) {
        if (node == NULL) {
            return;
        }
        Children& children = node->children;
        for (Children::const_iterator it = children.begin(); it != children.end(); ++it) {
            _clear(it->second);
        }
        node->children.clear();
        delete node;
    }

    void _build(Node* node, set<int> datas_index, set<int> dimensions_index) {
        if (datas_index.size() == 0) {
            node->type = -1;
            return;
        }
        node->type = _same_type(datas_index);
        if (node->type != -1 || dimensions_index.empty()) {
            return;
        }

        // get min information entropy
        double entropy = ENTROPY_INF;
        for (set<int>::const_iterator it = dimensions_index.begin(); it != dimensions_index.end(); ++it) {
            double tmp_entropy = _get_split_entropy(datas_index, *it);
            if (tmp_entropy < entropy) {
                node->type = *it;
                entropy = tmp_entropy;
            }
        }
        unordered_map<int, set<int>> dimension_type;
        for (set<int>::const_iterator it = datas_index.begin(); it != datas_index.end(); ++it) {
            int type = datas[*it][node->type];
            dimension_type[type].insert(*it);
        }
        dimensions_index.erase(node->type);
        for (unordered_map<int, set<int>>::const_iterator it = dimension_type.begin(); it != dimension_type.end(); ++it) {
            Node* child = new Node();
            _build(child, it->second, dimensions_index);
            node->children[it->first] = child;
        }
    }

    // split information entropy: split_entropy = sigma(p*info_entropy(Dj))
    double _get_split_entropy(set<int>& datas_index, int dimension_index) {
        // <dimension_type, <dimension_type_count, <data_type, data_type_count>>>
        unordered_map<int, pair<int, unordered_map<int, int>>> dimension_type_count;
        for (set<int>::const_iterator it = datas_index.begin(); it != datas_index.end(); ++it) {
            int dimension_type = datas[(*it)][dimension_index];
            int data_type = datas[*it][dimensionality];
            if (dimension_type_count.find(dimension_type) == dimension_type_count.end()) {
                dimension_type_count[dimension_type] = make_pair(0, unordered_map<int, int>());
            }
            ++dimension_type_count[dimension_type].first;

            unordered_map<int, int>& data_type_count = dimension_type_count[dimension_type].second;
            if (data_type_count.find(data_type) == data_type_count.end()) {
                data_type_count[data_type] = 0;
            }
            ++data_type_count[data_type];
        }

        double entropy = 0.0;

        for (unordered_map<int, pair<int, unordered_map<int,int>>>::const_iterator it = dimension_type_count.begin(); it != dimension_type_count.end(); ++it) {
            vector<int> numerator;
            const unordered_map<int, int>& data_type_count = it->second.second;
            transform(data_type_count.begin(), data_type_count.end(), back_inserter(numerator), [](decltype(*begin(data_type_count))& kv){return kv.second;});
            entropy += 1.0 * it->second.first / datas_index.size()* _cal_entropy(numerator);
        };
        return entropy;
    }

    // information entropy: info_entropy = -sigma(p*log(p))
    double _cal_entropy(const vector<int>& numerator) {
        int denominator = 0;
        double entropy = 0.0;
        for (int i = 0; i < numerator.size(); ++i) {
            denominator += numerator[i];
        }
        for (int i = 0; i < numerator.size(); ++i) {
            if (numerator[i] != 0) {
                double probability = 1.0 * numerator[i] / denominator;
                entropy -= 1.0 * probability * log(probability);
            }

        }
        return entropy;
    }

    // the type of the datas
    // -1 if not the same type
    int _same_type(const set<int>& datas_index) {
        int type = datas[*datas_index.begin()][dimensionality];
        for (set<int>::const_iterator it = datas_index.begin(); it != datas_index.end(); ++it) {
            if (datas[*it][dimensionality] != type) {
                return -1;
            }
        }
        return type;
    }

    int _predicate(const Node* node, const vector<int>& data) {
        if (node->type == -1 || node->children.size() == 0) {
            return node->type;
        }
        return _predicate(node->children.at(data[node->type]), data);
    }
private:
    vector<vector<int>> datas;
    Node* root;
};

enum outlook {SUNNY, OVERCAST, RAIN};
enum temp {HOT, MILD, COOL};
enum hum {HIGH, NORMAL};
enum windy {WEAK, STRONG};
enum play {NO, YES};
vector<vector<int>> datas = {
        {SUNNY, HOT, HIGH, WEAK, NO}, // 0
        {SUNNY, HOT, HIGH, STRONG, NO}, // 1
        {OVERCAST, HOT, HIGH, WEAK, YES}, // 2
        {RAIN, MILD, HIGH, WEAK, YES}, // 3
        {RAIN, COOL, NORMAL, WEAK, YES}, // 4
        {RAIN, COOL, NORMAL, STRONG, NO}, // 5
        {OVERCAST, COOL, NORMAL, STRONG, YES}, // 6
        {SUNNY, MILD, HIGH, WEAK, NO}, // 7
        {SUNNY, COOL, NORMAL, WEAK, YES}, // 8
        {RAIN, MILD, NORMAL, WEAK, YES}, // 9
        {SUNNY, MILD, NORMAL, STRONG, YES}, // 10
        {OVERCAST, MILD, HIGH, STRONG, YES}, // 11
        {OVERCAST, HOT, NORMAL, WEAK, YES}, // 12
        {RAIN, MILD, HIGH, STRONG, NO} // 13
};
int main() {
    ID3Tree tree(datas);
    tree.build();

    cout << tree.predicate({SUNNY, COOL, HIGH, STRONG}) << endl;

//    for (int i = 0; i < datas.size(); ++i) {
//        cout << tree.predicate(vector<int>(datas[i].begin(), datas[i].begin() + 4)) << endl;
//    }

    return 0;
}