#include "pch.h"

#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;
#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77

class Player {
public:
	int a;
	int **zones = new int*[10];
	Player() {
		for (int i = 0; i < 10; i++) {
			zones[i] = new int[10];
			for (int j = 0; j < 10; j++) { zones[i][j] = 0; }
		}
	}

	int ships[4] = { 4,6,6,4 };

	bool is_dead(int a[4]) {
		if (a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0) {
			return true;
		}
	}
};

class Ships {
public:
	int x1, y1, x2, y2;
	int health_bar;

	Ships(int a1, int b1, int a2, int b2, int l) {
		x1 = a1;
		y1 = b1;
		x2 = a2;
		y2 = b2;
		health_bar = l;
	};
};

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void vivod(int **array, const char alphabet[10], int i, bool costil) {
	for (int j = 0; j < 12; j++) {
		if (i == 0 && j >= 2) { cout << alphabet[j - 2] << " "; }
		else if (i == 1) { break; }
		else if ((i > 1 && j == 1) || (i == 0 && j < 2)) { cout << "  "; }
		else if (i > 1 && j == 0) {
			if (i - 1 != 10) { cout << i - 1 << " "; }
			else { cout << i - 1; }
		}
		else {
			if (costil == false) {
				switch (array[i - 2][j - 2]) {
				case 0:
					cout << ". ";
					break;
				case 1:
				case 2:
				case 3:
				case 4:
					cout << array[i - 2][j - 2] << " ";
					break;
				}
			}
			else {
				cout << ". ";
			}
		}
	}
}

int ** arrangement_player(int **array, const char alphabet[10], Ships **a) {
	int ships[4] = { 1, 2, 3, 4 };
	int ship_length = 0;
	int ship_count = 0;
	int number = 0;
	int number_letter = 0;
	char letter;

	cout << endl;
	for (int i = 0; i < 12; i++) {
		cout << "                        "; //отступ от границы слева 
		vivod(array, alphabet, i, false);
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


		cin >> letter >> number;
		number -= 1;
		number_letter = letter - 'A';


		setCursorPosition(0, 21);
		cout << "                                                                                 ";
		bool can_be_placed = true;
		setCursorPosition(0, 26);
		for (int i = -1; i < 2; i++) {
			if (number + i >= 10 || number + i < 0) { continue; }
			for (int j = -1; j < 2; j++) {
				if (number_letter + j >= 10 || number + j < 0) { continue; }
				if (array[number + i][number_letter + j] != 0) { //проверят их же на наличие других объектов
					can_be_placed = false;
				}
			}
		}
		if (can_be_placed == false) {
			setCursorPosition(0, 21);
			cout << "     Вы не можете расположить корабль в этой точке. Попробуйте еще раз.";
			continue;
		}

		else { ships[ship_count] -= 1; }
		array[number][number_letter] = ship_length; //закидываем в массив нашего поля голову корабля

		setCursorPosition(28 + number_letter * 2, 3 + number); //*2 учитывает пробелы в выводимом массиве
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
						cout << array[number][number_letter - i];
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
			cout << "     Расстановка окончена! Компьютер так же расставил свои корабли." << endl
				<< "                    Приступим к игре." << endl;
			//system("pause");
			Sleep(4000);
			break;
		}
	}
	return array;
}

