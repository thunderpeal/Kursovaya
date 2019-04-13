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
const char alphabet[10] = { 'A','B','C','D','E','F','G','H','I','J' };

class Ships{
public:
	void setCursorPosition(int x, int y)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}
	int x1, y1, x2, y2;
	int length;
	bool horizontal_orientation;
	int direction; //o вверх 1 вниз 2 влево 3 вправо
	int health_bar;
	void set(int a1, int b1, int a2, int b2, int l) {
		x1 = a1;
		y1 = b1;
		x2 = a2;
		y2 = b2;

		if (y1 == y2) { horizontal_orientation = true; }
		else { horizontal_orientation = false;  }


		if (y1 >= y2) { direction = 0; }
		else if (y2 > y1) { direction = 1; }
		if (x1 > x2) { direction = 2; }
		else if (x2 > x1) { direction = 3; }
		


		length = l;
		health_bar = l;
	};
	bool is_it(int x, int y) {
		if (((x >= x1 && x <= x2) || (x >= x2 && x <= x1)) && ((y >= y1 && y <= y2) || (y >= y2 && y <= y1))) {
			return true;
		}
		else {
			return false;
		}
	}

	bool is_dead() {
		if (health_bar == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void death(int** zones) {
		if (horizontal_orientation == true) {
			int k = -1;
			if (direction == 2) {  k = 1; }
			for (int i = -1; i <= length; i++) {
				if (x1 - k*i < 0 || x1 - k*i >= 10) { continue; }
				for (int j = -1; j < 2; j++) {
					if (y1 - k*j > 9 || y1 - k*j < 0 || zones[y1 - k*j][x1 - k*i] == -2) { continue; }
					zones[y1 - k*j][x1 - k*i] = -1;
					setCursorPosition(12 + x1 * 2 - k*2 * i, 3 + y1 - k*j);
					cout << "o ";
				}
			}	
		}
		else if (horizontal_orientation == false){
			int k = -1;
			if (direction == 0) { k = 1; }
			for (int i = -1; i <= length; i++) {
				if (y1 - k * i < 0 || y1 - k * i >= 10) { continue; }
				for (int j = -1; j < 2; j++) {
					if (x1 - k * j > 9 || x1 - k * j < 0 || zones[y1 - k * i][x1 - k * j] == -2) { continue; }
					zones[y1 - k * i][x1 - k * j] = -1;
					setCursorPosition(12 + x1 * 2 - 2 * k*j, 3 + y1 - k * i);
					cout << "o ";
				}
			}
		}
	}	
};

class Game {
public:
	int ships[4] = { 4,6,6,4 };
	int **zones = new int*[10];

	void set_0(int**&a) {
		for (int i = 0; i < 10; i++) {
			zones[i] = new int[10];
			for (int j = 0; j < 10; j++) { zones[i][j] = 0; }
		}
	}

	void setCursorPosition(int x, int y)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}

	void print_gamezone(int ** &array, const char alphabet[10], int i, bool costil) {
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

	void game_beginning_text() {
		setCursorPosition(0, 16);
		cout << "    Вы находитесь в режиме боя. Право первого хода определяется жребием." << endl;
		cout << "    Ваши корабли располагаются на поле слева. Удачи!";
		Sleep(5000);
		for (int i = 0; i < 5; i++) {
			Sleep(250);
			setCursorPosition(0, 16);
			cout << "    Вы находитесь в режиме боя. Право первого хода определяется жребием." << endl;
			cout << "    Ваши корабли располагаются на поле слева. Удачи!";
			Sleep(250);
			setCursorPosition(0, 16);
			cout << "                                                                           " << endl;
			cout << "                                                                           " << endl;
		}
	}

	void delete_dynamics() {

	}

	bool is_dead(Ships *a) {
		bool death = true;
		for (int i = 0; i < 10; i++) {
			if (a[i].health_bar != 0) {
				death = false;
				return false;
				break;
			}
		}
		if (death == true) {
			return true;
		}
	}

	void auto_arrangement(int **&array, const char alphabet[10], Ships *a) {
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
				bool *directions = new bool[4];
				directions[0] = true; directions[1] = true; directions[2] = true; directions[3] = true;

				bool can_be_placed = true;

				ship_location_checker(array, directions, &can_be_placed, x, y, ship_length);
				if (can_be_placed == false) {
					continue;
				}
				ships[ship_count] -= 1;
				int enter = -1;
				while (true) { //рандомно выбираем направление из доступных
					enter = rand() % 4;
					bool a = directions[enter];
					if (a == true) { break; }
				}

				switch (enter) {
				case 0:
					a[check].set(x,y, x ,y - ship_length + 1, ship_length);
					for (int i = 0; i < ship_length; i++) {
						array[y - i][x] = ship_length;
					}
					break;
				case 1:
					a[check].set(x, y, x, y + ship_length - 1, ship_length);
					for (int i = 0; i < ship_length; i++) {
						array[y + i][x] = ship_length;
					}
					break;
				case 2:
					a[check].set(x, y, x - ship_length + 1, y, ship_length);
					for (int i = 0; i < ship_length; i++) {
						array[y][x - i] = ship_length;
					}
					break;
				case 3:
					a[check].set(x, y, x + ship_length -1, y, ship_length);
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
			if (ships[ship_count] == 0 && ship_count == 3) {
				break;
			}
		}
	}

	void ship_location_checker(int **& array, bool dir[4], bool* c_b_p, int x, int y, int ship_length) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (x + j >= 10 || x + j < 0 || y + i >= 10 || y + i < 0) { //проверяет все клетки вокруг случайно 
					continue;											//выбранной на выход за границы поля
				}
				else if (array[y + i][x + j] != 0) { //проверят их же на наличие других объектов
					*c_b_p = false;
				}
			}
		}

		if (*c_b_p == true) {
			for (int i = 1; i < ship_length; i++) {//в какую сторону нельзя повернуть корабль
				if (y - i < 0) { dir[0] = false; }//вверх нельзя
				else {
					for (int j = -1; j < 2; j++) {
						if (x + j >= 10 || x + j < 0 || y - i - 1 < 0) { continue; }
						else if (array[y - i - 1][x + j] != 0) { dir[0] = false; }
					}
				}
				if (y + i >= 10) {
					dir[1] = false; //вниз нельзя
				}
				else {
					for (int j = -1; j < 2; j++) {
						if (x + j >= 10 || x + j < 0 || y + i + 1 >= 10) { continue; }
						else if (array[y + i + 1][x + j] != 0) { dir[1] = false; }
					}
				}
				if (x - i < 0) {
					dir[2] = false;
				} //влево нельзя
				else {
					for (int j = -1; j < 2; j++) {
						if (y + j >= 10 || y + j < 0 || x - i - 1 < 0) { continue; }
						else if (array[y + j][x - i - 1] != 0) { dir[2] = false; }
					}
				}

				if (x + i >= 10) {
					dir[3] = false; //вправо нельзя
				}
				else {
					for (int j = -1; j < 2; j++) {
						if (y + j >= 10 || y + j < 0 || x + i + 1 >= 10) { continue; }
						else if (array[y + j][x + i + 1] != 0) { dir[3] = false; }
					}
				}
			}
		}
		if (dir[0] == false && dir[1] == false && dir[2] == false && dir[3] == false) {
			*c_b_p = false;
		}
	}
};

