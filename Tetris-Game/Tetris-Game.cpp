#include "TestSuite.h"
#include "Point.h"
#include "Tetromino.h"
#include "Gameboard.h"

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void handleShapeCommand(Tetromino& t, TetShape shape) {
	t.setShape(shape);
	t.printToConsole();
}

int main()
{
	//Testing Gameboard's methods 
    Gameboard board;
    Point pt1{ 1,1 };
    Point pt2{ 2,2 };

    board.setContent(pt1, 1);
    board.setContent(pt2, 2);
    board.fillRow(3, 3);
    board.printToConsole();

	std::cout << board.getContent(pt1) << "\n";		//expected: 1
	std::cout << board.getContent(3, 3) << "\n";;	//expected: 3
	std::cout << board.isRowCompleted(1) << "\n";;	//expected: 0
	std::cout << board.isRowCompleted(3) << "\n";;	//expected: 1

	for (size_t i = 0; i < Gameboard::MAX_Y; i++)
	{
		board.fillRow(i,i);
	}
	board.removeRow(18);						//remove the lowest row
	board.removeRow(18);						//remove the lowest row
	board.printToConsole();

	std::vector<int> rowIndices = board.getCompletedRowIndices();
	for (auto& i : rowIndices) {
		std::cout << i << " ";
	}


}
