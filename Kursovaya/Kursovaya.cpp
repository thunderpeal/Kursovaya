#include "pch.h"
#include <iostream>
#include "Sea_Battle.h"

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

int ** ras(int **array, const char alphabet[10]) {
	while (true) {
		int number = 0;
		int number_letter;
		char letter;
		cout << endl;
		for (int i = 0; i < 12; i++) {
			cout << "                        "; //отступ от границы слева 
			simple_vivod(array, alphabet, i);
			cout << endl;
		}
		cout << endl << endl << endl;
		cout << "     Это режим расстановки ваших кораблей." << endl;
		cout << "     Введите точку (например, D 4), где хотите поставить 'голову' корабля, " << endl;
		cout << "     а затем укажите стрелочкой направление тела корабля." << endl << endl;

		cout << "     Сейчас расположите линкор: ";

		cin >> letter >> number;
		number_letter = letter - 'A';
		
		array[number_letter][number] = 4;

		system("pause");
		system("cls");
	}
	return array;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	const char alphabet[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int ** self_zones = new int*[10];
	int ** enemy_zones = new int*[10];
	self_zones = set_0(self_zones);
	enemy_zones = set_0(enemy_zones);

	ras(self_zones, alphabet);
	
	//vivod(self_zones, enemy_zones, alphabet);
}
//ДЕЛАЕМ РАССТАНОВКУУУ