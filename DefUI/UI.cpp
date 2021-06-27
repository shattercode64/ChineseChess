#include "UI.h"

UI::UI()
{
	for (int y = 0; y <= 45; y++) for (int x = 0; x < 53; x++)
	{
		userColour[x][y] = _BGBOLDER_COLOUR;
		switch (y)
		{
		case 0:
			if (x == 0) userInterface[x][y] = "╔";
			else if (x == 37) userInterface[x][y] = "╦";
			else if (x == 52) userInterface[x][y] = "╗";
			else userInterface[x][y] = "═";
			break;

		case 32:
			if (x == 0) userInterface[x][y] = "║";
			else if (x == 37) userInterface[x][y] = "╠";
			else if (x == 52) userInterface[x][y] = "╣";
			else if (x > 37 && x < 52) userInterface[x][y] = "═";
			else userInterface[x][y] = " ";
			break;

		case 45:
			if (x == 0) userInterface[x][y] = "╚";
			else if (x == 52) userInterface[x][y] = "╝";
			else if (x == 37) userInterface[x][y] = "╩";
			else userInterface[x][y] = "═";
			break;

		default:
			if (x == 0 || x == 37 || x == 52) userInterface[x][y] = "║";
			else userInterface[x][y] = " ";
			break;
		}
	}

	newBoard();

}

void UI::printUI()
{
	for (int y = 0; y <= 44; y++)
	{
		for (int x = 0; x < 53; x++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), userColour[x][y]);
			std::cout << userInterface[x][y] << " ";
		}
		std::cout << endl;
	}
	for (int x = 0; x < 53; x++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), userColour[x][45]);
		std::cout << userInterface[x][45] << " ";
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _TITLE_COLOUR);
	string title = "  C H I N E S E    C H E S S ";
	for (int i = 0; i < 15; i++)
	{
		gotoxy(i + 1, 0);
		std::cout << "\b" << title[i];

		gotoxy(29 - i, 0);
		std::cout << "\b" << title[28 - i];

		gotoxy(15, 0);
		Sleep(60);
	}


	printSentenceAnimated("H I S T O R Y", 90, 1, _TITLE_COLOUR);
	printSentenceAnimated("C U R R E N T    M O V E", 79, 33, _TITLE_COLOUR);

	gotoxy(10, 10);
}

void UI::newBoard()
{
	// Initial values.
	player = _PLAYER_WHITE;
	promptSentence = _ENTER_TO_SELECT;

	x0 = -1;
	y0 = -1;
	x1 = -1;
	y1 = -1;

	newGame = true;
	gameWon = false;

	lastEaten = "+";
	lastEaten_Colour = _BOARD_COLOUR;
	noMove = true;

	clearHistory();

	for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x < 33; x++)
		{
			gameColour[x][y] = _BOARD_COLOUR;

			if (y == 0 || y == 12 || y == 18 || y == 30 || (y % 3 == 0 && y != 15))
			{
				if (x == 0 || x == 32 || x % 4 == 0) gameBoard[x][y] = "+";
				else gameBoard[x][y] = "--";
			}
			else if (y >= 13 && y <= 17)
			{
				if (x == 0 || x == 32) gameBoard[x][y] = "|";
				else gameBoard[x][y] = " ";
			}
			else
			{
				if (x % 4 == 0) gameBoard[x][y] = "|";
				else gameBoard[x][y] = " ";
			}
		}
	}
	
	gameBoard[14][1] = "\\";
	gameBoard[15][2] = "\\";
	gameBoard[18][4] = "\\";
	gameBoard[19][5] = "\\";

	gameBoard[14][25] = "\\";
	gameBoard[15][26] = "\\";
	gameBoard[18][28] = "\\";
	gameBoard[19][29] = "\\";

	gameBoard[14][5] = "/";
	gameBoard[15][4] = "/";
	gameBoard[18][2] = "/";
	gameBoard[19][1] = "/";

	gameBoard[14][29] =  "/";
	gameBoard[15][28] = "/";
	gameBoard[18][26] = "/";
	gameBoard[19][25] = "/";

	for (int y = 0; y < 31; y++) for (int x = 0; x < 33; x++) defaultGameBoard[x][y] = gameBoard[x][y];

	// Set black chess pieces.
	gameBoard[0][0] = 'D';
	gameBoard[4][0] = 'E';
	gameBoard[8][0] = 'C';
	gameBoard[12][0] = 'B';
	gameBoard[16][0] = 'A';
	gameBoard[20][0] = 'B';
	gameBoard[24][0] = 'C';
	gameBoard[28][0] = 'E';
	gameBoard[32][0] = 'D';
	for (int x = 0; x < 33; x += 4) gameColour[x][0] = _PIECE_COLOUR_BLACK;
	gameBoard[4][6] = 'F';
	gameBoard[28][6] = 'F';
	gameColour[4][6] = _PIECE_COLOUR_BLACK;
	gameColour[28][6] = _PIECE_COLOUR_BLACK;
	for (int x = 0; x < 33; x += 8)
	{
		gameBoard[x][9] = 'G';
		gameColour[x][9] = _PIECE_COLOUR_BLACK;
	}

	// Set white chess pieces.

	gameBoard[0][30] = 'K';
	gameBoard[4][30] = 'L';
	gameBoard[8][30] = 'J';
	gameBoard[12][30] = 'I';
	gameBoard[16][30] = 'H';
	gameBoard[20][30] = 'I';
	gameBoard[24][30] = 'J';
	gameBoard[28][30] = 'L';
	gameBoard[32][30] = 'K';
	for (int x = 0; x < 33; x += 4) gameColour[x][30] = _PIECE_COLOUR_WHITE;
	gameBoard[4][24] = 'M';
	gameBoard[28][24] = 'M';
	gameColour[4][24] = _PIECE_COLOUR_WHITE;
	gameColour[28][24] = _PIECE_COLOUR_WHITE;
	for (int x = 0; x < 33; x += 8)
	{
		gameBoard[x][21] = 'N';
		gameColour[x][21] = _PIECE_COLOUR_WHITE;
	}

}

