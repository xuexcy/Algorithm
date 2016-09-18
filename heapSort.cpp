#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>

using namespace std;

void heapAdjust(vector<int>& v, int pos, int maxIndex){
    //do not consider the node which its index >= maxIndex
    //minLeaf is the first leaf
	int minLeaf = maxIndex / 2;
	while(pos < minLeaf){
		if(pos * 2 + 2 < maxIndex){
			if(v[pos] >= v[pos*2 + 1] && v[pos] >= v[pos*2+2]){
				return;
			}
			int temp = (v[pos*2 + 1] > v[pos*2+2] ? pos*2+1 : pos*2+2);
			swap(v[pos], v[temp]);
			pos = temp;
		}
		else if(v[pos] < v[pos*2+1]){
			swap(v[pos], v[pos*2+1]);
			pos = pos * 2 + 1;
		}
		else{
            break;
		}
	}
}

void heapSort(vector<int>& v) {
	if(v.empty()){
		return ;
	}

	//make a max heap
	//i : the index of the last inner node;
	for(int i =  v.size() / 2 - 1; i >= 0; --i){
		heapAdjust(v, i, v.size());
	}
	
	for(int i = v.size()-1; i > 0; --i){
		swap(v[0], v[i]);
		heapAdjust(v, 0, i);
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
	heapSort(v);
	print(v);
	return 0;
}
