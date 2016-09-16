#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

void bubbleSort(vector<int>& v) {
	for(int i = 0; i < v.size(); ++i){
        bool flag = true;
        for(int j = v.size()-1; j > i; --j){
            if(v[j] < v[j-1]){
                flag = false;
                swap(v[j-1], v[j]);
            }
        }
        if(flag){
            break;
        }
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
		v.push_back(rand()%100);
	}
	print(v);
	bubbleSort(v);
	print(v);
	return 0;
}