void UI::printBoard()
{
	const int x0{ 21 }, y0{ 7 };

	for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x <= 33; x++)
		{
			gotoxy(x0 + x + 1, y0 + y);

			if (x == 33)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BGBOLDER_COLOUR);
				std::cout << "\b ";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BOARD_COLOUR);
				std::cout << "\b" << defaultGameBoard[x][y];
			}
			
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _TEXT_COLOUR);
	gotoxy(21, 6);
	std::cout << "1   2   3   4   5   6   7   8   9";
	gotoxy(21, 38);
	std::cout << "九  八  七  六  五  四  三  二  一";
	gotoxy(25, 22);
	std::cout << "楚  河              漢  界";
	for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x < 33; x++)
		{
			gotoxy(x0 + x + 1, y0 + y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x][y]);
			std::cout << "\b";
			if (gameBoard[x][y].size() == 1)
			{
				for (int i = 1; i < 15; i++) if (chessPieceABC[i] == gameBoard[x][y])
				{
					printChessPiece(gameBoard[x][y]);
					continue;
				}
			}
			
		}
	}

	printHistory();

	printSentence("Use CTRL+Z to undo move (1 move only)", 6, 43, _TEXT_COLOUR);
	printSentence("Use CTRL+S to save board          CTRL+O to load previous board", 6, 44, _TEXT_COLOUR);

	printSentence(prompt[player], 77, 36, _TEXT_COLOUR);
	printSentence("Press ENTER to", 77, 38, _TEXT_COLOUR);
	printSentence(prompt[promptSentence], 77, 39, _TEXT_COLOUR);
	printSentence("Use ARROW KEYS", 77, 41, _TEXT_COLOUR);
	printSentence("to move around.", 77, 42, _TEXT_COLOUR);
}

void UI::gotoxy(short col, short row)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { col,row };
	SetConsoleCursorPosition(h, position);
}

void UI::printSentence(const string line, const short x, const short y, const int colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
	for (int i = 0; i < line.size(); i++)
	{
		gotoxy(x + i + 1, y);
		std::cout << "\b" << line[i];
		// Sleep(40);
	}
}

void UI::printSentenceAnimated(const string line, const short x, const short y, const int colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
	for (int i = 0; i < line.size(); i++)
	{
		gotoxy(x + i + 1, y);
		std::cout << "\b" << line[i];
		Sleep(40);
	}
}

void UI::changePlayer()
{
	if (player == _PLAYER_BLACK)
	{
		player = _PLAYER_WHITE;
	}
	else
	{
		player = _PLAYER_BLACK;
	}

	promptSentence = _ENTER_TO_SELECT;
}

