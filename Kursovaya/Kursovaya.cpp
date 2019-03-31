#include "pch.h"
#include "Sea_Battle.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>

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

void simple_vivod (int **array, const char alphabet[10], int i, bool costil) {
	for (int j = 0; j < 12; j++) {
		if (i == 0 && j >= 2) { cout << alphabet[j - 2] << " ";  }
		else if (i == 1) { break; }
		else if ((i > 1 && j == 1) || (i == 0 && j < 2)) { cout << "  "; }
		else if ( i > 1 && j == 0) { 
			if (i-1 != 10) {cout << i - 1 << " ";}
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

void vivod(int **array_1, int **array_2, const char alphabet[10]) {
	cout << endl; //отступ от границы сверху
	for (int i = 0; i < 12; i++) {
		cout << "        "; //отступ от границы слева 
		simple_vivod(array_1, alphabet, i, false);
		cout << "           ";
		simple_vivod(array_2, alphabet, i, false);
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
		simple_vivod(array, alphabet, i, false);
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
		ships[ship_count] -= 1;

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
			cout << "     Расстановка окончена! Компьютер так же расставил свои корабли."<<endl
				<<"                    Приступим к игре." << endl;
			//system("pause");
			Sleep(4000);
			break;
		}
	}
	return array;
}

int ** arrangement_computer(int **array, const char alphabet[10]) {
	int ships[4] = { 1, 2, 3, 4 };
	int ship_count = 0;
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
					else if (array[y + i][x + j] !=0 ) { //проверят их же на наличие других объектов
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
							else if (array[y-i-1][x + j] != 0) { array_bo[0] = false; }
						}
					}
					if (y + i >= 10) { 
						array_bo[1] = false; //вниз нельзя
					} 
					else {
						for (int j = -1; j < 2; j++) {
							if (x + j >= 10 || x + j < 0 || y + i + 1 >=10) { continue; }
							else if (array[y+i+1][x + j] != 0) { array_bo[1] = false; }
						}
					}
					if (x - i <= 0) { 
						array_bo[2] = false;
					} //влево нельзя
					else {
						for (int j = -1; j < 2; j++) {
							if (y + j >= 10 || y + j < 0 || x - i - 1 < 0) { continue; }
							else if (array[y+j][x - i -1] != 0) { array_bo[2] = false; }
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
					for (int i = 0; i < ship_length; i++) {
						array[y - i][x] = ship_length;
					}
					break;
				case 1:
					for (int i = 0; i < ship_length; i++) {
						array[y + i][x] = ship_length;
					}
					break;
				case 2:
					for (int i = 0; i < ship_length; i++) {
						array[y][x - i] = ship_length;
					}
					break;
				case 3:
					for (int i = 0; i < ship_length; i++) {
						array[y][x + i] = ship_length;
					}
					break;
				default:
					cout << "Some other key." << endl;
				}
				
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
	int ** self_zones = new int*[10];
	int ** enemy_zones = new int*[10];
	self_zones = set_0(self_zones);
	enemy_zones = set_0(enemy_zones);

	arrangement_computer(enemy_zones, alphabet);
	setCursorPosition(0, 2);
	cout << "  Расставить корабли самостоятельно"<<endl<<"  или использовать автоматическую расстановку? (1/0)";
	
	int answer;
	cin >> answer;
	system("cls");
	if (answer == 1) {
		arrangement_player(self_zones, alphabet);
	}
	else {
		arrangement_computer(self_zones, alphabet);
		setCursorPosition(0, 2);
		cout << "     Расстановка окончена! Компьютер так же расставил свои корабли." << endl
			<< "                    Приступим к игре." << endl;
		Sleep(3000);
	}

	system("cls");
	vivod(self_zones, enemy_zones, alphabet);

	int count_of_moves = 0;
	int counter = 0;
	int player_ships[4] = { 4,6,6,4 };
	int computer_ships[4] = { 4,6,6,4 };
	int number = 0;
	int number_letter = 0;
	char letter;
	int sequence = rand() % 2;
	bool player_won = false;
	bool computer_won = false;

	bool is_prev_success = false;
	bool is_prev_success_comp = false;

	setCursorPosition(0,16);
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
		cout  << count_of_moves << "   ";
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

			if (enemy_zones[number - 1][number_letter] == 1 || enemy_zones[number - 1][number_letter] == 2
				|| enemy_zones[number - 1][number_letter] == 3 || enemy_zones[number - 1][number_letter] == 4) {
				setCursorPosition(47 + number_letter*2, 2 + number);
				cout << "x ";
				
				switch (enemy_zones[number - 1][number_letter]) {
				case 1:
					computer_ships[3] -= 1;	
					break;
				case 2:
					computer_ships[2] -= 1;
					break;
				case 3:
					computer_ships[1] -= 1;
					break;
				case 4:
					computer_ships[0] -= 1;
					break;
				}

				setCursorPosition(50, 14);
				cout << "Есть пробитие!";
				Sleep(1500);
				setCursorPosition(45, 14);
				cout << "                            ";

				enemy_zones[number - 1][number_letter] = -2;
				if (computer_ships[0] == 0 && computer_ships[1] == 0 && computer_ships[2] == 0 && computer_ships[3] == 0) {
					player_won = true;
				}
				sequence = 1;
				is_prev_success = true;

			}
			else {
				setCursorPosition(47 + number_letter*2, 2 + number);
				cout << "o ";
				
				setCursorPosition(50, 14);
				cout << "   Промах";
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
				cout << "  Ход противника. Дождитесь завершения.";
			}
			
			int x = 0, y = 0;
			x = rand() % 10;
			y = rand() % 10;
			if (self_zones[y][x] == 1 || self_zones[y][x] == 2 || self_zones[y][x] == 3 || self_zones[y][x] == 4) {
				
				setCursorPosition(12 + x * 2, 3 + y);
				Sleep(1000);
				cout << "x ";
				setCursorPosition(12 + x * 2, 3 + y);
				Sleep(2000);
				
				switch (self_zones[y][x]) {
				case 1:
					player_ships[3] -= 1;
					break;
				case 2:
					player_ships[2] -= 1;
					break;
				case 3:
					player_ships[1] -= 1;
					break;
				case 4:
					player_ships[0] -= 1;
					break;
				}
				if (player_ships[0] == 0 && player_ships[1] == 0 && player_ships[2] == 0 && player_ships[3] == 0) {
					computer_won = true;
				}
				setCursorPosition(11, 14);
				cout << "Есть пробитие!";
				Sleep(1500);
				setCursorPosition(11, 14);
				cout << "                            ";
				is_prev_success_comp = true;
				sequence = 0;
				self_zones[y][x] = -2;
			}
			else {
				setCursorPosition(12 + x * 2, 3 + y);
				Sleep(1500);
				
				setCursorPosition(12 + x * 2, 3 + y);
				cout << "о";
				setCursorPosition(15, 14);
				cout << "Промах";
				Sleep(2000);
				setCursorPosition(15, 14);
				cout << "                            ";
				sequence = 1;
				is_prev_success_comp = false;
			}	
		}

		if (player_won == true) {
			setCursorPosition(0, 20);
			cout << "  Вы выиграли! Поздравляем!";
		}
		else if(computer_won == true) {
			setCursorPosition(0, 20);
			cout << "  Вы проиграли!";
		}
		count_of_moves += 1;
	}
}