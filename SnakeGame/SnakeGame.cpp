#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool endOfGame = false;

const short int FOOD_CELL = 1;
const short int BLOCK_CELL = 2;
int score = 0;

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; 
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void intro()
{
	setlocale(LC_ALL, "Russian");
	gotoxy(35, 10);
	cout << "##### #   # #####    #### #   #  ###  #   # #####";
	gotoxy(35, 11);
	cout << "  #   #   # #       #     ##  # #   # #  #  #";
	gotoxy(35, 12);
	cout << "  #   ##### ###      ###  # # # ##### ###   ###";
	gotoxy(35, 13);
	cout << "  #   #   # #           # #  ## #   # #  #  #";
	gotoxy(35, 14);
	cout << "  #   #   # #           # #  ## #   # #   # #";
	gotoxy(35, 15);
	cout << "  #   #   # #####   ####  #   # #   # #   # #####";
	gotoxy(70, 20);
	cout << "\x22Не для тупых - сойдёт\x22";
	gotoxy(82, 21);
	cout << "Лиана Хулиана";
	gotoxy(0, 29);
	Sleep(2000);
}

void printEditingField(short int(&field)[21][21])
{
	cout << '\xC9';
	for (int i = 0; i < 21; i++)
		cout << '\xCD';
	cout << "\xBB\n";
	for (int i = 0; i < 21; i++)
	{
		cout << '\xBA';
		for (int j = 0; j < 21; j++)
		{
			switch (field[i][j])
			{
			case 0:
				cout << " ";
				break;
			case 1:
				cout << "\xFD";
				break;
			case 2:
				cout << "\xB2";
				break;
			default:
				cout << "T";
			}
		}
		cout << "\xBA\n";
	}
	cout << '\xC8';
	for (int i = 0; i < 21; i++)
		cout << '\xCD';
	cout << '\xBC';

	gotoxy(48, 9);
	cout << "Map Editor";
	gotoxy(40, 10);
	cout << "Space - Put/break the wall";
	gotoxy(40, 11);
	cout << "Enter - Play";
	gotoxy(0, 29);
}

void printField(short int (&field)[21][21])
{
	cout << '\xC9';
	for (int i = 0; i < 21; i++)
		cout << '\xCD'; 
	cout << "\xBB\n";
	for (int i = 0; i < 21; i++)
	{
		cout << '\xBA';
		for (int j = 0; j < 21; j++)
		{
			switch (field[i][j])
			{
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "F";
					break;
				case 2:
					cout << "\xB2";
					break;
				default:
					cout << "O";
			}
		}
		cout << "\xBA\n";
	}
	cout << '\xC8';
	for (int i = 0; i < 21; i++)
		cout << '\xCD';
	cout << '\xBC';
}

void newFood(short int (&map)[21][21])
{
	short int newFoodX = 0, newFoodY = 0;
	bool done = false;;
	while (!done)
	{
		newFoodX = rand() % 21;
		newFoodY = rand() % 21;
		if (map[newFoodY][newFoodX] == 0)
		{
			map[newFoodY][newFoodX] = FOOD_CELL;
			done  = true;
		}
	}
}

