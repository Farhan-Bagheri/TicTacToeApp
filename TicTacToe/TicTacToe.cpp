#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

ofstream outFile("C:\\Users\\Farhan Bagheri\\Desktop\\ar.txt", ios::app);
class Game
{
	char grid[3][3] = { {'-','-','-'},{'-','-','-'},{'-','-','-'} };
	int row, column;
	bool isFull = true, endGame = false;

private:
	void PrintGrid(char board[3][3]) const
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << grid[i][j] << "   ";
			}
			cout << endl;
		}
	}
	void PlayerMove(int gameIndex)
	{
		bool placed = false;
		do
		{
			cout << "Which empty square would you choose (row column)? ";
			cin >> row >> column;
			if (grid[row - 1][column - 1] == '-')
			{
				grid[row - 1][column - 1] = 'X';
				placed = true;
				outFile << ' ' << gameIndex << "X" << " " << row << column;
			}
			else
			{
				cout << "That square is already taken!\n";
				placed = false;
			}
		} while (placed != true);
	}
	void CpuMove(int gameIndex)
	{
		int r = -1, c = -1;
		// All types of winning (8 combination)
		int lines[8][3][2] = {
			{{0,0}, {0,1}, {0,2}},  // First Line
			{{1,0}, {1,1}, {1,2}},  // Second Line
			{{2,0}, {2,1}, {2,2}},  // Third Line
			{{0,0}, {1,0}, {2,0}},  // First Row
			{{0,1}, {1,1}, {2,1}},  // Second Row
			{{0,2}, {1,2}, {2,2}},  // Third Row
			{{0,0}, {1,1}, {2,2}},  // Main Diameter
			{{0,2}, {1,1}, {2,0}}   // Sub Diameter
		};
		// First Priority: Win if possible!
		for (int i = 0; i < 8; i++) {
			int countO = 0, countEmpty = 0;
			int emptyR, emptyC;
			for (int j = 0; j < 3; j++) {
				int x = lines[i][j][0];
				int y = lines[i][j][1];
				if (grid[x][y] == 'O') countO++;
				else if (grid[x][y] == '-') {
					countEmpty++;
					emptyR = x;
					emptyC = y;
				}
			}
			if (countO == 2 && countEmpty == 1) {
				r = emptyR;
				c = emptyC;
				break;
			}
		}
		// Second Priority: Dont let opponent win!
		if (r == -1) {
			for (int i = 0; i < 8; i++) {
				int countX = 0, countEmpty = 0;
				int emptyR, emptyC;
				for (int j = 0; j < 3; j++) {
					int x = lines[i][j][0];
					int y = lines[i][j][1];
					if (grid[x][y] == 'X') countX++;
					else if (grid[x][y] == '-') {
						countEmpty++;
						emptyR = x;
						emptyC = y;
					}
				}
				if (countX == 2 && countEmpty == 1) {
					r = emptyR;
					c = emptyC;
					break;
				}
			}
		}
		// Third Priority: Take the center!
		if (r == -1 && grid[1][1] == '-') {
			r = 1;
			c = 1;
		}
		// 4th Priority: Take the corners!
		if (r == -1) {
			int corners[4][2] = { {0,0}, {0,2}, {2,0}, {2,2} };
			for (int i = 0; i < 4; i++) {
				if (grid[corners[i][0]][corners[i][1]] == '-') {
					r = corners[i][0];
					c = corners[i][1];
					break;
				}
			}
		}
		// 5th Priority: Claim the unclaimed!
		if (r == -1) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (grid[i][j] == '-') {
						r = i;
						c = j;
						break;
					}
				}
				if (r != -1) break;
			}
		}
		// Taking Action
		grid[r][c] = 'O';
		outFile << ' ' << gameIndex << "O" << " " << r + 1 << c + 1;
	}

	bool EndGame(char board[3][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (board[i][j] == '-')
					return false;
		return true;
	}
	bool Winner(char board[3][3], char player)
	{
		for (int i = 0; i < 3; i++)
			if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
				return true;
		for (int i = 0; i < 3; i++)
			if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
				return true;
		if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
			return true;
		if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
			return true;
	}
	char CheckWinner(char board[3][3], char player)
	{
		bool isWin;
		isWin = this->Winner(board, player);
		if (isWin == true)
		{
			return player;
		}
	}
public:
	void StartGame()
	{
		int gameIndex = 1;
		srand(time(0));
		this->PrintGrid(grid);

		while (endGame != true)
		{
			this->PlayerMove(gameIndex);
			if (CheckWinner(grid, 'X') == 'X')
			{
				cout << endl << "Player X is winner!" << endl;
				outFile << ' ' << 'X';
				break;
			}
			endGame = this->EndGame(grid);
			if (endGame)
			{
				cout << "Draw!";
				outFile << ' ' << 'D';
				break;
			}
			this->CpuMove(gameIndex);
			if (CheckWinner(grid, 'O') == 'O')
			{
				cout << "Player O is winner!" << endl;
				outFile << ' ' << 'O';
				break;
			}
			this->PrintGrid(grid);
			gameIndex++;
		}
		cout << "Final grid:" << endl;
		this->PrintGrid(grid);
		outFile << endl;
		outFile.close();

	}
};
int main()
{
	Game game;
	game.StartGame();
}
