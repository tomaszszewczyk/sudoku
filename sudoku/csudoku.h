#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class sudoku
{
private:
	vector<vector<int> > pole;
	int zeroes;

public:
	sudoku() : pole(9, vector<int>(9, 0)), zeroes(0) {}
	sudoku(string dane);
	string view();
	bool solve();
	bool check();
	bool finished();
	int obvious(int, int);
};