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
	void PrintGrid(char board[3][3])
	{
		for (int i = 0;i < 3;i++)
		{
			for (int j = 0;j < 3;j++)
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
		bool placed = false;
		while (!placed) {
			int r = rand() % 3;
			int c = rand() % 3;
			if (grid[r][c] == '-') {
				grid[r][c] = 'O';
				placed = true;
				outFile << ' ' << gameIndex << "O" << " " << r + 1 << c + 1;
			}
		}
	}
	bool EndGame(char board[3][3])
	{
		for (int i = 0;i < 3;i++)
			for (int j = 0;j < 3;j++)
				if (board[i][j] == '-')
					return false;
		return true;
	}
	bool Winner(char board[3][3], char player)
	{
		for (int i = 0;i < 3;i++)
			if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
				return true;
		for (int i = 0;i < 3;i++)
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