// sudoku.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "csudoku.h"

using namespace std;

int main()
{
	cout << "Podaj sudoku:" << endl;
	string dane, wpis;
	while (dane.size() < 81)
	{
		cin >> wpis;
		dane += wpis;
	}

	sudoku test = sudoku(dane);
	time_t start = time(nullptr);
	cout << endl << "Podano: " << endl << test.view() << endl << endl << "Rozwiazywanie..." << endl;
	if (test.solve())
		cout << endl << test.view();
	else
		cout << endl << "Niepowodzenie" << endl;

	time_t koniec = time(nullptr);

	cout << endl << "Zakonczono w: " << (int)koniec - (int)start << " sekund." << endl;

	system("PAUSE");

    return 0;
}