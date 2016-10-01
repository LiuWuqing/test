// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Queen { //皇后类
	int x, y; //皇后在棋盘上的位置坐标
	Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
	bool operator== (Queen const& q) const { //重载判等操作符，以检测不同皇后之间可能的冲突
	       return    (x == q.x) //行冲突（这一情况其实并不会发生，可省略）
				|| (y == q.y) //列冲突
				|| (x + y == q.x + q.y) //沿正对角线冲突
				|| (x - y == q.x - q.y); //沿反对角线冲突
	}
   bool operator!= (Queen const& q) const { return !(*this == q); } //重载不等操作符
};

void printsolus(const vector<vector<int>> &solus, int N)
{
	cout << "[" << endl;
	for (int k = 0; k < solus.size(); ++k) {//输出所有解
		auto solu = solus.at(k);
		cout << "\t" << "[";
		//输出解的每一行
		for (int j = 0; j < solu.size();++j) {
			int y = solu.at(j);
			if(j != 0)
				cout << "\t ";
			cout << "\"";
			for (int i = 0; i < N; ++i) {
				if (i == y)
					cout << "Q";
				else
					cout << '.';
			}
			cout << "\"";
			if (j != N - 1 && j != 0)
				cout << "," << endl;
			if (j == 0)
				cout << ',' << " "<< "// Solution" << k + 1 << endl;
		}
		if (k != solus.size() - 1)
			cout << ']' << ',' << endl << endl;
		else
			cout << ']' << endl;
	}
	cout << "]" << endl;
}

vector<vector<string>> printstring(const vector<vector<int>> &solus, int N)
{
	vector<vector<string>> ret;
	for (int k = 0; k < solus.size(); ++k) {//输出所有解
		auto solu = solus.at(k);
		vector<string> vecstr;
		for (int j = 0; j < solu.size(); ++j) {
			int y = solu.at(j);
			string str;
			for (int i = 0; i < N; ++i) {
				if (i == y)
					str.push_back('Q');
				else
					str.push_back('.'); 
			}
			vecstr.push_back(str);
		}
		ret.push_back(vecstr);
	}
	return ret;
}

void placeQueen(int N)
{
	vector<Queen> solu;
	vector<vector<int>> solus;
	Queen q(0, 0);
	do {
		if (q.y >= N || N <= solu.size()) {//越界
			q = *(solu.end() - 1);
			solu.pop_back();
			q.y++;
		}
		while (q.y < N && find(solu.begin(), solu.end(), q) != solu.end()) {
			q.y++;
		}
		if (q.y < N) {
			solu.push_back(q);
			if (solu.size() >= N) {//部分解已成为全局解
				vector<int> soluY;
				for (auto qu : solu)
					soluY.push_back(qu.y);
				solus.push_back(soluY);
			}
			q.x++;
			q.y = 0;
		}
	} while (0 < q.x || q.y < N);
 	printsolus(solus, N);
}

int main()
{
	int n(0);
	cin >> n;
	placeQueen(n);
 	return 0; 
}

