// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Queen { //�ʺ���
	int x, y; //�ʺ��������ϵ�λ������
	Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
	bool operator== (Queen const& q) const { //�����еȲ��������Լ�ⲻͬ�ʺ�֮����ܵĳ�ͻ
	       return    (x == q.x) //�г�ͻ����һ�����ʵ�����ᷢ������ʡ�ԣ�
				|| (y == q.y) //�г�ͻ
				|| (x + y == q.x + q.y) //�����Խ��߳�ͻ
				|| (x - y == q.x - q.y); //�ط��Խ��߳�ͻ
	}
   bool operator!= (Queen const& q) const { return !(*this == q); } //���ز��Ȳ�����
};

void printsolus(const vector<vector<int>> &solus, int N)
{
	cout << "[" << endl;
	for (int k = 0; k < solus.size(); ++k) {//������н�
		auto solu = solus.at(k);
		cout << "\t" << "[";
		//������ÿһ��
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
	for (int k = 0; k < solus.size(); ++k) {//������н�
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
		if (q.y >= N || N <= solu.size()) {//Խ��
			q = *(solu.end() - 1);
			solu.pop_back();
			q.y++;
		}
		while (q.y < N && find(solu.begin(), solu.end(), q) != solu.end()) {
			q.y++;
		}
		if (q.y < N) {
			solu.push_back(q);
			if (solu.size() >= N) {//���ֽ��ѳ�Ϊȫ�ֽ�
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

