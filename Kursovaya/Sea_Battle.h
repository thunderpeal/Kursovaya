#include "pch.h"

#ifndef SEA_BATTLE_H
#define SEA_BATTLE_H
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
const int NotUsed = system("color 3F");
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(int text, ConsoleColor background);

void setCursorPosition(int x, int y);
#endif