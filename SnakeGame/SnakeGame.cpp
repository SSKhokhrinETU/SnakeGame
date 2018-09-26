#include "pch.h"
#include <iostream>
#include <conio.h>

using namespace std;

int playingGame()
{
	return 0;
}

int editingMap()
{
	return 0;
}

int tutorial()
{
	return 0;
}

int menu()
{
	short int menuСhooser = 0;
	system("cls");
	cout << "1 — Play Game" << '\n' << "2 — Edit Map" << '\n' << "3 — Tutorial" << '\n' << "4 — Exit" << endl;
	cin >> menuСhooser;
	switch (menuСhooser)
	{
	case 1:
		playingGame();
		break;
	case 2:
		editingMap();
		break;
	case 3:
		tutorial();
		break;
	case 4: return 4;
		break;
	}
}

int main()
{
	while (_getch() != 27)
	{
		if (menu() == 4)
			break;
		system("cls");
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
