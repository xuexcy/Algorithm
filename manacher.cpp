#include<iostream>
#include<vector>

using namespace std;

pair<int,int> manacher(string str) {
    //add * to the string
    //"abc" -> "*a*b*c*"
    string s = "*";
    for(const auto& ch : str){
        s = s + ch + "*";
    }
    int len =s.length();

    int pMiddle = 0, pRight = 0;
    vector<int> v;
    for(int i = 0; i < len; ++i){
        if(i < pRight && i + v[2*pMiddle-i] < pRight){
            v.push_back(v[2*pMiddle-i]);
        }
        else{
            ++pRight;
            while(pRight < len && 2 * i - pRight >= 0 && s[2*i-pRight] == s[pRight]){
                ++pRight;
            }
            --pRight;
            v.push_back(pRight - i);
            pMiddle = i;
        }
    }
    pair<int,int> p; //index, length
    p.first = 0;
    for(int i = 1; i < len; ++i){
        if(v[p.first] < v[i]){
            p.first = i;
        }
    }
    p.second = v[p.first];
    p.first = (p.first-p.second)/2;
    return p;
}

void print(string s, pair<int,int> p) {
    cout << "source     : " << s << endl;
    cout << "plalindrome: ";
    for(int i = 0; i < p.first; ++i){
        cout << " ";
    }
    cout << s.substr(p.first, p.second) << endl;
}
int main() {
	string s = "waabwswfd";
    print(s, manacher(s));
	return 0;
}
