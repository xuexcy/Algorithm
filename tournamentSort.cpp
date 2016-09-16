#include<iostream>
#include<vector>
#include<random>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<limits.h>
using namespace std;

void tournamentSort(vector<int>& v) {
    vector<int> temp(2*v.size()-1);
    vector<int> ans;

    //add index of num to leaf node;
    for(int i = 0; i < v.size(); ++i){
        temp[v.size()-1+i] = i;
    }

    //loser/winner tree
    for(int i = v.size()-2; i >= 0; --i){
        temp[i] = (v[temp[2*i+1]] < v[temp[2*i+2]] ? temp[2*i+1] : temp[2*i+2]);
    }

    ans.push_back(v[temp[0]]);// loser
    v[temp[0]] = INT_MAX;
    for(int i = 0; i < v.size()-1; ++i){
        int pos = v.size() - 1 + temp[0];
        while(pos){
            pos = (pos - 1) / 2;
            temp[pos] = (v[temp[pos*2+1]] < v[temp[pos*2+2]] ? temp[pos*2+1] : temp[pos*2+2]);
        }
        ans.push_back(v[temp[0]]);
        v[temp[0]] = INT_MAX;
    }
    copy(ans.begin(), ans.end(), v.begin());
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
	tournamentSort(v);
	print(v);
	return 0;
}