int ** arrangement_computer(int **array, const char alphabet[10], Ships **a) {
	int ships[4] = { 1, 2, 3, 4 };
	int ship_count = 0;
	int check = 0;
	int ship_length = 0;
	int x = 0, y = 0;

	while (true) {
		if (ships[ship_count] == 0) {
			ship_count += 1;
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

			bool can_be_placed = true;

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (x + j >= 10 || x + j < 0 || y + i >= 10 || y + i < 0) { //проверяет все клетки вокруг случайно 
						continue;											//выбранной на выход за границы поля
					}
					else if (array[y + i][x + j] != 0) { //проверят их же на наличие других объектов
						can_be_placed = false;
					}
				}
			}

			if (can_be_placed == true) {
				for (int i = 1; i < ship_length; i++) {//в какую сторону нельзя повернуть корабль
					if (y - i <= 0) { array_bo[0] = false; }//вверх нельзя
					else {
						for (int j = -1; j < 2; j++) {
							if (x + j >= 10 || x + j < 0 || y - i - 1 < 0) { continue; }
							else if (array[y - i - 1][x + j] != 0) { array_bo[0] = false; }
						}
					}
					if (y + i >= 10) {
						array_bo[1] = false; //вниз нельзя
					}
					else {
						for (int j = -1; j < 2; j++) {
							if (x + j >= 10 || x + j < 0 || y + i + 1 >= 10) { continue; }
							else if (array[y + i + 1][x + j] != 0) { array_bo[1] = false; }
						}
					}
					if (x - i <= 0) {
						array_bo[2] = false;
					} //влево нельзя
					else {
						for (int j = -1; j < 2; j++) {
							if (y + j >= 10 || y + j < 0 || x - i - 1 < 0) { continue; }
							else if (array[y + j][x - i - 1] != 0) { array_bo[2] = false; }
						}
					}

					if (x + i >= 10) {
						array_bo[3] = false; //вправо нельзя
					}
					else {
						for (int j = -1; j < 2; j++) {
							if (y + j >= 10 || y + j < 0 || x + i + 1 >= 10) { continue; }
							else if (array[y + j][x + i + 1] != 0) { array_bo[3] = false; }
						}
					}
				}

				if (array_bo[0] == false && array_bo[1] == false && array_bo[2] == false && array_bo[3] == false) { continue; }

				ships[ship_count] -= 1;
				int enter = -1;
				while (true) { //рандомно выбираем направление из доступных
					enter = rand() % 4;
					bool a = array_bo[enter];
					if (a == true) { break; }
				}

				switch (enter) {
				case 0:
					a[check] = new Ships(x, y, x, y - ship_length + 1, ship_length);
					for (int i = 0; i < ship_length; i++) {
						array[y - i][x] = ship_length;
					}
					break;
				case 1:
					a[check] = new Ships(x, y, x - ship_length + 1, y, ship_length);
					for (int i = 0; i < ship_length; i++) {
						array[y + i][x] = ship_length;
					}
					break;
				case 2:
					a[check] = new Ships(x, y, x - ship_length + 1, y, ship_length);
					for (int i = 0; i < ship_length; i++) {
						array[y][x - i] = ship_length;
					}
					break;
				case 3:
					a[check] = new Ships(x, y, x - ship_length + 1, y, ship_length);
					for (int i = 0; i < ship_length; i++) {
						array[y][x + i] = ship_length;
					}
					break;
				default:
					cout << "Some other key." << endl;
				}
				check += 1;

				break;
			}
			else { continue; }
		}
		if (ships[ship_count] == 0 && ship_count == 3) {
			break;
		}
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	const char alphabet[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	Player player0;
	Ships **player0_ships = new Ships*[10];
	Player player1;
	Ships **player1_ships = new Ships*[10];
	arrangement_computer(player0.zones, alphabet, player0_ships);

	setCursorPosition(0, 2);
	cout << "     Расставить корабли самостоятельно" << endl << "     или использовать автоматическую расстановку? (1/0)";

	int answer;
	cin >> answer;
	system("cls");
	if (answer == 1) {
		arrangement_player(player1.zones, alphabet, player1_ships);
	}
	else {
		arrangement_computer(player1.zones, alphabet, player1_ships);
		setCursorPosition(0, 2);
		cout << "     Расстановка окончена! Компьютер также расставил свои корабли." << endl
			<< "                    Приступим к игре." << endl;
		Sleep(3000);
	}

	system("cls");

	cout << endl; //отступ от границы сверху
	for (int i = 0; i < 12; i++) {
		cout << "        "; //отступ от границы слева 
		vivod(player1.zones, alphabet, i, false);
		cout << "           ";
		vivod(player0.zones, alphabet, i, false);
		cout << endl;
	}
	cout << endl << endl << endl; //отступ снизу

	int count_of_moves = 0;
	int counter = 0;

	int number = 0;
	int number_letter = 0;
	char letter;
	int sequence = rand() % 2;

	bool is_prev_success = false;
	bool is_prev_success_comp = false;

	setCursorPosition(0, 16);
	cout << "  Вы находитесь в режиме боя. Право первого хода определяется жребием." << endl;
	cout << "  Ваши корабли располагаются на поле слева. Удачи!";
	Sleep(5000);
	for (int i = 0; i < 5; i++) {
		Sleep(250);
		setCursorPosition(0, 16);
		cout << "  Вы находитесь в режиме боя. Право первого хода определяется жребием." << endl;
		cout << "  Ваши корабли располагаются на поле слева. Удачи!";
		Sleep(250);
		setCursorPosition(0, 16);
		cout << "                                                                           " << endl;
		cout << "                                                                           " << endl;
	}

	setCursorPosition(0, 0);
	cout << "Ходов " << count_of_moves;
	while (true) {
		setCursorPosition(6, 0);
		cout << count_of_moves << "   ";
		if (sequence == 1) {
			if (is_prev_success == true) {
				setCursorPosition(41, 16);
				cout << "  ";
				setCursorPosition(41, 16);
			}
			else {
				setCursorPosition(0, 16);
				cout << "                                                ";
				setCursorPosition(0, 16);
				cout << "  Ваш ход. Введите координаты для атаки: ";
			}

			cin >> letter >> number;
			number_letter = letter - 'A';

			if (player0.zones[number - 1][number_letter] == 1 || player0.zones[number - 1][number_letter] == 2
				|| player0.zones[number - 1][number_letter] == 3 || player0.zones[number - 1][number_letter] == 4) {
				setCursorPosition(47 + number_letter * 2, 2 + number);
				cout << "x ";

				switch (player0.zones[number - 1][number_letter]) {
				case 1:
					player0.ships[3] -= 1;
					break;
				case 2:
					player0.ships[2] -= 1;
					break;
				case 3:
					player0.ships[1] -= 1;
					break;
				case 4:
					player0.ships[0] -= 1;
					break;
				}

				setCursorPosition(50, 14);
				cout << "Есть пробитие!";
				Sleep(1500);
				setCursorPosition(45, 14);
				cout << "                            ";

				player0.zones[number - 1][number_letter] = -2;

				sequence = 1;
				is_prev_success = true;

			}
			else {
				setCursorPosition(47 + number_letter * 2, 2 + number);
				cout << "o ";

				setCursorPosition(50, 14);
				cout << "   Промах!";
				Sleep(2000);
				setCursorPosition(45, 14);
				cout << "                            ";

				sequence = 0;
				is_prev_success = false;
			}
		}
		else {
			if (is_prev_success_comp == false) {
				setCursorPosition(0, 16);
				cout << "                                                                              ";
				setCursorPosition(0, 16);
				cout << "  Ход противника. Дождитесь окончания.";
			}

			int x = 0, y = 0;
			x = rand() % 10;
			y = rand() % 10;
			if (player1.zones[y][x] == 1 || player1.zones[y][x] == 2 || player1.zones[y][x] == 3 || player1.zones[y][x] == 4) {

				setCursorPosition(12 + x * 2, 3 + y);
				Sleep(1000);
				cout << "x ";
				setCursorPosition(12 + x * 2, 3 + y);
				Sleep(2000);

				switch (player1.zones[y][x]) {
				case 1:
					player1.ships[3] -= 1;
					break;
				case 2:
					player1.ships[2] -= 1;
					break;
				case 3:
					player1.ships[1] -= 1;
					break;
				case 4:
					player1.ships[0] -= 1;
					break;
				}

				setCursorPosition(11, 14);
				cout << "Есть пробитие!";
				Sleep(1500);
				setCursorPosition(11, 14);
				cout << "                            ";
				is_prev_success_comp = true;
				sequence = 0;
				player1.zones[y][x] = -2;
			}
			else {
				setCursorPosition(12 + x * 2, 3 + y);
				Sleep(1500);

				setCursorPosition(12 + x * 2, 3 + y);
				cout << "о";
				setCursorPosition(15, 14);
				cout << "Промах!";
				Sleep(2000);
				setCursorPosition(15, 14);
				cout << "                            ";
				sequence = 1;
				is_prev_success_comp = false;
			}
		}

		if (player0.is_dead(player0.ships) == true) {
			setCursorPosition(0, 20);
			cout << "  Вы выиграли! Поздравляем!";
		}
		else if (player1.is_dead(player1.ships) == true) {
			setCursorPosition(0, 20);
			cout << "  Вы проиграли!";
		}
		count_of_moves += 1;
	}
}