void UI::movePiece()
{
	printSentence("                       ", 77, 44, _TEXT_COLOUR);

	if (!newGame)
	{
		printSentence(prompt[player], 77, 36, _TEXT_COLOUR);
		printSentence("select piece.   ", 77, 39, _TEXT_COLOUR);
	}
	else newGame = false;

	if (player == _PLAYER_BLACK)
	{
		int x, y;
		x = 21;
		y = 7;
		gotoxy(x, y);

		int key = _getch();
		while (key != 13 || gameColour[x - 21][y - 7] != _PIECE_COLOUR_BLACK)
		{
			if (key == 224) key = _getch();

			switch (key)
			{
			case 15:
				loadBoard();
				return;
				break;

			case 80:
				y += 3;
				if (y == 22) y += 3;
				break;

			case 72:
				y -= 3;
				if (y == 22) y -= 3;
				break;

			case 77:
				x += 4;
				break;

			case 75:
				x -= 4;
				break;

			case 19:
				saveBoard();
				break;

			case 26:
				undo();
				printSentence(prompt[player], 77, 36, _TEXT_COLOUR);
				printSentence("select piece.   ", 77, 39, _TEXT_COLOUR);
				break;
			}

			while (x > 53) x -= 4;
			while (x < 21) x += 4;
			while (y > 37) y -= 3;
			while (y < 7) y += 3;

			gotoxy(x, y);

			key = _getch();
		}

		gameColour[x - 21][y - 7] = _SELECTED_COLOUR_BLACK;

		gotoxy(x + 1, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x - 21][y - 7]);
		std::cout << "\b";
		printChessPiece(gameBoard[x - 21][y - 7]);
		gotoxy(x, y);

		promptSentence = 3;
		printSentence("select location.", 77, 39, _TEXT_COLOUR);

		findValidPlaces(gameBoard[x - 21][y - 7], x - 21, y - 7);
		if (gameBoard[x - 21][y - 7] == "C") // Elephants cannot cross the river.
		{
			for (int y1 = 18; y1 <= 30; y1 += 3) for (int x1 = 0; x1 <= 32; x1 += 4) if (gameColour[x1][y1] == _HIGHLIGHT_COLOUR)
			{
				unHighlight(x1, y1);
			}
		}
		

		x0 = x;
		y0 = y;

		gotoxy(x0, y0);

		key = _getch();
		while (key != 13 || (x0 == x && y0 == y) || (gameColour[x - 21][y - 7] != _HIGHLIGHT_COLOUR))
		{
			if (key == 224) key = _getch();

			switch (key)
			{

			case 80:
				y += 3;
				if (y == 22) y += 3;
				break;

			case 72:
				y -= 3;
				if (y == 22) y -= 3;
				break;

			case 77:
				x += 4;
				break;

			case 75:
				x -= 4;
				break;
			}

			while (x > 53) x -= 4;
			while (x < 21) x += 4;
			while (y > 37) y -= 3;
			while (y < 7) y += 3;

			gotoxy(x, y);

			key = _getch();
		}

		move(x0, y0, x, y, _PIECE_COLOUR_BLACK);
		lastMove = _PIECE_COLOUR_BLACK;

		for (int y1 = 0; y1 <= 30; y1 += 3) for (int x1 = 0; x1 <= 32; x1 += 4) if (gameColour[x1][y1] == _HIGHLIGHT_COLOUR)
		{
			unHighlight(x1, y1);
		}

		promptSentence = 2;

		x1 = x;
		y1 = y;

		gotoxy(x, y);
	}
	else
	{
		int x, y;
		x = 21;
		y = 25;
		gotoxy(x, y);

		int key = _getch();
		while (key != 13 || (x0 == x && y0 == y) || gameColour[x - 21][y - 7] != _PIECE_COLOUR_WHITE)
		{
			if (key == 224) key = _getch();

			switch (key)
			{
			case 15:
				loadBoard();
				return;
				break;

			case 19:
				saveBoard();
				break;

			case 80:
				y += 3;
				if (y == 22) y += 3;
				break;

			case 72:
				y -= 3;
				if (y == 22) y -= 3;
				break;

			case 77:
				x += 4;
				break;

			case 75:
				x -= 4;
				break;

			case 26:
				undo();
				printSentence(prompt[player], 77, 36, _TEXT_COLOUR);
				printSentence("select piece.   ", 77, 39, _TEXT_COLOUR);
				break;
			}

			while (x > 53) x -= 4;
			while (x < 21) x += 4;
			while (y > 37) y -= 3;
			while (y < 7) y += 3;

			gotoxy(x, y);

			key = _getch();
		}

		gameColour[x - 21][y - 7] = _SELECTED_COLOUR_WHITE;

		gotoxy(x + 1, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x - 21][y - 7]);
		std::cout << "\b";
		printChessPiece(gameBoard[x - 21][y - 7]);
		gotoxy(x, y);

		promptSentence = 3;
		printSentence("select location.", 77, 39, _TEXT_COLOUR);

		findValidPlaces(gameBoard[x - 21][y - 7], x - 21, y - 7);
		if (gameBoard[x - 21][y - 7] == "J") // Elephants cannot cross the river.
		{
			for (int y1 = 0; y1 <= 12; y1 += 3) for (int x1 = 0; x1 <= 32; x1 += 4) if (gameColour[x1][y1] == _HIGHLIGHT_COLOUR)
			{
				unHighlight(x1, y1);
			}
		}

		x0 = x;
		y0 = y;

		gotoxy(x0, y0);

		key = _getch();
		while (key != 13 || (x0 == x && y0 == y) || (gameColour[x - 21][y - 7] != _HIGHLIGHT_COLOUR))
		{
			if (key == 224) key = _getch();

			switch (key)
			{
			case 80:
				y += 3;
				if (y == 22) y += 3;
				break;

			case 72:
				y -= 3;
				if (y == 22) y -= 3;
				break;

			case 77:
				x += 4;
				break;

			case 75:
				x -= 4;
				break;
			}
			while (x > 53) x -= 4;
			while (x < 21) x += 4;
			while (y > 37) y -= 3;
			while (y < 7) y += 3;

			gotoxy(x, y);

			key = _getch();
		}
		move(x0, y0, x, y, _PIECE_COLOUR_WHITE);
		lastMove = _PIECE_COLOUR_WHITE;
		promptSentence = 2;

		for (int y1 = 0; y1 <= 30; y1 += 3) for (int x1 = 0; x1 <= 32; x1 += 4) if (gameColour[x1][y1] == _HIGHLIGHT_COLOUR)
		{
			unHighlight(x1, y1);
		}

		x1 = x;
		y1 = y;

		gotoxy(x, y);
	}

	updateHistory();
	printHistory();
	noMove = false;

	checkIfWon();
}

void UI::move(short x0, short y0, short x, short y, int colour)
{
	lastEaten = gameBoard[x - 21][y - 7];
	lastEaten_Colour = _BOARD_COLOUR;
	for (int i = 1; i < 15; i++) if (chessPieceABC[i] == lastEaten)
	{
		if (i < 8) lastEaten_Colour = _PIECE_COLOUR_BLACK;
		else if (i > 7) lastEaten_Colour = _PIECE_COLOUR_WHITE;
	}

	gameBoard[x - 21][y - 7] = gameBoard[x0 - 21][y0 - 7];
	gameColour[x - 21][y - 7] = colour;

	gameBoard[x0 - 21][y0 - 7] = defaultGameBoard[x0 - 21][y0 - 7];
	gameColour[x0 - 21][y0 - 7] = _BOARD_COLOUR;

	if (x0 - 20 < 33)
	{
		gameBoard[x0 - 20][y0 - 7] = defaultGameBoard[x0 - 20][y0 - 7];
		gameColour[x0 - 20][y0 - 7] = _BOARD_COLOUR;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x0 - 20][y0 - 7]);
		gotoxy(x0 + 2, y0);
		std::cout << "\b" << gameBoard[x0 - 20][y0 - 7];
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BGBOLDER_COLOUR);
		gotoxy(x0 + 2, y0);
		std::cout << "\b" << " ";
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x0 - 21][y0 - 7]);
	gotoxy(x0 + 1, y0);
	std::cout << "\b" << gameBoard[x0 - 21][y0 - 7];

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x - 21][y - 7]);
	gotoxy(x + 1, y);
	std::cout << "\b";
	printChessPiece(gameBoard[x - 21][y - 7]);

}

