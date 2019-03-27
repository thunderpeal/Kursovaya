#include "pch.h"
#include <iostream>
#include "Sea_Battle.h"

int ** set_0(int **array) {
	for (int i = 0; i < 12; i++) {
		array[i] = new int[12];
		for (int j = 0; j < 12; j++) {
			if (i == 0 && j > 1 ) {
				array[i][j] = 9; //буквы
			}
			else if ((i <= 1 && j == 0) || i == 1 || j == 1) {
				array[i][j] = 8; //пробелы
			}
			else if (j == 0 && i != 0) {
				array[i][j] = 7; //цифры
			}
			else {
				array[i][j] = 0; //собственно, поля
			}
			
		}
	}
	return array;
}

void simple_vivod (int **array, const char alphabet[10], int i) {
	int checker_1_1 = 0; //для корректного отображения букв над полем
	int checker_1_2 = i-2; //а это для цифр, у нас они с 3 строки идут
	for (int j = 0; j < 12; j++) {
		switch (array[i][j]) {
		case 0:
			cout << ". ";
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			cout << array[i][j] << " ";
			break;
		case 7:
			checker_1_2 += 1;
			if (checker_1_2 == 10) { cout << checker_1_2; }
			else { cout << checker_1_2 << " "; }
			break;
		case 8:
			cout << "  ";
			break;
		case 9:
			cout << alphabet[checker_1_1] << " ";
			checker_1_1 += 1;
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

int main()
{
	const char alphabet[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int ** self_zones = new int*[10];
	int ** enemy_zones = new int*[10];
	self_zones = set_0(self_zones);
	enemy_zones = set_0(enemy_zones);
	vivod(self_zones, enemy_zones, alphabet);
}

//ДЕЛАЕМ РАССТАНОВКУУУ