void snake(short int(&matrix)[21][21], char destination)
{
	short int headX = 0, headY = 0, headFinder = 3;
	short int tailX = 0, tailY = 0, tailFinder = 500;
	short int foodCounter = 0;

	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			if (matrix[i][j] > headFinder)
			{
				headX = j;
				headY = i;
				headFinder = matrix[i][j];
			}
			else if ((matrix[i][j] < tailFinder) && (matrix[i][j] > BLOCK_CELL))
			{
				tailX = j;
				tailY = i;
				tailFinder = matrix[i][j];
			}


	switch (destination)
	{
		case 72:
			if ((matrix[headY - 1][headX] != 0) && (matrix[headY - 1][headX] != FOOD_CELL))
				endOfGame = true;
			else if (matrix[headY - 1][headX] == FOOD_CELL)
			{
				matrix[headY - 1][headX] = matrix[headY][headX] + 1;
				score++;
				break;
			}
			else
			{
				matrix[headY - 1][headX] = matrix[headY][headX] + 1;
				for (int i = 0; i < 21; i++)
				{
					for (int j = 0; j < 21; j++)
					{
						if (matrix[i][j] > 3)
							matrix[i][j]--;
					}
				}
			}
			matrix[tailY][tailX] = 0;
			break;
		case 77:
			if ((matrix[headY][headX + 1] != 0) && (matrix[headY][headX + 1] != FOOD_CELL))
				endOfGame = true;
			else if (matrix[headY][headX + 1] == FOOD_CELL)
			{
				matrix[headY][headX + 1] = matrix[headY][headX] + 1;
				score++;
				break;
			}
			else
			{
				matrix[headY][headX + 1] = matrix[headY][headX] + 1;
				for (int i = 0; i < 21; i++)
				{
					for (int j = 0; j < 21; j++)
					{
						if (matrix[i][j] > 3)
							matrix[i][j]--;
					}
				}
			}
			matrix[tailY][tailX] = 0;
			break;
		case 80:
			if ((matrix[headY + 1][headX] != 0) && (matrix[headY + 1][headX] != FOOD_CELL))
				endOfGame = true;
			else if (matrix[headY + 1][headX] == FOOD_CELL)
			{
				matrix[headY + 1][headX] = matrix[headY][headX] + 1;
				score++;
				break;
			}
			else
			{
				matrix[headY + 1][headX] = matrix[headY][headX] + 1;
				for (int i = 0; i < 21; i++)
				{
					for (int j = 0; j < 21; j++)
					{
						if (matrix[i][j] > 3)
							matrix[i][j]--;
					}
				}
			}
			matrix[tailY][tailX] = 0;
			break;
		case 75:
			if ((matrix[headY][headX - 1] != 0) && (matrix[headY][headX - 1] != FOOD_CELL))
				endOfGame = true;
			else if (matrix[headY][headX - 1] == FOOD_CELL)
			{
				matrix[headY][headX - 1] = matrix[headY][headX] + 1;
				score++;
				break;
			}
			else
			{
				matrix[headY][headX - 1] = matrix[headY][headX] + 1;
				for (int i = 0; i < 21; i++)
				{
					for (int j = 0; j < 21; j++)
					{
						if (matrix[i][j] > 3)
							matrix[i][j]--;
					}
				}
			}
			matrix[tailY][tailX] = 0;
			break;
	}
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (matrix[i][j] == FOOD_CELL)
				foodCounter++;
		}
	}
	if (foodCounter < 5)
		newFood(matrix);

}

void outro()
{
	system("cls");
	gotoxy(35, 10);
		cout << " ###    ###  #   # #####    ###  #   # ##### ####";
	gotoxy(35, 11);
		cout << "#   #  #   # ## ## #       #   # #   # #     #   #";
	gotoxy(35, 12);
		cout << "#      ##### # # # ####    #   # #   # ####  ####";
	gotoxy(35, 13);
		cout << "#   ## #   # #   # #       #   #  # #  #     #   #";
	gotoxy(35, 14);
		cout << "#    # #   # #   # #       #   #  # #  #     #   #";
	gotoxy(35, 15);
		cout << " ###   #   # #   # #####    ###    #   ##### #   #";
	gotoxy(52, 19);
	cout << "Your score: " << score;
	gotoxy(39, 21);
}

int main()
{	
	short int field[21][21] = {0};
	short int ptrX = 0, ptrY = 0;
	int headPtrX = 0;
	int headPtrY = 0;
	char ch = 0, tempChoose = 0;
	bool done = false;

	intro();
	setlocale(LC_ALL, "C");

	while (done == false)
	{
		system("cls");
		printEditingField(field);
		gotoxy((1 + ptrX), (1 + ptrY));
		printf("%1c", 194);
		gotoxy(0, 25);
		do
		{
			ch = _getch();
			if (ch == -32)
				tempChoose = _getch();
		} while ((ch != -32) && (ch != 13) && (ch != 32));
		done = false;
		if (ch == 32)
		{
			if (field[ptrY][ptrX] == 0)
			{
				field[ptrY][ptrX] = BLOCK_CELL;
				
			}
			else 
				field[ptrY][ptrX] = 0;
		}
		if (ch == 13)
			done = true;
		else {
			
			switch (tempChoose)
			{
			case 72:			//up
				if (ptrY > 0)
					ptrY--;
				break;
			case 80:			//down
				if (ptrY < 20)
					ptrY++;
				break;
			case 75:			//left
				if (ptrX > 0)
					ptrX--;
				break;
			case 77:			//right
				if (ptrX < 20)
					ptrX++;
				break;
			}
		}
		
		ch = 0;
	}

	for (int i = 0; i < 21; i++)
		field[i][0] = field[i][20] = field[0][i]=field[20][i] = BLOCK_CELL;
	

	field[9][10] = 3;
	field[10][10] = 4;
	field[11][10] = 5;

	for (int i = 0; i < 5; i++)
		newFood(field);
	printField(field);
	while ((ch != 27) && !endOfGame)
	{
		system("cls");
		printField(field);
		ch = _getch();
		if (ch == 224)
			ch = _getch();
		snake(field, ch);
	}

	outro();
	system("pause");

	return 0;
}