void UI::undo()
{
	if (!noMove)
	{

		gameBoard[x0 - 21][y0 - 7] = gameBoard[x1 - 21][y1 - 7];
		gameColour[x0 - 21][y0 - 7] = gameColour[x1 - 21][y1 - 7];

		gameBoard[x1 - 21][y1 - 7] = lastEaten;
		gameColour[x1 - 21][y1 - 7] = lastEaten_Colour;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x0 - 21][y0 - 7]);
		gotoxy(x0 + 1, y0);
		std::cout << "\b";
		if (gameBoard[x0 - 21][y0 - 7] != "+" && gameBoard[x0 - 21][y0 - 7] != "--" && gameBoard[x0 - 21][y0 - 7] != "|" && gameBoard[x0 - 21][y0 - 7] != " ")
		{
			printChessPiece(gameBoard[x0 - 21][y0 - 7]);
		}
		else
		{
			std::cout << gameBoard[x0 - 21][y0 - 7];

			if (x0 - 20 < 33)
			{
				gameBoard[x0 - 20][y0 - 7] = defaultGameBoard[x0 - 20][y0 - 7];

				gotoxy(x0 + 2, y0);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BOARD_COLOUR);
				std::cout << "\b" << gameBoard[x0 - 20][y0 - 7];

			}
			else
			{
				gotoxy(x0 + 2, y0);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BGBOLDER_COLOUR);
				std::cout << "\b ";
			}
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x1 - 21][y1 - 7]);
		gotoxy(x1 + 1, y1);
		std::cout << "\b";
		if (gameBoard[x1 - 21][y1 - 7] != "+" && gameBoard[x1 - 21][y1 - 7] != "--" && gameBoard[x1 - 21][y1 - 7] != "|" && gameBoard[x1 - 21][y1 - 7] != " ")
		{
			printChessPiece(gameBoard[x1 - 21][y1 - 7]);
		}
		else
		{
			std::cout << gameBoard[x1 - 21][y1 - 7];

			if (x1 - 20 < 33)
			{
				gameBoard[x1 - 20][y1 - 7] = defaultGameBoard[x1 - 20][y1 - 7];

				gotoxy(x1 + 2, y1);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BOARD_COLOUR);
				std::cout << "\b" << gameBoard[x1 - 20][y1 - 7];

			}
			else
			{
				gotoxy(x1 + 2, y1);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BGBOLDER_COLOUR);
				std::cout << "\b ";
			}
		}

		noMove = true;

		// historyList.erase(historyList.end() - 1);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BGBOLDER_COLOUR);
		gotoxy(78, 2 + historyList.size());
		std::cout << "                   ";

		historyList.erase(historyList.end() - 1);

		if (player == _PLAYER_WHITE)
		{
			player = _PLAYER_BLACK;
			movePiece();
			player = _PLAYER_WHITE;
		}
		else
		{
			player = _PLAYER_WHITE;
			movePiece();
			player = _PLAYER_BLACK;
		}
	}
}

