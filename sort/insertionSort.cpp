#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
using namespace std;

void insertionSort(vector<int>& v) {
	for (int i = 1; i < v.size(); ++i) {
		int temp = v[i], j;
		for (j = i -1; j >=0 && v[j] > temp; --j){
            v[j+1] = v[j];
		}
		v[j+1] = temp;
	}
}

void print(vector<int>& v) {
    int len = v.size();
	for (int i = 0; i < len - 1; ++i) {
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
	insertionSort(v);
	print(v);
	return 0;
}
