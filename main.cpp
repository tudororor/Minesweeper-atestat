#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

int a[100][100], bombs, difficulty, n;
bool game;

///0 -> nimic
///1-8 -> bombe pe langa
///9 -> bomba
///10 -> nimic descoperit
///11-18 -> bombe pe langa descoperite
///19 -> bomba apasata
///20 steag
///21-28 steag pe numar
///29-steag pe bomba


bool checkLimit(int i, int j)
{
	if (i >= 1 && i <= n && j >= 1 && j <= n)
	{
		return 1;
	}
	return 0;
}

void incrementare(int i, int j)
{
	if (a[i][j] != 9 && checkLimit(i, j))
	{
			a[i][j]++;
	}
}

void generare()
{
	srand(time(0));
	int i, j, k = 0;
	game = 1;
	switch (difficulty)
	{
	case 1:
		n = 8;
		bombs = 10;
		break;
	case 2:
		n = 16;
		bombs = 40;
		break;
	case 3:
		n = 24;
		bombs = 99;
		break;
	default:
		break;
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			a[i][j] = 0;
	while (k < bombs)
	{
		i = rand() % n + 1;
		j = rand() % n + 1;
		if (a[i][j] == 0)
		{
			a[i][j] = 9;
			k++;
		}
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			if (a[i][j] == 9)
			{
				incrementare(i - 1, j - 1);
				incrementare(i - 1, j);
				incrementare(i - 1, j + 1);
				incrementare(i, j - 1);
				incrementare(i, j + 1);
				incrementare(i + 1, j - 1);
				incrementare(i + 1, j);
				incrementare(i + 1, j + 1);
			}
		}
}

void show()
{
	int i, j;
	system("CLS");
	cout << "    ";
	for(i = 1; i <= n; i++)
        cout << i << "   ";
    cout << endl;
    cout << "  ";
	for (i = 1; i <= n; i++)
		cout << "----";
	cout << '-' << endl;
	for (i = 1; i <= n; i++)
	{
		cout << i << ' ';
		cout << '|';
		for (j = 1; j <= n; j++)
		{
			if (a[i][j] <= 9)
			{
				cout << "   ";
			}
			else if (a[i][j] <= 18)
			{
				cout << ' ' << a[i][j] - 10 << ' ';
			}
			else if (a[i][j] == 19)
			{
				cout << " * ";
			}
			else if (a[i][j] >= 20)
			{
				cout << " s ";
			}
			cout << '|';
		}
		cout << endl;
		cout << "  ";
		for (int m = 1; m <= n; m++)
			cout << "----";
		cout << '-' << endl;
	}
}

void expand(int i, int j)
{
	int cnt = 0;
	if (checkLimit(i, j))
	{
		if (a[i][j] == 0)
		{
			a[i][j] = 10;
			if (checkLimit(i - 1, j - 1)) expand(i - 1, j - 1);
			if (checkLimit(i - 1, j)) expand(i - 1, j);
			if (checkLimit(i - 1, j + 1)) expand(i - 1, j + 1);
			if (checkLimit(i, j - 1)) expand(i, j - 1);
			if (checkLimit(i, j + 1)) expand(i, j + 1);
			if (checkLimit(i + 1, j - 1)) expand(i + 1, j - 1);
			if (checkLimit(i + 1, j)) expand(i + 1, j);
			if (checkLimit(i + 1, j + 1)) expand(i + 1, j + 1);
		}
		else if (a[i][j] <= 8)
		{
			a[i][j] = a[i][j] + 10;
		}
		else if (a[i][j] == 9)
		{
			a[i][j] = 19;
			game = 0;
		}
		else if (a[i][j] <= 18 && a[i][j] > 10)
		{
			if (a[i - 1][j] >= 20 && checkLimit(i - 1, j)) cnt++;
			if (a[i - 1][j + 1] >= 20 && checkLimit(i - 1, j + 1)) cnt++;
			if (a[i - 1][j - 1] >= 20 && checkLimit(i - 1, j - 1)) cnt++;
			if (a[i][j - 1] >= 20 && checkLimit(i, j - 1)) cnt++;
			if (a[i][j + 1] >= 20 && checkLimit(i, j + 1)) cnt++;
			if (a[i + 1][j] >= 20 && checkLimit(i + 1, j)) cnt++;
			if (a[i + 1][j + 1] >= 20 && checkLimit(i + 1, j + 1)) cnt++;
			if (a[i + 1][j - 1] >= 20 && checkLimit(i + 1, j - 1)) cnt++;
			if (cnt == a[i][j] % 10)
			{
				if (checkLimit(i - 1, j - 1) && a[i - 1][j - 1] <= 9)
				{
					expand(i - 1, j - 1);
				}
				if (checkLimit(i - 1, j) && a[i - 1][j] <= 9)
				{
					expand(i - 1, j);
				}
				if (checkLimit(i - 1, j - 1) && a[i - 1][j + 1] <= 9)
				{
					expand(i - 1, j + 1);
				}
				if (checkLimit(i, j - 1) && a[i][j - 1] <= 9)
				{
					expand(i, j - 1);
				}
				if (checkLimit(i, j + 1) && a[i][j + 1] <= 9)
				{
					expand(i, j + 1);
				}
				if (checkLimit(i + 1, j - 1) && a[i + 1][j - 1] <= 9)
				{
					expand(i + 1, j - 1);
				}
				if (checkLimit(i + 1, j) && a[i + 1][j] <= 9)
				{
					expand(i + 1, j);
				}
				if (checkLimit(i + 1, j + 1) && a[i + 1][j + 1] <= 9)
				{
					expand(i + 1, j + 1);
				}
			}
		}
	}
}

void input()
{
	char z[100];
	int i, j;
	cout << endl << "Alege tipul de mutare(s -> steag / v -> verificare), dupa care apasa enter." << endl;
	cout << "Mutare: "; cin >> z;
	cout << "Introdu coordonatele, dupa care apasa enter" << endl;
	cout << "Coordonate: "; cin >> i >> j;
	if (checkLimit(i, j))
	{
		if (strcmp(z, "v") == 0)
		{
			if (a[i][j] <= 18)
			{
				expand(i, j);
			}
		}
		else if (strcmp(z, "s") == 0)
		{
			if (a[i][j] <= 9)
			{
				a[i][j] = a[i][j] + 20;
			}
			else if (a[i][j] >= 20)
			{
				a[i][j] = a[i][j] - 20;
			}
		}
	}
}

int main()
{
	cin >> difficulty;
	generare();
	do
	{
		show();
		input();
	}while (game > 0);
	show();
	if(game >= 1)
    {
        cout << endl << endl << "Ai castigat!" << endl;
    }
    else
    {
        cout << endl << endl << "Ai pierdut!" << endl;
    }
	system("pause");
	return 0;
}