void UI::updateHistory()
{
	string sentence;
	string piece = gameBoard[x1 - 21][y1 - 7];

	if (lastMove == _PIECE_COLOUR_BLACK) sentence = "黑: ";
	else sentence = "紅: ";

	if (piece == "A") sentence = sentence + "將 ";
	else if (piece == "B") sentence = sentence + "士 ";
	else if (piece == "C") sentence = sentence + "象 ";
	else if (piece == "D") sentence = sentence + "車 ";
	else if (piece == "E") sentence = sentence + "馬 ";
	else if (piece == "F") sentence = sentence + "包 ";
	else if (piece == "G") sentence = sentence + "卒 ";
	else if (piece == "H") sentence = sentence + "師 ";
	else if (piece == "I") sentence = sentence + "仕 ";
	else if (piece == "J") sentence = sentence + "相 ";
	else if (piece == "K") sentence = sentence + "車 ";
	else if (piece == "L") sentence = sentence + "傌 ";
	else if (piece == "M") sentence = sentence + "炮 ";
	else if (piece == "N") sentence = sentence + "兵 ";

	if (x1 != x0) // Moves horizontally or diagonally.
	{
		if (y1 == y0)
		{
			if (lastMove == _PIECE_COLOUR_BLACK)
			{
				sentence = sentence + (char)((x0 - 17) / 4 + 48) + " 平 " + (char)((x1 - 17) / 4 + 48);
			}
			else
			{
				int digit = 10 - (x0 - 17) / 4;
				if (digit == 1) sentence = sentence + "一";
				else if (digit == 2) sentence = sentence + "二";
				else if (digit == 3) sentence = sentence + "三";
				else if (digit == 4) sentence = sentence + "四";
				else if (digit == 5) sentence = sentence + "五";
				else if (digit == 6) sentence = sentence + "六";
				else if (digit == 7) sentence = sentence + "七";
				else if (digit == 8) sentence = sentence + "八";
				else if (digit == 9) sentence = sentence + "九";

				sentence = sentence + " 平 ";

				digit = 10 - (x1 - 17) / 4;
				if (digit == 1) sentence = sentence + "一";
				else if (digit == 2) sentence = sentence + "二";
				else if (digit == 3) sentence = sentence + "三";
				else if (digit == 4) sentence = sentence + "四";
				else if (digit == 5) sentence = sentence + "五";
				else if (digit == 6) sentence = sentence + "六";
				else if (digit == 7) sentence = sentence + "七";
				else if (digit == 8) sentence = sentence + "八";
				else if (digit == 9) sentence = sentence + "九";
			}
		}
		else
		{
			if (y1 > y0 && lastMove == _PIECE_COLOUR_BLACK)
			{
				sentence = sentence + (char)((x0 - 17) / 4 + 48) + " 進 " + (char)((x1 - 17) / 4 + 48);
			}
			else if (y1 < y0 && lastMove == _PIECE_COLOUR_BLACK)
			{
				sentence = sentence + (char)((x0 - 17) / 4 + 48) + " 退 " + (char)((x1 - 17) / 4 + 48);
			}
			else if (y1 < y0 && lastMove == _PIECE_COLOUR_WHITE)
			{
				int digit = 10 - (x0 - 17) / 4;
				if (digit == 1) sentence = sentence + "一";
				else if (digit == 2) sentence = sentence + "二";
				else if (digit == 3) sentence = sentence + "三";
				else if (digit == 4) sentence = sentence + "四";
				else if (digit == 5) sentence = sentence + "五";
				else if (digit == 6) sentence = sentence + "六";
				else if (digit == 7) sentence = sentence + "七";
				else if (digit == 8) sentence = sentence + "八";
				else if (digit == 9) sentence = sentence + "九";

				sentence = sentence + " 進 ";

				digit = 10 - (x1 - 17) / 4;
				if (digit == 1) sentence = sentence + "一";
				else if (digit == 2) sentence = sentence + "二";
				else if (digit == 3) sentence = sentence + "三";
				else if (digit == 4) sentence = sentence + "四";
				else if (digit == 5) sentence = sentence + "五";
				else if (digit == 6) sentence = sentence + "六";
				else if (digit == 7) sentence = sentence + "七";
				else if (digit == 8) sentence = sentence + "八";
				else if (digit == 9) sentence = sentence + "九";
			}
			else if (y1 > y0 && lastMove == _PIECE_COLOUR_WHITE)
			{
				int digit = 10 - (x0 - 17) / 4;
				if (digit == 1) sentence = sentence + "一";
				else if (digit == 2) sentence = sentence + "二";
				else if (digit == 3) sentence = sentence + "三";
				else if (digit == 4) sentence = sentence + "四";
				else if (digit == 5) sentence = sentence + "五";
				else if (digit == 6) sentence = sentence + "六";
				else if (digit == 7) sentence = sentence + "七";
				else if (digit == 8) sentence = sentence + "八";
				else if (digit == 9) sentence = sentence + "九";

				sentence = sentence + " 退 ";

				digit = 10 - (x1 - 17) / 4;
				if (digit == 1) sentence = sentence + "一";
				else if (digit == 2) sentence = sentence + "二";
				else if (digit == 3) sentence = sentence + "三";
				else if (digit == 4) sentence = sentence + "四";
				else if (digit == 5) sentence = sentence + "五";
				else if (digit == 6) sentence = sentence + "六";
				else if (digit == 7) sentence = sentence + "七";
				else if (digit == 8) sentence = sentence + "八";
				else if (digit == 9) sentence = sentence + "九";
			}
		}
		
	}
	else if (x1 == x0 && y1 != y0) // Moves vertically.
	{
		bool crossRiver = false;

		if (y1 < y0)
		{
			for (int i = y1; i <= y0; i += 3)
			{
				if (i == 22)
				{
					crossRiver = true;
					break;
				}
			}
		}
		else if (y0 < y1)
		{
			for (int i = y1; i >= y0; i -= 3)
			{
				if (i == 22)
				{
					crossRiver = true;
					break;
				}
			}
		}
	
		if (y1 > y0 && lastMove == _PIECE_COLOUR_BLACK)
		{
			if (crossRiver) sentence = sentence + (char)((x0 - 17) / 4 + 48) + " 進 " + (char)((y1 - y0) / 3 + 47);
			else sentence = sentence + (char)((x0 - 17) / 4 + 48) + " 進 " + (char)((y1 - y0) / 3 + 48);
		}
		else if (y1 < y0 && lastMove == _PIECE_COLOUR_BLACK)
		{
			if (crossRiver) sentence = sentence + (char)((x0 - 17) / 4 + 48) + " 退 " + (char)((y0 - y1) / 3 + 47);
			else sentence = sentence + (char)((x0 - 17) / 4 + 48) + " 退 " + (char)((y0 - y1) / 3 + 48);
		}
		else if (y1 < y0 && lastMove == _PIECE_COLOUR_WHITE)
		{
			int digit = 10 - (x0 - 17) / 4;

			if (digit == 1) sentence = sentence + "一";
			else if (digit == 2) sentence = sentence + "二";
			else if (digit == 3) sentence = sentence + "三";
			else if (digit == 4) sentence = sentence + "四";
			else if (digit == 5) sentence = sentence + "五";
			else if (digit == 6) sentence = sentence + "六";
			else if (digit == 7) sentence = sentence + "七";
			else if (digit == 8) sentence = sentence + "八";
			else if (digit == 9) sentence = sentence + "九";

			sentence = sentence + " 進 ";

			digit = (y0 - y1) / 3;

			if (crossRiver) digit--;

			if (digit == 1) sentence = sentence + "一";
			else if (digit == 2) sentence = sentence + "二";
			else if (digit == 3) sentence = sentence + "三";
			else if (digit == 4) sentence = sentence + "四";
			else if (digit == 5) sentence = sentence + "五";
			else if (digit == 6) sentence = sentence + "六";
			else if (digit == 7) sentence = sentence + "七";
			else if (digit == 8) sentence = sentence + "八";
			else if (digit == 9) sentence = sentence + "九";
		}
		else if (y1 > y0 && lastMove == _PIECE_COLOUR_WHITE)
		{
			int digit = 10 - (x0 - 17) / 4;

			if (digit == 1) sentence = sentence + "一";
			else if (digit == 2) sentence = sentence + "二";
			else if (digit == 3) sentence = sentence + "三";
			else if (digit == 4) sentence = sentence + "四";
			else if (digit == 5) sentence = sentence + "五";
			else if (digit == 6) sentence = sentence + "六";
			else if (digit == 7) sentence = sentence + "七";
			else if (digit == 8) sentence = sentence + "八";
			else if (digit == 9) sentence = sentence + "九";

			sentence = sentence + " 退 ";

			digit = (y1 - y0) / 3;

			if (crossRiver) digit--;

			if (digit == 1) sentence = sentence + "一";
			else if (digit == 2) sentence = sentence + "二";
			else if (digit == 3) sentence = sentence + "三";
			else if (digit == 4) sentence = sentence + "四";
			else if (digit == 5) sentence = sentence + "五";
			else if (digit == 6) sentence = sentence + "六";
			else if (digit == 7) sentence = sentence + "七";
			else if (digit == 8) sentence = sentence + "八";
			else if (digit == 9) sentence = sentence + "九";
		}
	}
	if (historyList.size() < _HISTORY_SIZE)
	{
		historyList.push_back(sentence);
	}
	else
	{
		historyList.erase(historyList.begin());
		historyList.push_back(sentence);
	}
}

