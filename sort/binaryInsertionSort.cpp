#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;
int search(vector<int>& v, int beg, int end){
   int ans = end;
   int target = v[end];
   while(beg < end){
        int mid = (beg + end) >> 1;
        if(v[mid] > target){
            end = ans = mid;
        }
        else{
            beg = mid + 1;
        }
   }
   return ans;
}
void binaryInsertionSort(vector<int>& v) {
	for (int i = 1; i < v.size(); ++i) {
		int temp = v[i];
		int j = search(v, 0, i);
		for(int k = i; k > j; --k){
            v[k] = v[k-1];
		}
		v[j] = temp;
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
	binaryInsertionSort(v);
	print(v);
	return 0;
}