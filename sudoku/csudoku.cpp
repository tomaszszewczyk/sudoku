#include "stdafx.h"
#include "csudoku.h"

sudoku::sudoku(string dane)
	: pole(9, vector<int>(9, 0))
{
	zeroes = 0;
	if (dane.size() != 81)
	{
		cout << "Data input error" << endl;
		return;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			pole[i][x] = tomek::ctoi(dane[i * 9 + x]);
			if (pole[i][x] == 0)
				zeroes++;
		}
	}
	
	return;
	}
	

string sudoku::view()
{
	string output;
	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
			output += tomek::itoc(pole[i][x]);
		output += '\n';
	}
	return output;
}

bool sudoku::finished()
{
	for(int i = 0; i < 9; i++)
		for (int x = 0; x < 9; x++)
			if (pole[i][x] == 0)
				return false;
	return true;
}

int sudoku::obvious(int wiersz, int kolumna)
{
	//check row
	vector<bool> liczby = vector<bool>(10, false);
	for (int x = 0; x < 9; x++)
		liczby[pole[wiersz][x]] = true;
	//check column
	for (int x = 0; x < 9; x++)
		liczby[pole[x][kolumna]] = true;
	//chceck box
	int a, b;
	a = wiersz / 3;
	b = kolumna / 3;
	for (int i = 0; i < 3; i++)
		for (int x = 0; x < 3; x++)
			liczby[pole[a * 3 + i][b * 3 + x]] = true;

	int wynik = 0;
	for (int i = 1; i < 10; i++)
	{
		if (liczby[i] == false && wynik == 0)
			wynik = i;
		else if (liczby[i] == false && wynik != 0)
			return -1;
	}
	if (wynik == 0)
		return -1;
	else
		return wynik;
}

bool sudoku::solve()
{
	//Nowa metoda
	//W pêtli nieskonczonej sprawdzaj po pokolei czy jest oczywista odpowiedz
	//Jesli nic nie znalazles dodaj w pierwszym miejscu liczbe i wywolaj siebie
	if (!check())
		return false;
	
	int iteracje = 0;
	static int wywolania = 0;
	wywolania++;
	cout << endl << "Numer wywolania solve(): " << wywolania << endl;
	bool nic;
	while (!finished())
	{
		nic = true;
		cout << "Iteracja nr: " << ++iteracje << endl;
		for (int i = 0; i < 9; i++)
			for (int x = 0; x < 9; x++)
			{
				if (pole[i][x] == 0)
				{
					int wartosc = obvious(i, x);
					if (wartosc != -1)
					{
						pole[i][x] = wartosc;
						nic = false;
					}
				}
			}
		if (nic == true)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int x = 0; x < 9; x++)
				{
					if (pole[i][x] == 0)
					{
						vector<vector<int>> backup;
						for (int a = 0; a < 9; a++)
						{
							pole[i][x] = a + 1;
							backup = pole;
							if (solve())
								return true;
							else
								pole = backup;
						}
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool sudoku::check()
{
	//check rows
	for (int i = 0; i < 9; i++)
	{
		vector<bool> liczby = vector<bool>(10, false);
		for (int x = 0; x < 9; x++)
		{
			if (pole[i][x] != 0)
			{
				if (liczby[pole[i][x]] == false)
					liczby[pole[i][x]] = true;
				else
				{
					//cout << "Blad w wierszu. Powtorzenie " << pole[i][x] << " w miejscu [" << i << "] [" << x << endl;
					return false;
				}
			}
		}
	}
	//check colums
	for (int i = 0; i < 9; i++)
	{
		vector<bool> liczby = vector<bool>(10, false);
		for (int x = 0; x < 9; x++)
		{
			if (pole[x][i] != 0)
			{
				if (liczby[pole[x][i]] == false)
					liczby[pole[x][i]] = true;
				else
				{
					//cout << "Blad w kolumnie. Powtorzenie " << pole[x][i] << " w miejscu [" << x << "] [" << i << endl;
					return false;
				}
			}
		}
	}
	//check box
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			for (int i = 0; i < 3; i++)
			{
				vector<bool> liczby = vector<bool>(10, false);
				for (int x = 0; x < 3; x++)
				{
					if (pole[i + 3 * a][x + 3 * b] != 0)
					{
						if (liczby[pole[i + 3 * a][x + 3 * b]] == false)
							liczby[pole[i + 3 * a][x + 3 * b]] = true;
						else
						{
							//cout << "Blad w box [" << a << "] [" << b << "]. Powtorzenie " << pole[i + 3*a][x + 3*b] << " w miejscu [" << i << "] [" << x << endl;
							return false;
						}

					}
				}
			}
		}
	}
	return true;
}