void UI::printHistory()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _TEXT_COLOUR);

	for (int i = 0; i < historyList.size(); i++)
	{
		gotoxy(78, 3 + i);
		std::cout << historyList[i];
	}

	
}

void UI::printChessPiece(string piece)
{
	if (piece == "A") std::cout << "將";
	else if (piece == "B") std::cout << "士";
	else if (piece == "C") std::cout << "象";
	else if (piece == "D") std::cout << "車";
	else if (piece == "E") std::cout << "馬";
	else if (piece == "F") std::cout << "包";
	else if (piece == "G") std::cout << "卒";
	else if (piece == "H") std::cout << "師";
	else if (piece == "I") std::cout << "仕";
	else if (piece == "J") std::cout << "相";
	else if (piece == "K") std::cout << "車";
	else if (piece == "L") std::cout << "傌";
	else if (piece == "M") std::cout << "炮";
	else if (piece == "N") std::cout << "兵";
}

bool UI::isGameWon() { return gameWon; }

void UI::checkIfWon()
{
	bool aliveA = false;
	bool aliveH = false;

	for (int y = 0; y < 31; y++) for (int x = 0; x < 33; x++)
	{
		if (gameBoard[x][y] == "A") aliveA = true;
		if (gameBoard[x][y] == "H") aliveH = true;
	}

	gameWon = aliveA ^ aliveH;

	if (gameWon)
	{
		if (aliveA)
		{
			printSentenceAnimated("BLACK has won the game!", 77, 44, _TEXT_COLOUR);
		}
		else
		{
			printSentenceAnimated("RED has won the game!", 77, 44, _TEXT_COLOUR);
			printSentence("  ", 98, 44, _TEXT_COLOUR);
			gotoxy(98, 44);
		}
		
	}

	gotoxy(x1, y1);
}

void UI::saveBoard()
{
	printSentence("Overwrite memory? (Y/N)", 77, 44, _TEXT_COLOUR);
	int key = _getch();

	while (key != 121 && key != 110) key = _getch();

	if (key == 110) return;
	else
	{
		ioStream.open("memory.txt", ios::out); // 33 31 9x 11y

		if (!ioStream.is_open()) return;

		for (int y = 0; y < 31; y += 3)
		{
			if (y == 22) continue;
			for (int x = 0; x < 33; x += 4)
			{
				int i;
				for (i = 1; i < 15; i++) if (chessPieceABC[i] == gameBoard[x][y])
				{
					ioStream << i << " ";
					break;
				}

				if (i == 15) ioStream << 0 << " ";
			}
			ioStream << endl;
		}

		ioStream.close();
		printSentence("Game is saved!         ", 77, 44, _TEXT_COLOUR);
	}

}

void UI::loadBoard()
{
	printSentence("Overwrite board? (Y/N)", 77, 44, _TEXT_COLOUR);
	int key = _getch();

	while (key != 121 && key != 110) key = _getch();

	if (key == 110) return;
	else
	{
		ioStream.open("memory.txt", ios::in); // 33 31 9x 11y

		if (!ioStream.is_open()) return;

		for (int y = 0; y < 31; y++) for (int x = 0; x < 33; x++)
		{
			gameBoard[x][y] = defaultGameBoard[x][y];
			gameColour[x][y] = _BOARD_COLOUR;
		}

		string input;
		for (int y = 0; y < 31; y += 3)
		{
			if (y == 22) continue;
			for (int x = 0; x < 33; x += 4)
			{
				ioStream >> input;

				if (input == "0") gameBoard[x][y] = "+";
				else
				{
					gameBoard[x][y] = chessPieceABC[stoi(input)];

					if (stoi(input) < 8) gameColour[x][y] = _PIECE_COLOUR_BLACK;
					else if (stoi(input) > 7) gameColour[x][y] = _PIECE_COLOUR_WHITE;
					
					gameBoard[x][y] = gameBoard[x][y];
					gameColour[x][y] = gameColour[x][y];
				}
				
			}
		}

		ioStream.close();

		// Initial values.

		clearHistory();
		player = _PLAYER_WHITE;
		promptSentence = _ENTER_TO_SELECT;

		x0 = -1;
		y0 = -1;
		x1 = -1;
		y1 = -1;

		newGame = true;
		gameWon = false;

		lastEaten = "+";
		lastEaten_Colour = _BOARD_COLOUR;
		noMove = true;

		printBoard();

		printSentence("Game is loaded!        ", 77, 44, _TEXT_COLOUR);

		movePiece();
	}
}

void UI::clearHistory()
{
	for (int i = 0; i < historyList.size(); i++)
	{
		gotoxy(78, 3 + i);
		std::cout << "                   ";
	}

	historyList.clear();
}

void UI::highlight(const int x, const int y) // x, y of gameBoard
{
	gameColour[x][y] = _HIGHLIGHT_COLOUR;
	// gameColour[x + 1][y] = _HIGHLIGHT_COLOUR;

	gotoxy(x + 22, y + 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x][y]);
	std::cout << "\b";

	if (gameBoard[x][y] != "+" && gameBoard[x][y] != "--" && gameBoard[x][y] != "|" && gameBoard[x][y] != " ") printChessPiece(gameBoard[x][y]);
	else
	{
		std::cout << gameBoard[x][y];
		// std::cout << " ";
	}

	gotoxy(x + 21, y + 7);
}