class Player: public Game {
public:
	Ships player1_ships[10];
	Player() {
		set_0(zones);
		arrangement(zones, alphabet, player1_ships);
	}

	void player_arrangement_type(int **&array, const char alphabet[10], Ships *a) {
		int ships[4] = { 1, 2, 3, 4 };
		int ship_length = 0;
		int ship_count = 0;
		int number = 0;
		int number_letter = 0;
		char letter;
		int check = 0;

		cout << endl;
		for (int i = 0; i < 12; i++) {
			cout << "                        "; //отступ от границы слева 
			print_gamezone(array, alphabet, i, false);
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
			setCursorPosition(0, 20);
			cout << "                                                                ";
			setCursorPosition(0, 20);
			switch (ship_count) {
			case 0:
				ship_length = 4;
				cout << "     Сейчас расположите линкор: ";
				break;
			case 1:
				ship_length = 3;
				cout << "     Теперь расположите крейсер: ";
				break;
			case 2:
				ship_length = 2;
				cout << "     Очередь расположить эсминец: ";
				break;
			case 3:
				ship_length = 1;
				cout << "     Сейчас расположите катер: ";
				break;
			}

			cin >> letter >> number;
			number -= 1;
			number_letter = letter - 'A';

			setCursorPosition(0, 21);
			cout << "                                                                                 ";
			//setCursorPosition(0, 26);
			bool can_be_placed = true;
			bool *directions = new bool[4];
			directions[0] = true; directions[1] = true; directions[2] = true; directions[3] = true;

			ship_location_checker(array, directions, &can_be_placed, number_letter, number, ship_length);

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
				cout << "     Теперь введите направление расположения корабля стрелкой: ";
				bool exit = false;
				while (true) {
					if (exit == true) { break; }
					int KeyStroke;
					KeyStroke = _getch();

					if (KeyStroke == 224)
					{
						KeyStroke = _getch(); // Even though there are 2 getch() it reads one keystroke
						switch (KeyStroke)
						{
						case UP_ARROW:
							if (directions[0] == true) {
								a[check].set(number_letter, number, number_letter, number - ship_length + 1, ship_length);
								check += 1;
								for (int i = 1; i < ship_length; i++) {
									array[number - i][number_letter] = ship_length;
									setCursorPosition(28 + number_letter * 2, 3 + number - i);
									cout << array[number - i][number_letter];
									exit = true;
								}
							}
							else {
								setCursorPosition(0, 21);
								cout << "     Вы не можете расположить корабль в эту сторону. Попробуйте еще раз.";
								setCursorPosition(63, 20);
							}
							break;
						case DOWN_ARROW:
							if (directions[1] == true) {
								a[check].set(number_letter, number, number_letter, number + ship_length - 1, ship_length);
								check += 1;
								for (int i = 1; i < ship_length; i++) {
									array[number + i][number_letter] = ship_length;
									setCursorPosition(28 + number_letter * 2, 3 + number + i);
									cout << array[number + i][number_letter];
									exit = true;
								}
							}
							else {
								setCursorPosition(0, 21);
								cout << "     Вы не можете расположить корабль в эту сторону. Попробуйте еще раз.";
								setCursorPosition(63, 20);
							}
							break;
						case LEFT_ARROW:
							if (directions[2] == true) {
								a[check].set(number_letter, number, number_letter - ship_length + 1, number, ship_length);
								check += 1;
								for (int i = 1; i < ship_length; i++) {
									array[number][number_letter - i] = ship_length;
									setCursorPosition(28 + number_letter * 2 - 2 * i, 3 + number);
									cout << array[number][number_letter - i];
									exit = true;
								}
							}
							else {
								setCursorPosition(0, 21);
								cout << "     Вы не можете расположить корабль в эту сторону. Попробуйте еще раз.";
								setCursorPosition(63, 20);
							}
							break;
						case RIGHT_ARROW:
							if (directions[3] == true) {
								a[check].set(number_letter, number, number_letter + ship_length - 1, number, ship_length);
								check += 1;
								for (int i = 1; i < ship_length; i++) {
									array[number][number_letter + i] = ship_length;
									setCursorPosition(28 + number_letter * 2 + 2 * i, 3 + number);
									cout << array[number][number_letter + i];
									exit = true;
								}
							}
							else {
								setCursorPosition(0, 21);
								cout << "     Вы не можете расположить корабль в эту сторону. Попробуйте еще раз.";
								setCursorPosition(63, 20);
							}
							break;
						default:
							cout << "Some other key." << endl;
						}
					}
					else cout << KeyStroke << endl;
				}
				setCursorPosition(0, 21);
				cout << "                                                                                         ";
			}
			if (ships[ship_count] == 0 && ship_count == 3) { break; }
		}
	}

	void arrangement(int **& zones, const char alphabet[10],  Ships *player1_ships) {
		int answer = 0;
		int answer_1 = 0;
		while (true) {
			setCursorPosition(0, 2);
			cout << "     Расставить корабли самостоятельно" << endl << "     или использовать автоматическую расстановку?(1/0) ";
			cin >> answer;
			system("cls");
			if (answer == 1) {
				player_arrangement_type(zones, alphabet, player1_ships);
				setCursorPosition(0, 22);
				cout << "      Подтвердить установку или повторить с нуля?(1/0) ";
				cin >> answer_1;
				if (answer_1 == 0) {
					set_0(zones);
					system("cls");
					continue;
				}
				else { break; }
			}
			else {
				auto_arrangement(zones, alphabet, player1_ships);
				cout << endl;
				for (int i = 0; i < 12; i++) {
					cout << "                        "; //отступ от границы слева 
					print_gamezone(zones, alphabet, i, false);
					cout << endl;
				}

				setCursorPosition(0, 15);
				cout << "            Подтвердить установку или повторить с нуля?(1/0) ";
				cin >> answer_1;
				setCursorPosition(0, 17);

				if (answer_1 == 0) {
					set_0(zones);
					system("cls");
					continue;
				}
				else {
					cout << "        Расстановка окончена! Компьютер также расставил свои корабли." << endl
						<< "                    Приступим к игре." << endl;
					Sleep(3000);
					break;
				}

			}
		}
	}
};

