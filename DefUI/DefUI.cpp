#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <iostream>

#include "UI.h"

void gotoxy(short col, short row)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { col,row };
	SetConsoleCursorPosition(h, position);
}

int main()
{
	system("chcp 65001");
	system("cls");
	system("MODE CON COLS=106 LINES=49");
	int cmd{ 121 };

	UI chineseChess;
	chineseChess.printUI();

	while (cmd == 121)
	{
		chineseChess.newBoard();
		chineseChess.printSentence("                       ", 77, 44, _TEXT_COLOUR);
		chineseChess.printBoard();

		while (!chineseChess.isGameWon())
		{
			chineseChess.movePiece();
			chineseChess.changePlayer();
		}

		Sleep(1500);

		chineseChess.printSentenceAnimated("Play again? (Y/N)", 77, 44, _TEXT_COLOUR);
		chineseChess.printSentence("       ", 94, 44, _TEXT_COLOUR);
		gotoxy(94, 44);

		cmd = _getch();

		while (cmd != 121 && cmd != 110) cmd = _getch();
	}

	chineseChess.printSentenceAnimated("Thanks for playing!", 77, 44, _TEXT_COLOUR);
	chineseChess.printSentence("   ", 96, 44, _TEXT_COLOUR);
	gotoxy(96, 44);

	Sleep(1000);

	return 0;
}