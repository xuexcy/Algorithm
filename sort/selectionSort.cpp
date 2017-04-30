#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

void selectionSort(vector<int>& v) {
	for(int i = 0; i < v.size(); ++i){
        int minIndex = i;
        for(int j = i + 1; j < v.size(); ++j){
            if(v[j] < v[minIndex]){
                minIndex = j;
            }
        }
        swap(v[i], v[minIndex]);
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
	selectionSort(v);
	print(v);
	return 0;
}