void UI::unHighlight(const int x, const int y) // x, y of gameBoard
{
	if (gameBoard[x][y] != "+" && gameBoard[x][y] != "--" && gameBoard[x][y] != "|" && gameBoard[x][y] != " ")
	{
		for (int i = 1; i < 15; i++) if (chessPieceABC[i] == gameBoard[x][y])
		{
			if (i < 8)
			{
				gameColour[x][y] = _PIECE_COLOUR_BLACK;
				// if (x + 1 < 33) gameColour[x + 1][y] = _PIECE_COLOUR_BLACK;
			}
			else if (i > 7)
			{
				gameColour[x][y] = _PIECE_COLOUR_WHITE;
				// if (x + 1 < 33) gameColour[x + 1][y] = _PIECE_COLOUR_WHITE;
			}

			break;
		}
	}
	else
	{
		gameColour[x][y] = _BOARD_COLOUR;
		// if (x + 1 < 33) gameColour[x + 1][y] = _BOARD_COLOUR;
	}

	gotoxy(x + 22, y + 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameColour[x][y]);
	std::cout << "\b";
	if (gameBoard[x][y] != "+" && gameBoard[x][y] != "--" && gameBoard[x][y] != "|" && gameBoard[x][y] != " ") printChessPiece(gameBoard[x][y]);
	else std::cout << gameBoard[x][y];

	/*if (x + 1 < 33) std::cout << gameBoard[x + 1][y];
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _BGBOLDER_COLOUR);
		std::cout << " ";
	}*/
}

