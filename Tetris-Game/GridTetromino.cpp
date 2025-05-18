#include "GridTetromino.h"

GridTetromino::GridTetromino(): gridLoc(0,0) {}

const Point& GridTetromino::getGridLoc() const {
	return gridLoc;
};

void GridTetromino::setGridLoc(int x, int y) {
	gridLoc = Point(x, y);
};

void GridTetromino::setGridLoc(const Point& newGridLoc) {
	gridLoc = newGridLoc;
};

void GridTetromino::move(int xOffset, int yOffset) {
	gridLoc = Point(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
};

const std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const{
	std::vector<Point> mappedBlockLocs;
	for (const auto& blockLoc : blockLocs) {
		mappedBlockLocs.push_back(Point(blockLoc.getX() + gridLoc.getX(), blockLoc.getY() + gridLoc.getY()));
	}
	return mappedBlockLocs;
};
