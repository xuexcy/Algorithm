#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<map>
using namespace std;


void countingSort(vector<int>& v) {
    map<int, int> m;
	for(int i = 0; i < v.size(); ++i){
        m[v[i]] += 1;
    }
    int t = 0;
    for(const auto& p : m){
        for_each(v.begin()+t, v.begin() + t + p.second, [&](int& i){i = p.first;});
        t += p.second;
    }
}

void print(vector<int>& v) {
    int len = v.size();
	for(int i = 0; i < len - 1; ++i) {
		cout << v[i] << " ";
	}
	if (v.size()) {
		cout << v.back() << endl;
	}
}
int main() {
	srand((int)time(0));
	vector<int> v;
	for (int i = 0; i < 20; ++i) {
		v.push_back(rand()%10);
	}
	print(v);
	countingSort(v);
	print(v);
	return 0;
}
