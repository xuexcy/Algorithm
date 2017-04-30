#include<iostream>
#include<time.h>
#include<fstream>
#include<random>
#include<string>
#include<algorithm>
#include<vector>
#include<stdio.h>
using namespace std;

//create n numbers randomly and write into the file "fileName"
void generateData(string fileName, int n) {
	srand((int)time(0));
	if (ifstream(fileName)) {
		cout << "file \"" << fileName << "\" not exist" << endl;
		return;
	}
	ofstream out(fileName);
	for (int i = 0; i < n; ++i) {
        //in my computer, RAND_MAX = 32767
        //(-1073709056, 1073709056)
        //the probability of zero will be double than others
		out << (rand()%2 ? 1 : -1) * (rand()*32767 + rand()) << " ";
	}
	out.close();
	cout << "generate data completed" << endl;
}

//check whether the numbers in the file "fileName" is sorted
bool checkSorted(string fileName) {
	if (!ifstream(fileName)) {
		cout << "the file \"" << fileName << "\" doesn't exist" << endl;
		return false;
	}
	cout << "the numbers in " << fileName;
	ifstream in(fileName);
	int last, num;
	in >> last;
	while (in >> num) {
		if (last > num) {
			cout << " are not sorted" << endl;
			return false;
		}
		last = num;
	}
	cout << " are sorted" << endl;
	return true;
}


//seperate the numbers in the file "fileName" into
//n files, "0.txt", "1.txt", ... "n-1.txt" by (numbers % n)
//you can seperate these numbers by your own way
void seperateToFiles(string fileName, int n) {
    ifstream in(fileName);
	vector<ofstream> v(n);
    int num;

	for (int i = 0; i < n; ++i) {
		v[i].open(to_string(i) + ".txt");
	}
	while (in >> num) {
		v[(num%n+n)%n] << num << " ";
	}

	in.close();
	for (int i = 0; i < n; ++i) {
		v[i].close();
	}
	cout << "seperate completed" << endl;
}

//sort the numbers in the file "fileName" and write the result
//into the file "resultName" by n way merge using loser tree
void nWayMergeSort(string fileName, int n, string resultName) {
	if (!ifstream(fileName)) {
		cout << "file \"" << fileName << "\" doesn't exist" << endl;
		return;
	}
	if (ifstream(resultName)) {
		cout << "file \"" << resultName << "\" exists" << endl;
		return;
	}
	seperateToFiles(fileName, n);
	vector<ifstream> ifs(n);
    vector<ofstream> ofs(n);

	//sort the numbers in the files and write
	//the result into original file
	for (int i = 0; i < n; ++i) {
		ifs[i].open(to_string(i) + ".txt");
		int num;
		vector<int> nums;

		//read numbers from file to vector
		while (ifs[i] >> num) {
			nums.push_back(num);
		}
		ifs[i].close();

		sort(nums.begin(), nums.end());

		//write sorted numbers to file
		ofs[i].open(to_string(i) + ".txt");
		for (int j = 0; j < nums.size(); ++j) {
			ofs[i] << nums[j] << " ";
		}
		ofs[i].close();
	}

    cout << "seperated files sort completed" << endl;
	for (int i = 0; i < n; ++i) {
		ifs[i].open(to_string(i) + ".txt");
	}

	vector<int> loserTree(2*n - 1);
	vector<int> nums(n);
	for (int i = 0; i < n; ++i) {
		ifs[i] >> nums[i];
		loserTree[n - 1 + i] = i;
	}

	//init loser tree
	for (int i = n - 2; i >= 0; --i) {
		loserTree[i] = (nums[loserTree[2 * i + 1]] < nums[loserTree[2 * i + 2]] ?
			loserTree[2 * i + 1] : loserTree[2 * i + 2]);
	}

	ofstream out(resultName);
	while (nums[loserTree[0]] != INT_MAX) {
		out << nums[loserTree[0]] << " ";
		if (!(ifs[loserTree[0]] >> nums[loserTree[0]])) {
			nums[loserTree[0]] = INT_MAX;
		}
		//adjust loser tree
		int index = n - 1 + loserTree[0];
		while (index) {
			//get parent
			index = (index - 1) / 2;
			loserTree[index] = (nums[loserTree[2 * index + 1]] < nums[loserTree[2 * index + 2]] ?
				loserTree[2 * index + 1] : loserTree[2 * index + 2]);
		}
	}
	out.close();
	for (int i = 0; i < n; ++i) {
		ifs[i].close();
	}

    //delete i.txt
	/*for(int i = 0; i < n; ++i){
        remove((to_string(i) + ".txt").c_str());
	}*/
	cout << "sort completed" << endl;
}
int main() {
	//generateData("data.txt", 1000000000);
	//checkSorted("data.txt");
	//nWayMergeSort("data.txt", 500, "result.txt");
	//checkSorted("result.txt");

	generateData("dataTest.txt", 100000);
	checkSorted("dataTest.txt");
	nWayMergeSort("dataTest.txt", 100, "resultTest.txt");
	checkSorted("resultTest.txt");

	return 0;
}
