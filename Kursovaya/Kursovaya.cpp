#include "pch.h"
#include "Sea_Battle.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <random>

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77


void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

int ** set_0(int **array) {
	for (int i = 0; i < 10; i++) {
		array[i] = new int[10];
		for (int j = 0; j < 10; j++) { array[i][j] = 0; } //собственно, поля
	}
	return array;
}

void simple_vivod (int **array, const char alphabet[10], int i) {
	for (int j = 0; j < 12; j++) {
		if (i == 0 && j >= 2) { cout << alphabet[j - 2] << " ";  }
		else if (i == 1) { break; }
		else if ((i > 1 && j == 1) || (i == 0 && j < 2)) { cout << "  "; }
		else if ( i > 1 && j == 0) { 
			if (i-1 != 10) {cout << i - 1 << " ";}
			else { cout << i - 1; }	
		}
		else {
			switch (array[i-2][j-2]) {
			case 0:
				cout << ". ";
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				cout << array[i-2][j-2] << " ";
				break;
			case -1:
				cout << "o "; 
				break;
			case (-2):
				cout << "x ";
				break;
			}
		}
	}
}

void vivod(int **array_1, int **array_2, const char alphabet[10]) {
	cout << endl; //отступ от границы сверху
	for (int i = 0; i < 12; i++) {
		cout << "        "; //отступ от границы слева 
		simple_vivod(array_1, alphabet, i);
		cout << "           ";
		simple_vivod(array_2, alphabet, i);
		cout << endl;
	}
	cout << endl << endl << endl; //отступ снизу
}


