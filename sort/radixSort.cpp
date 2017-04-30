#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<math.h>
using namespace std;

void radixSort1(vector<int>& v, int index) {
    if(index == -1){
        return ;
    }
    int p = pow(10, index);
    vector<vector<int>> temp(10);
    for(int i = 0; i < v.size(); ++i){
        temp[v[i]/p%10].push_back(v[i]);
    }
    --index;
    int t = 0;
    for(int i = 0; i < 10; ++i){
        radixSort1(temp[i], index);
        for(int j = 0; j < temp[i].size(); ++j){
            v[t++] = temp[i][j];
        }
    }
}

void radixSort2(vector<int>& v, int index, int len) {
    if(index == len){
        return ;
    }
    int p = pow(10, index);
    vector<vector<int>> temp(10);
    for(int i = 0; i < v.size(); ++i){
        temp[v[i]/p%10].push_back(v[i]);
    }
    int t = 0;
    for(int i = 0; i < temp.size(); ++i){
        for(int j = 0; j < temp[i].size(); ++j){
            v[t++] = temp[i][j];
        }
    }
    radixSort2(v, index+1, len);
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
	radixSort1(v, 1);
	print(v);

	vector<int> v2;
	for (int i = 0; i < 20; ++i) {
		v2.push_back(rand()%100);
	}
	print(v2);
	radixSort2(v2, 0, 2);
	print(v2);

	return 0;
}
