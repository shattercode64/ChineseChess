#ifndef UI_H
#define UI_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define _BGBOLDER_COLOUR 59
#define _TITLE_COLOUR 48
#define _BOARD_COLOUR 59
#define _TEXT_COLOUR 63

#define _PIECE_COLOUR_BLACK 15
#define _PIECE_COLOUR_WHITE 79

#define _SELECTED_COLOUR_BLACK 118
#define _SELECTED_COLOUR_WHITE 116

#define _HIGHLIGHT_COLOUR 113


#define _PLAYER_BLACK 0
#define _PLAYER_WHITE 1 // Goes first.

#define _ENTER_TO_SELECT 2
#define _ENTER_TO_PLACE 3

#define _HISTORY_SIZE 15

class UI
{
public:
	UI();

	void printUI();
	void printBoard();

	void newBoard();
	void saveBoard();
	void loadBoard();

	void movePiece();
	void changePlayer();

	void updateHistory();
	void printHistory();
	void clearHistory();

	bool isGameWon();

	void printSentence(const string, const short, const short, const int);
	void printSentenceAnimated(const string, const short, const short, const int);
	
private:

	void gotoxy(short, short);
	void move(short, short, short, short, int);
	void printChessPiece(string);
	void undo();
	void checkIfWon();
	void highlight(const int, const int); // x, y of gameBoard
	void unHighlight(const int, const int); // x, y of gameBoard
	void findValidPlaces(const string, const int, const int);

	bool newGame, gameWon, noMove;

	string userInterface[53][46]; // x, y
	int userColour[53][46]; // x, y

	string gameBoard[33][31]; // x, y
	string defaultGameBoard[33][31]; // x, y
	int gameColour[33][31]; // x, y

	int player, promptSentence;
	int x1, y1, x0, y0, lastMove;
	string lastEaten;
	int lastEaten_Colour;
	const string prompt[4] =
	{
		"Black's Move!", "Red's Move!  ", "select piece.   ", "select location."
	};
	const string chessPieceABC[15] = // 1 - 7 Black & 8 - 14 White
	{
		"0", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"
	};
	const string chinese123 = "0九八七六五四三二一";
	vector <string> historyList;

	fstream ioStream;

};

#endif // !UI_H