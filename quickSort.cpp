#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

void quickSort(vector<int>& v, int beg, int end) {
    if(end - beg <= 1){
        return;
    }
    int temp = beg + (rand() % (end - beg));
    swap(v[temp], v[beg]);
    int l = beg + 1, r = end - 1;
    while(l <= r){
        while(l <= r && v[l] <= v[beg]) ++l;
        while(l <= r && v[r] > v[beg]) --r;
        if(l < r){
            swap(v[l], v[r]);
        }
    }
    swap(v[beg], v[r]);
    quickSort(v, beg, r);
    quickSort(v, r+1, end);
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
	for (int i = 0; i < 10; ++i) {
		v.push_back(rand()%100);
	}
	print(v);
	quickSort(v, 0, v.size());
	print(v);
	return 0;
}