class Computer : public Game {
public:
	Ships ships0[10];
	Computer() {
		set_0(zones);
		auto_arrangement(zones, alphabet, ships0);
	}
};

class Battle: public Game {

};

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	
	Game game;
	Computer player0;
	Player player1;

	system("cls");

	cout << endl; //отступ от границы сверху
	for (int i = 0; i < 12; i++) {
		cout << "        "; //отступ от границы слева 
		game.print_gamezone(player1.zones, alphabet, i, false);
		cout << "           ";
		game.print_gamezone(player0.zones, alphabet, i, false);
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

	game.game_beginning_text();
	
	game.setCursorPosition(0, 0);
	cout << "Ходов " << count_of_moves;
	int x = 0, y = 0;
	int y1 = 0, x1 = 0;
	int x_supreme = 0, y_supreme = 0;
	Ships *current_ship = 0;
	bool help = false;
	int enter = -1;
	int count_of_hits = 0;
	bool *directions_con = new bool[4];
	directions_con[0] = true; directions_con[1] = true; directions_con[2] = true; directions_con[3] = true;

	while (true) {
		game.setCursorPosition(6, 0);
		cout << count_of_moves << "   ";
		if (sequence == 1) {
			if (is_prev_success == true) {
				game.setCursorPosition(41, 16);
				cout << "  ";
				game.setCursorPosition(41, 16);
			}
			else {
				game.setCursorPosition(0, 16);
				cout << "                                                      ";
				game.setCursorPosition(0, 16);
				cout << "    Ваш ход. Введите координаты для атаки: ";
			}

			cin >> letter >> number;
			number_letter = letter - 'A';

			if (player0.zones[number - 1][number_letter] == 1 || player0.zones[number - 1][number_letter] == 2
				|| player0.zones[number - 1][number_letter] == 3 || player0.zones[number - 1][number_letter] == 4) {
				game.setCursorPosition(47 + number_letter * 2, 2 + number);
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

				game.setCursorPosition(50, 14);
				cout << "Есть пробитие!";
				Sleep(1500);
				game.setCursorPosition(45, 14);
				cout << "                            ";

				player0.zones[number - 1][number_letter] = -2;

				sequence = 1;
				is_prev_success = true;

			}
			else {
				game.setCursorPosition(47 + number_letter * 2, 2 + number);
				cout << "o ";

				game.setCursorPosition(50, 14);
				cout << "   Промах!";
				Sleep(2000);
				game.setCursorPosition(45, 14);
				cout << "                            ";

				sequence = 0;
				is_prev_success = false;
			}
		}
		else {
			if (is_prev_success_comp == false) {
				game.setCursorPosition(0, 16);
				cout << "                                                                              ";
				game.setCursorPosition(0, 16);
				cout << "    Ход противника. Дождитесь окончания.";
				while (true) {		
					x = rand() % 10;
					y = rand() % 10;
					if (player1.zones[y][x] == -2 || player1.zones[y][x] == -1 || player1.zones[y][x] == 0) {
						continue;
					}
					else {
						if (player1.zones[y][x] == 1 || player1.zones[y][x] == 2 || player1.zones[y][x] == 3 || player1.zones[y][x] == 4) {
							game.setCursorPosition(12 + x * 2, 3 + y);
							Sleep(1000);
							cout << "x ";
							game.setCursorPosition(12 + x * 2, 3 + y);
							Sleep(2000);

							game.setCursorPosition(0, 18);
							cout << x << y;
							system("pause");
							for (int i = 0; i < 10; i++) {
								if (player1.player1_ships[i].is_it(x,y) == true) {
									player1.player1_ships[i].health_bar -= 1;
									if (player1.player1_ships[i].is_dead() == true) {
										player1.player1_ships[i].death(player1.zones);
										is_prev_success_comp = false;
										game.setCursorPosition(11, 14);
										cout << "Корабль затоплен!";
										Sleep(2500);
										game.setCursorPosition(11, 14);
										cout << "                            ";
									}
									else {
										x_supreme = x;
										y_supreme = y;
										count_of_hits += 1;
										game.setCursorPosition(11, 14);
										cout << "Есть пробитие!";
										Sleep(1500);
										game.setCursorPosition(11, 14);
										cout << "                            ";
										current_ship = &player1.player1_ships[i];
										is_prev_success_comp = true;
									}
									break;
								}
							}
							player1.zones[y][x] = -2;
							sequence = 0;
							
						}

						else {
							player1.zones[y][x] = -1;
							game.setCursorPosition(12 + x * 2, 3 + y);
							Sleep(1500);

							game.setCursorPosition(12 + x * 2, 3 + y);
							cout << "о";
							game.setCursorPosition(15, 14);
							cout << "Промах!";
							Sleep(2000);
							game.setCursorPosition(15, 14);
							cout << "                            ";
							sequence = 1;
							is_prev_success_comp = false;
						}
						break;
					}
				}
			}
			else {
				if (help == false) {
					if (y - 1 < 0 || player1.zones[y - 1][x] == -2 || player1.zones[y - 1][x] == -1) {
						directions_con[0] = false;
					}
					if (y + 1 >= 10 || player1.zones[y + 1][x] == -2 || player1.zones[y + 1][x] == -1) {
						directions_con[1] = false;
					}
					if (x - 1 < 0 || player1.zones[y][x - 1] == -2 || player1.zones[y][x - 1] == -1) {
						directions_con[2] = false;
					}
					if (x + 1 >= 10 || player1.zones[y][x + 1] == -2 || player1.zones[y][x + 1] == -1) {
						directions_con[3] = false;
					}
					help = true;

					while (true) { //рандомно выбираем направление из доступных
						enter = rand() % 4;
						bool a = directions_con[enter];
						if (a == true) { break; }
					}
				}
				
				switch (enter) {
				case 0:
					y1 = y - 1;
					x1 = x;
					break;
				case 1:
					y1 = y + 1;
					x1 = x;
					break;
				case 2:
					x1 = x- 1;
					y1 = y;
					break;
				case 3:
					x1 = x + 1;
					y1 = y;
					break;

				}

				if (player1.zones[y1][x1] == 1 || player1.zones[y1][x1] == 2 || player1.zones[y1][x1] == 3 || player1.zones[y1][x1] == 4) {
					game.setCursorPosition(12 + x1 * 2, 3 + y1);
					Sleep(1000);
					cout << "x ";
					game.setCursorPosition(12 + x1 * 2, 3 + y1);
					Sleep(2000);

					game.setCursorPosition(0, 18);
					cout << directions_con[0] << directions_con[1] << directions_con[2] << directions_con[3];


					player1.zones[y1][x1] = -2;
					x = x1;
					y = y1;

					count_of_hits += 1;
					if (count_of_hits >= 2) {
						if (enter == 0 || enter == 1) {
							directions_con[2] = false;
							directions_con[3] = false;
						}
						else if (enter == 2 || enter == 3) {
							directions_con[0] = false;
							directions_con[1] = false;
						}
					}

					current_ship->health_bar -= 1;
					if (current_ship->is_dead() == true) {
						current_ship->death(player1.zones);
						is_prev_success_comp = false;
						directions_con[0] = true; directions_con[1] = true; directions_con[2] = true; directions_con[3] = true;
						current_ship = 0;
						enter = -1;
						count_of_hits = 0;
						help = false;
						x_supreme = 0;
						y_supreme = 0;

						game.setCursorPosition(11, 14);
						cout << "Корабль затоплен!";
						Sleep(2500);
						game.setCursorPosition(11, 14);
						cout << "                            ";
					}
					else {
						game.setCursorPosition(11, 14);
						cout << "Есть пробитие!";
						Sleep(1500);
						game.setCursorPosition(11, 14);
						cout << "                            ";
						is_prev_success_comp = true;
					}
					sequence = 0;
				}

				else {
					directions_con[enter] = false;
					while (true) { //рандомно выбираем направление из доступных
						enter = rand() % 4;
						bool a = directions_con[enter];
						if (a == true) { break; }
					}
					x = x_supreme;
					y = y_supreme;
					player1.zones[y1][x1] = -1;
					game.setCursorPosition(12 + x1 * 2, 3 + y1);
					Sleep(1500);

					game.setCursorPosition(12 + x1 * 2, 3 + y1);
					cout << "о";
					game.setCursorPosition(15, 14);
					cout << "Промах!";
					Sleep(2000);
					game.setCursorPosition(15, 14);
					cout << "                            ";
					sequence = 1;
				
				}
			}
		}

		if (player0.is_dead(player0.ships0) == true) {
			game.setCursorPosition(0, 20);
			cout << "  Вы выиграли! Поздравляем!";
		}
		else if (player1.is_dead(player1.player1_ships) == true) {
			game.setCursorPosition(0, 20);
			cout << "  Вы проиграли!";
		}
		count_of_moves += 1;
	}
}