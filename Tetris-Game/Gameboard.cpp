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
	for (int row = 0; row < MAX_Y; row++) {
		for (int col = 0; col < MAX_X; col++) {
			if (grid[row][col] == EMPTY_BLOCK) {
				std::cout << std::setw(2) << ".";
			}
			else {
				std::cout << std::setw(2) << grid[row][col];
			}
		}
		std::cout << std::endl;
	}
};

int Gameboard::getContent(const Point& point) const {
	assert(isValidPoint(point) && "this point is not available in grid");
	return grid[point.getY()][point.getX()];
};

int Gameboard::getContent(int x, int y) const {
	assert(isValidPoint(x, y) && "this point is not available in grid");
	return grid[y][x];
};

void Gameboard::setContent(const Point& point, int content) {
	if (isValidPoint(point)) {
		grid[point.getY()][point.getX()] = content;
	}
	else {
		std::cout << "Invalid point: " << point.getX() << ", " << point.getY() << std::endl;
	}
};

void Gameboard::setContent(int x, int y, int content) {
	if (isValidPoint(x, y)) {
		grid[y][x] = content;
	}
	else {
		std::cout << "Invalid point: " << x << ", " << y << std::endl;
	}
};

void Gameboard::setContent(const std::vector<Point> points, int content) {
	for (const auto& point : points) {
		if (isValidPoint(point)) {
			grid[point.getY()][point.getX()] = content;
		}
		else {
			std::cout << "Invalid point: " << point.getX() << ", " << point.getY() << std::endl;
		}
	}

};

bool Gameboard::areAllLocsEmpty(const std::vector<Point>points) {
	for (const auto& point : points) {
		if (isValidPoint(point)) {
			if (grid[point.getY()][point.getX()] != EMPTY_BLOCK) {
				return false;
			}
		}
		else {
			std::cout << "Invalid point: " << point.getX() << ", " << point.getY() << std::endl;
		}
	}
	return true;
};

int Gameboard::removeCompletedRows() {
	std::vector<int> completedRows = getCompletedRowIndices();
	int count = completedRows.size();
	removeRows(completedRows);
	return count;
};


const Point& Gameboard::getSpawnLoc() {
	return spawnLoc;
};

bool Gameboard::isValidPoint(const Point& point) const {
	if (point.getX() < 0 || point.getX() >= MAX_X || point.getY() < 0 || point.getY() >= MAX_Y) {
		return false;
	}
	return true;
};

bool Gameboard::isValidPoint(int x, int y) const {
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
		return false;
	}
	return true;
};

bool Gameboard::isRowCompleted(int row) {
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

std::vector<int> Gameboard::getCompletedRowIndices() {
	std::vector<int> completedRows;
	for (int row = 0; row < MAX_Y; row++) {
		if (isRowCompleted(row)) {
			completedRows.push_back(row);
		}
	}
	return completedRows;
};

void Gameboard::copyRowIntoRow(int sourceRow, int targetRow) {
	assert(sourceRow >= 0 && sourceRow < MAX_Y && "source row index is out of bounds");
	assert(targetRow >= 0 && targetRow < MAX_Y && "target row index is out of bounds");
	for (int col = 0; col < MAX_X; col++) {
		grid[targetRow][col] = grid[sourceRow][col];
	}
};

void Gameboard::removeRow(int row) {
	assert(row >= 0 && row < MAX_Y && "row index is out of bounds");
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


