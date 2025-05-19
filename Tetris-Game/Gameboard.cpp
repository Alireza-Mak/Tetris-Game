#include "Gameboard.h"
#include <iomanip>
#include <cassert>


Gameboard::Gameboard() {
	empty();
};

void Gameboard::empty() {
	for (int row = 0; row < MAX_Y; row++) {
		fillRow(row, EMPTY_BLOCK);
	}
};

void Gameboard::printToConsole() const{
	for (size_t row = 0; row < MAX_Y; row++) {
		for (size_t col = 0; col < MAX_X; col++)
		{
			int value = grid[row][col];
			if (value == EMPTY_BLOCK) {
				std::cout << '.' << std::setw(2);
			}
			else {
				std::cout << value << std::setw(2);
			}
		}
		std::cout << '\n';
	}
	std::cout << '\n';
};

int Gameboard::getContent(const Point& point) const {
	assert(isValidPoint(point));
	return grid[point.getY()][point.getX()];
};

int Gameboard::getContent(int x, int y) const {
	assert(isValidPoint(x, y));
	return grid[y][x];
};

void Gameboard::setContent(const Point& point, int content) {
	if (isValidPoint(point)) {
		grid[point.getY()][point.getX()] = content;
	}
};

void Gameboard::setContent(int x, int y, int content) {
	if (isValidPoint(x, y)) {
		grid[y][x] = content;
	}
};

void Gameboard::setContent(const std::vector<Point> points, int content) {
	for (const auto& point : points) {
		if (isValidPoint(point)) {
			grid[point.getY()][point.getX()] = content;
		}
	}

};

bool Gameboard::areAllLocsEmpty(const std::vector<Point>points) const {
	for (const auto& point : points) {
		if (isValidPoint(point)) {
			if (grid[point.getY()][point.getX()] != EMPTY_BLOCK) {
				return false;
			}
		}
	}
	return true;
};

int Gameboard::removeCompletedRows() {
	std::vector<int> completedRows = getCompletedRowIndices();
	removeRows(completedRows);
	return completedRows.size();
};


const Point& Gameboard::getSpawnLoc() const {
	return spawnLoc;
};

bool Gameboard::isValidPoint(const Point& point) const {
	return isValidPoint(point.getX(), point.getY());
};

bool Gameboard::isValidPoint(int x, int y) const {
	return x > EMPTY_BLOCK && x <= MAX_X && y > EMPTY_BLOCK && y <= MAX_Y;
};

bool Gameboard::isRowCompleted(int row) const {
	assert(row >= 0 && row < MAX_Y && "row index is out of bounds");
	for (int col = 0; col < MAX_X; col++) {
		if (grid[row][col] == EMPTY_BLOCK) {
			return false;
		}
	}
	return true;
};

void Gameboard::fillRow(int row, int content) {
	for (int col = 0; col < MAX_X; col++) {
		grid[row][col] = content;
	}
};

std::vector<int> Gameboard::getCompletedRowIndices() const {
	std::vector<int> completedRows;
	for (int row = 0; row < MAX_Y; row++) {
		if (isRowCompleted(row)) {
			completedRows.push_back(row);
		}
	}
	return completedRows;
};

void Gameboard::copyRowIntoRow(int sourceRow, int targetRow) {
	assert(sourceRow >= 0 && sourceRow < MAX_Y);
	assert(targetRow >= 0 && targetRow < MAX_Y);
	for (int col = 0; col < MAX_X; col++) {
		grid[targetRow][col] = grid[sourceRow][col];
	}
};

void Gameboard::removeRow(int row) {
	assert(row >= EMPTY_BLOCK && row < MAX_Y);
	for (int y = row - 1; y >= 0; y--) {
		copyRowIntoRow(y, y + 1);
	}
	fillRow(0, EMPTY_BLOCK);
};

void Gameboard::removeRows(const std::vector<int> rows) {
	for (const auto& row : rows) {
		removeRow(row);
	}
};