void UI::findValidPlaces(const string chessPc, const int x, const int y)
{
	if (player == _PLAYER_BLACK)
	{
		/*
		const int blackCastle[][2] =
		{
			{12, 0}, {16, 0}, {20, 0},
			{12, 3}, {16, 3}, {20, 3},
			{12, 6}, {16, 6}, {20, 6}
		};
		*/

		if (chessPc == "A") // Black general.
		{
			int possiblePlaces[][2] =
			{
				{x, y - 3},
			{x - 4, y}, {x + 4, y},
				{x, y + 3}
			};

			for (int i = 0; i < 8; i++)
			{
				if ((possiblePlaces[i][0] >= 12 && possiblePlaces[i][0] <= 20) && (possiblePlaces[i][1] >= 0 && possiblePlaces[i][1] <= 6) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_BLACK)) // if it's inside the board and is not occupied by an ally.
				{
					highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
				}
			}
		}
		else if (chessPc == "B") // Black mandarins.
		{
			int possiblePlaces[][2] =
			{
				{x - 4, y - 3}, {x + 4, y - 3},
				{x - 4, y + 3}, {x + 4, y + 3}
			};

			for (int i = 0; i < 8; i++)
			{
				if ((possiblePlaces[i][0] >= 12 && possiblePlaces[i][0] <= 20) && (possiblePlaces[i][1] >= 0 && possiblePlaces[i][1] <= 6) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_BLACK)) // if it's inside the board and is not occupied by an ally.
				{
					highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
				}
			}
		}
		else if (chessPc == "E") // Black horses.
		{ 
			int possiblePlaces[8][2] =
			{
				{x - 8, y + 3}, {x - 4, y + 6}, {x + 4, y + 6}, {x + 8, y + 3},
				{x - 8, y - 3}, {x - 4, y - 6}, {x + 4, y - 6}, {x + 8, y - 3}
			};

			if (y == 12) for (int i = 0; i < 4; i++) possiblePlaces[i][1] += 3;

			for (int i = 0; i < 8; i++)
			{
				if ((possiblePlaces[i][0] >= 0 && possiblePlaces[i][0] <= 32) && (possiblePlaces[i][1] >= 0 && possiblePlaces[i][1] <= 30) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_BLACK)) // if it's inside the board and is not occupied by an ally.
				{
					highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
				}
			}
		}
		else if (chessPc == "D") // Black carriages.
		{
			for (int y1 = y - 3; y1 >= 0; y1 -= 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x, y1);
			}

			for (int y1 = y + 3; y1 <= 30; y1 += 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x, y1);
			}

			for (int x1 = x - 4; x1 >= 0; x1 -= 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x1, y);
					break;
				}
				else
					highlight(x1, y);
			}

			for (int x1 = x + 4; x1 <= 32; x1 += 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x1, y);
					break;
				}
				else
					highlight(x1, y);
			}
		}
		else if (chessPc == "C") // Black elephants.
		{
			int x1, y1;

			x1 = x - 4;
			for (y1 = y - 3; y1 >= 0 && x1 >= 0; y1 -= 3, x1 -= 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

			x1 = x + 4;
			for (y1 = y - 3; y1 >= 0 && x1 <= 32; y1 -= 3, x1 += 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

			x1 = x - 4;
			for (y1 = y + 3; y1 <= 30 && x1 >= 0; y1 += 3, x1 -= 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

			x1 = x + 4;
			for (y1 = y + 3; y1 <= 30 && x1 <= 32; y1 += 3, x1 += 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

		}
		else if (chessPc == "G") // Black soldiers.
		{
			if (y < 15 && y + 3 != 15)
				highlight(x, y + 3);
			else if (y < 15 && y + 3 == 15)
				highlight(x, y + 6);
			else
			{
				int possiblePlaces[][2] =
				{
						{x, y + 3},
				  {x - 4, y},{x + 4, y}
				};

				for (int i = 0; i < 3; i++)
				{
					if ((possiblePlaces[i][0] >= 0 && possiblePlaces[i][0] <= 32) && (possiblePlaces[i][1] >= 0 && possiblePlaces[i][1] <= 30) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_BLACK)) // if it's inside the board and is not occupied by an ally.
					{
						highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
					}
				}
			}
		}
		else if (chessPc == "F") // Black cannon.
		{
			// Same as Black carriages, but with different eating rules.
			bool findFriend;

			findFriend = false;
			for (int y1 = y - 3; y1 >= 0; y1 -= 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x, y1);
						break;
					}
				}
				else if (y1 != 15 && !findFriend)
					highlight(x, y1);
			}

			findFriend = false;
			for (int y1 = y + 3; y1 <= 30; y1 += 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x, y1);
						break;
					}
				}
				else if (y1 != 15 && !findFriend)
					highlight(x, y1);
			}

			findFriend = false;
			for (int x1 = x - 4; x1 >= 0; x1 -= 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x1, y);
						break;
					}
				}
				else if (!findFriend)
					highlight(x1, y);
			}

			findFriend = false;
			for (int x1 = x + 4; x1 <= 32; x1 += 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x1, y);
						break;
					}
				}
				else if (!findFriend)
					highlight(x1, y);
			}

		}
	}
	else if (player == _PLAYER_WHITE)
	{
		/*
		const int whiteCastle[][2] =
		{
			{12, 24}, {16, 24}, {20, 24},
			{12, 27}, {16, 27}, {20, 27},
			{12, 30}, {16, 30}, {20, 30}
		};
		*/

		if (chessPc == "H") // White general.
		{
			int possiblePlaces[][2] =
			{
				{x, y - 3},
			{x - 4, y}, {x + 4, y},
				{x, y + 3}
			};

			for (int i = 0; i < 8; i++)
			{
				if ((possiblePlaces[i][0] >= 12 && possiblePlaces[i][0] <= 20) && (possiblePlaces[i][1] >= 24 && possiblePlaces[i][1] <= 30) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_WHITE)) // if it's inside the board and is not occupied by an ally.
				{
					highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
				}
			}
		}
		else if (chessPc == "I") // White mandarins.
		{
			int possiblePlaces[][2] =
			{
				{x - 4, y - 3}, {x + 4, y - 3},
				{x - 4, y + 3}, {x + 4, y + 3}
			};

			for (int i = 0; i < 8; i++)
			{
				if ((possiblePlaces[i][0] >= 12 && possiblePlaces[i][0] <= 20) && (possiblePlaces[i][1] >= 24 && possiblePlaces[i][1] <= 30) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_WHITE)) // if it's inside the board and is not occupied by an ally.
				{
					highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
				}
			}
		}
		else if (chessPc == "L") // White horses.
		{ 
			int possiblePlaces[8][2] =
			{
				{x - 8, y + 3}, {x - 4, y + 6}, {x + 4, y + 6}, {x + 8, y + 3},
				{x - 8, y - 3}, {x - 4, y - 6}, {x + 4, y - 6}, {x + 8, y - 3}
			};

			if (y == 18) for (int i = 4; i < 8; i++) possiblePlaces[i][1] -= 3;

			for (int i = 0; i < 8; i++)
			{
				if ((possiblePlaces[i][0] >= 0 && possiblePlaces[i][0] <= 32) && (possiblePlaces[i][1] >= 0 && possiblePlaces[i][1] <= 30) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_WHITE)) // if it's inside the board and is not occupied by an ally.
				{
					highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
				}
			}
		}
		else if (chessPc == "K") // White carriages.
		{
			for (int y1 = y - 3; y1 >= 0; y1 -= 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x, y1);
			}

			for (int y1 = y + 3; y1 <= 30; y1 += 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x, y1);
			}

			for (int x1 = x - 4; x1 >= 0; x1 -= 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x1, y);
					break;
				}
				else
					highlight(x1, y);
			}

			for (int x1 = x + 4; x1 <= 32; x1 += 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x1, y);
					break;
				}
				else
					highlight(x1, y);
			}
		}
		else if (chessPc == "J") // White elephants.
		{
			int x1, y1;

			x1 = x - 4;
			for (y1 = y - 3; y1 >= 0 && x1 >= 0; y1 -= 3, x1 -= 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

			x1 = x + 4;
			for (y1 = y - 3; y1 >= 0 && x1 <= 32; y1 -= 3, x1 += 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

			x1 = x - 4;
			for (y1 = y + 3; y1 <= 30 && x1 >= 0; y1 += 3, x1 -= 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

			x1 = x + 4;
			for (y1 = y + 3; y1 <= 30 && x1 <= 32; y1 += 3, x1 += 4)
				if (gameColour[x1][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					break;
				}
				else if (gameColour[x1][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					highlight(x1, y1);
					break;
				}
				else if (y1 != 15)
					highlight(x1, y1);

		}
		else if (chessPc == "N") // White soldiers.
		{
			if (y > 15 && y - 3 != 15)
				highlight(x, y - 3);
			else if (y > 15 && y - 3 == 15)
				highlight(x, y - 6);
			else
			{
				int possiblePlaces[][2] =
				{
						{x, y - 3},
				  {x - 4, y},{x + 4, y}
				};

				for (int i = 0; i < 3; i++)
				{
					if ((possiblePlaces[i][0] >= 0 && possiblePlaces[i][0] <= 32) && (possiblePlaces[i][1] >= 0 && possiblePlaces[i][1] <= 30) && (gameColour[possiblePlaces[i][0]][possiblePlaces[i][1]] != _PIECE_COLOUR_BLACK)) // if it's inside the board and is not occupied by an ally.
					{
						highlight(possiblePlaces[i][0], possiblePlaces[i][1]);
					}
				}
			}
		}
		else if (chessPc == "M") // White cannon.
		{
			// Same as Black carriages, but with different eating rules.
			bool findFriend;

			findFriend = false;
			for (int y1 = y - 3; y1 >= 0; y1 -= 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x, y1);
						break;
					}
				}
				else if (y1 != 15 && !findFriend)
					highlight(x, y1);
			}

			findFriend = false;
			for (int y1 = y + 3; y1 <= 30; y1 += 3)
			{
				if (gameColour[x][y1] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x][y1] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x, y1);
						break;
					}
				}
				else if (y1 != 15 && !findFriend)
					highlight(x, y1);
			}

			findFriend = false;
			for (int x1 = x - 4; x1 >= 0; x1 -= 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x1, y);
						break;
					}
				}
				else if (!findFriend)
					highlight(x1, y);
			}

			findFriend = false;
			for (int x1 = x + 4; x1 <= 32; x1 += 4)
			{
				if (gameColour[x1][y] == _PIECE_COLOUR_WHITE) // Blocked by an ally.
				{
					if (!findFriend) findFriend = true;
				}
				else if (gameColour[x1][y] == _PIECE_COLOUR_BLACK) // Blocked by an enemy.
				{
					if (!findFriend) break;
					else if (findFriend)
					{
						highlight(x1, y);
						break;
					}
				}
				else if (!findFriend)
					highlight(x1, y);
			}

		}
	}
} 