int ** arrangement_player(int **array, const char alphabet[10]) {
	int ships[4] = { 1, 2, 3, 4 };
	int ship_length = 0;
	int ship_count = 0;
	int number = 0;
	int number_letter = 0;
	char letter;

	cout << endl;
	for (int i = 0; i < 12; i++) {
		cout << "                        "; //отступ от границы слева 
		simple_vivod(array, alphabet, i);
		cout << endl;
	}
	cout << endl << endl << endl;
	cout << "     Это режим расстановки ваших кораблей." << endl;
	cout << "     Введите точку (например, D4), где хотите поставить 'голову' корабля, " << endl;
	cout << "     а затем укажите стрелочкой направление тела корабля." << endl << endl;

	while (true) {
		if (ships[ship_count] == 0) {
			ship_count += 1;
		}

		if (ships[ship_count] > 0) {
			switch (ship_count) {
			case 0: 
				ship_length = 4;
				setCursorPosition(0, 20);
				cout << "                                                                ";
				setCursorPosition(0, 20);
				cout << "     Сейчас расположите линкор: ";
				break;
			case 1:
				ship_length = 3;
				setCursorPosition(0, 20);
				cout << "                                                                ";
				setCursorPosition(0, 20);
				cout << "     Сейчас расположите крейсер: ";
				break;
			case 2:
				ship_length = 2;
				setCursorPosition(0, 20);
				cout << "                                                                ";
				setCursorPosition(0, 20);
				cout << "     Сейчас расположите эсминец: ";
				break;
			case 3:
				ship_length = 1;
				setCursorPosition(0, 20);
				cout << "                                                                ";
				setCursorPosition(0, 20);
				cout << "     Сейчас расположите катер: ";
				break;
			}
			ships[ship_count] -= 1;	
		}

		cin >> letter >> number;
		number -= 1;
		number_letter = letter - 'A'; 
		array[number][number_letter] = ship_length; //закидываем в массив нашего поля голову корабля

		setCursorPosition(28 + number_letter*2, 3+number); //*2 учитывает пробелы в выводимом массиве
		cout << array[number][number_letter];

		if (ship_length != 1) {
			setCursorPosition(0, 20);
			cout << "     Теперь введите направление расположения корабля стрелкой : ";
			int KeyStroke;
			KeyStroke = _getch();

			if (KeyStroke == 224)
			{
				KeyStroke = _getch(); // Even though there are 2 getch() it reads one keystroke
				switch (KeyStroke)
				{
				case UP_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number - i][number_letter] = ship_length;
						setCursorPosition(28 + number_letter * 2, 3 + number - i);
						cout << array[number - i][number_letter];
					}
					break;
				case DOWN_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number + i][number_letter] = ship_length;
						setCursorPosition(28 + number_letter * 2, 3 + number + i);
						cout << array[number + i][number_letter];
					}
					break;
				case LEFT_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number][number_letter - i] = ship_length;
						setCursorPosition(28 + number_letter * 2 - 2 * i, 3 + number);
						cout<< array[number][number_letter - i];
					}
					break;
				case RIGHT_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number][number_letter + i] = ship_length;
						setCursorPosition(28 + number_letter * 2 + 2 * i, 3 + number);
						cout << array[number][number_letter + i];
					}
					break;
				default:
					cout << "Some other key." << endl;
				}
			}
			else cout << KeyStroke << endl;
		}
		
		if (ships[ship_count] == 0 && ship_count == 3) {
			setCursorPosition(0, 20);
			cout << "     Расстановка окончена! Приступим к игре." << endl;
			//system("pause");
			Sleep(4000);
			break;
		}
	}
	return array;
}
int ** arrangement_computer(int **array, const char alphabet[10]) {

	cout << endl;
	for (int i = 0; i < 12; i++) {
		cout << "                        "; //отступ от границы слева 
		simple_vivod(array, alphabet, i);
		cout << endl;
	}
	cout << endl << endl << endl;

	default_random_engine generator;
	uniform_int_distribution<int> distribution(4, 9);
	int ships[4] = { 1, 2, 3, 4 };
	int ship_count = 0;
	int ship_length = 0;
	int x = 0, y = 0;

	while (true) {
		if (ships[ship_count] == 0) {
			ship_count += 1;
			setCursorPosition(0, 30);
			cout << ship_count<< " " << ships[0] << ships[1] << ships[2] << ships[3] <<endl;

		}
		switch (ship_count) {
		case 0:
			ship_length = 4;
			break;
		case 1:
			ship_length = 3;
			break;
		case 2:
			ship_length = 2;
			break;
		case 3:
			ship_length = 1;
			break;
		}
		while (true) {
			x = rand() % 10;
			y = rand() % 10;
			bool array_bo[4] = { true, true, true, true }; //ВЕРХ НИЗ ЛЕВО ПРАВО
			if (array[y][x] == 0) {
				for (int i = 1; i < ship_length; i++) {//в какую сторону нельзя повернуть корабль
					if (y - i <= 0) { array_bo[0] = false; } //вверх нельзя
					else if (y + i >= 10) { array_bo[1] = false; } //вниз нельзя

					if (x - i <= 0) { array_bo[2] = false; } //влево нельзя
					else if (x + i >= 10) { array_bo[3] = false; }
				}

				if (array_bo[0] == false && array_bo[1] == false && array_bo[2] == false && array_bo[3] == false) { continue; }


				int enter = -1;

				while (true) {
					enter = rand() % 4;
					bool a = array_bo[enter];
					if (a == true) { break; }
				}
				setCursorPosition(0, 25);
				cout << ship_length;
				switch (enter) {
				case 0:
					for (int i = 0; i < ship_length; i++) {
						array[y - i][x] = ship_length;
						setCursorPosition(28 + x * 2, 3 + y - i);
						cout << array[y - i][x];
					}
					break;
				case 1:
					for (int i = 0; i < ship_length; i++) {
						array[y + i][x] = ship_length;
						setCursorPosition(28 + x * 2, 3 + y + i);
						cout << array[y + i][x];
					}
					break;
				case 2:
					for (int i = 0; i < ship_length; i++) {
						array[y][x - i] = ship_length;
						setCursorPosition(28 + x * 2 - 2 * i, 3 + y);
						cout << array[y][x - i];
					}
					break;
				case 3:
					for (int i = 0; i < ship_length; i++) {
						array[y][x + i] = ship_length;
						setCursorPosition(28 + x * 2 + 2 * i, 3 + y);
						cout << array[y][x + i];
					}
					break;
				default:
					cout << "Some other key." << endl;
				}

				ships[ship_count] -= 1;
				break;
			}
			else { continue; }
		}
		if (ships[ship_count] == 0 && ship_count == 3) {
			setCursorPosition(0, 26);
			setCursorPosition(0, 31);
			cout << ship_count << " " << ships[0] << ships[1] << ships[2] << ships[3] << endl;
			system("pause");
		}

	}
	

}
int main()
{
	srand(time(NULL));
	
	setlocale(LC_ALL, "Russian");
	const char alphabet[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int ** self_zones = new int*[10];
	int ** enemy_zones = new int*[10];
	self_zones = set_0(self_zones);
	enemy_zones = set_0(enemy_zones);
	arrangement_computer(enemy_zones, alphabet);
	arrangement_player(self_zones, alphabet);
	system("cls");
	vivod(self_zones, enemy_zones, alphabet);
}