#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

void mergeSort(vector<int>& v, int beg, int end) {
    if(end - beg <= 1){
        return;
    }
    int mid = (beg + end) >> 1;
    mergeSort(v, beg, mid);
    mergeSort(v, mid, end);
    vector<int> temp;
    int i = beg, j = mid;
    while(i < mid && j < end){
        temp.push_back(v[i] < v[j] ? v[i++] : v[j++]);
    }
    while(i < mid){
        temp.push_back(v[i++]);
    }
    while(j < end){
        temp.push_back(v[j++]);
    }
    copy(temp.begin(), temp.end(), v.begin()+beg);
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
	mergeSort(v, 0, v.size());
	print(v);
	return 0;
}
