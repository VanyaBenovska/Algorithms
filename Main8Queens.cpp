#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

//•	The Rows are 8, numbered from 0 to 7.
//•	The Columns are 8, numbered from 0 to 7.
//•	The left diagonals are 15, numbered from - 7 to 7. We can use the following formula to calculate the left diagonal number by row and column: leftDiag = col - row.
//•	The right diagonals are 15, numbered from 0 to 14 by the formula : rightDiag = col + row.

//Following the definitions above for our example the queen {4, 1} occupies the row 4, column 1, left diagonal -3 and right diagonal 5

const int SIZE = 8;
static std::vector<std::vector<char>> board;
static int countOfSolutions = 0;

static std::set<int> attackedRows;
static std::set<int> attackedCols;
static std::set<int> attackedLeftDiagonals;
static std::set<int> attackedRightDiagonals;

void PrintSolution() {
	std::ostringstream oss;
	oss << "......................................" << std::endl;
	for (int i = 0; i < SIZE; i++) {		
		for (int j = 0; j < SIZE; j++) {			 
			if (board[i][j] == 'q') {
				oss << "q ";
			}
			else {
				oss << ". ";
			}
			oss << " ";
		}
		oss << std::endl;
	}
	std::cout << oss.str() << std::endl;
}

bool CanPlaceQueen(int row, int col) {
	//if (attackedRows.contains(row) ||
		//)
	if (attackedRows.find(row) != attackedRows.end() ||
		attackedCols.find(col) != attackedCols.end() ||
		attackedLeftDiagonals.find(col - row) != attackedLeftDiagonals.end() ||
		attackedRightDiagonals.find(col + row) != attackedRightDiagonals.end()
		) {
		return false;
	}
	return true;
}

void MarkAllAttackedPositions(int row, int col) {
	board[row][col] = 'q';
	attackedRows.insert(row);
	attackedCols.insert(col);
	attackedLeftDiagonals.insert(col - row);
	attackedRightDiagonals.insert(col + row);
}

void UnmarkAllAttackedPositions(int row, int col) {
	board[row][col] = '.';
	attackedRows.erase(row);
	attackedCols.erase(col);
	attackedLeftDiagonals.erase(col - row);
	attackedRightDiagonals.erase(col + row);
}

void PutQueens(int row)
{
	if (row == SIZE) {
		countOfSolutions++;
		PrintSolution();
	}
	else {
		for (int col = 0; col < SIZE; col++) {
			if (CanPlaceQueen(row, col))
			{				
				MarkAllAttackedPositions(row, col);
				PutQueens(row + 1);
				UnmarkAllAttackedPositions(row, col);
			}
		}
	}
	//CHECK
	//PrintSolution();
}

int main() {
	for (int i = 0; i < SIZE; i++) {
		std::vector<char> chV;
		for (int j = 0; j < SIZE; j++) {
			chV.push_back('.');
		}		
		board.push_back(chV);
	}
	std::cout << "8 QUEENS PUZZLE" << std::endl;

	//CHECK
	PrintSolution();

	PutQueens(0);
	std::cout << "Total count of found solutins: " << countOfSolutions << std::endl;
	return 0;
}