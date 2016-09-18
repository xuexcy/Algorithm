#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>

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

void shellSort(vector<int>& v, int gap) {
    if(v.empty() || gap == 0){
        return ;
    }
    gap = min(gap, (int)v.size()/2);
    for(int i = 0; i < gap; ++i){
        //you can do the insertion sort on the vector
        // v, instead of using the insertion sort function
        vector<int> temp;
        for(int j = i; j < v.size(); j += gap){
            temp.push_back(v[j]);
        }
        insertionSort(temp);
        for(int j = 0; j < temp.size(); ++j){
            v[i+j*gap] = temp[j];
        }
    }
    shellSort(v, gap/2);
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
	shellSort(v, 5);
	print(v);
	return 0;
}
