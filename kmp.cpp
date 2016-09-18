#include<iostream>
#include<vector>
using namespace std;
int kmp(string source, string target){
    int len1 = source.length();
    int len2 = target.length();
    if(len1 == 0){
        return -1;
    }
    else if(len2 == 0){
        return 0;
    }

    //get next array
    vector<int> next;
    next.push_back(-1);
    for(int i = 0; i < len2 - 1; ++i){
        int j = next[i];
        while(j != -1 && target[j] != target[i]){
            j = next[j];
        }
        next.push_back(j+1);
    }

    int i = 0, j = 0;
    while(len1 - i >= len2 - j){ // ensure the source has enough characters
        while(j < len2 && source[i] == target[j]){
            ++j;
            ++i;
        }
        if(j == len2){ //match successfully
            return i-len2;
        }
        else if(j == -1){ //move source to next character
            ++j;
            ++i;
        }
        else{
            j = next[j];
        }
    }
    return -1;
}

void print(string source, string target, int index){
    if(index == -1){
        cout << "no match" << endl;
    }
    else{
        cout << "source: " << source << endl;
        cout << "target: ";
        for(int i = 0; i < index; ++i){
            cout << " ";
        }
        cout << target << endl;
    }
}

int main(){
    string source = "abababcdacbababadbcabababadbdabbaababcbcbc";
    string target = "ababadbdabba";//next[] = {-1 0 0 1 2 3 0 0 0 1 2 0}  
    print(source, target, kmp(source, target));
}