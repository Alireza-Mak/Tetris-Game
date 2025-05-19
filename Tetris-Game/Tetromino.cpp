#include "Tetromino.h"


Tetromino::Tetromino() {
	blockLocs = { Point(0,0), Point(0,0), Point(0,0), Point(0,0) };
	setShape(TetShape::O);
};

TetColor Tetromino::getColor() const {
	return this->color;
};

TetShape Tetromino::getShape() const {
	return this->shape;
};

void Tetromino::setShape(const TetShape& shape) {
	this->shape = shape;
	blockLocs.at(0) = Point(0, 0);
	switch (shape)
	{
	case TetShape::O:
		color = TetColor::YELLOW;
		blockLocs.at(1) = Point(0, 1);
		blockLocs.at(2) = Point(1, 1);
		blockLocs.at(3) = Point(1, 0);
		break;
	case TetShape::I:
		color = TetColor::BLUE_LIGHT;
		blockLocs.at(1) = Point(0, 1);
		blockLocs.at(2) = Point(0, 2);
		blockLocs.at(3) = Point(0, -1);
		break;
	case TetShape::S:
		color = TetColor::RED;
		blockLocs.at(1) = Point(0, 1);
		blockLocs.at(2) = Point(1, 1);
		blockLocs.at(3) = Point(-1, 0);
		break;
	case TetShape::Z:
		color = TetColor::GREEN;
		blockLocs.at(1) = Point(1, 0);
		blockLocs.at(2) = Point(0, 1);
		blockLocs.at(3) = Point(-1, 1);
		break;
	case TetShape::L:
		color = TetColor::ORANGE;
		blockLocs.at(1) = Point(0, 1);
		blockLocs.at(2) = Point(0, -1);
		blockLocs.at(3) = Point(1, -1);
		break;
	case TetShape::J:
		color = TetColor::BLUE_DARK;
		blockLocs.at(1) = Point(0, 1);
		blockLocs.at(2) = Point(0, -1);
		blockLocs.at(3) = Point(-1, -1);
		break;
	case TetShape::T:
		color = TetColor::PURPLE;
		blockLocs.at(1) = Point(1, 0);
		blockLocs.at(2) = Point(0, -1);
		blockLocs.at(3) = Point(-1, 0);
		break;
	}
};

void Tetromino::rotateClockwise() {
	if (shape != TetShape::O) {
		for (auto& point : this->blockLocs) {
			Point new_point = point;
			new_point.multiplyX(-1);
			new_point.swapXY();
			point = new_point;
		}
	}
};

void Tetromino::printToConsole() const{
	for (int y = const_vals::start_grid.getY(); y >= const_vals::end_grid.getY(); y--) {
		for (int x = const_vals::start_grid.getX(); x <= const_vals::end_grid.getX(); x++) {
			bool found_point = false;
			for (auto& p : this->blockLocs)
			{
				if (x == p.getX() && y == p.getY()) {
					found_point = true;
					break;
				}
			}
			found_point ? std::cout << "X" : std::cout << ".";
		}
		std::cout << '\n';
	}
};


TetShape Tetromino::getRandomShape() {
	int rand_num = rand() % static_cast<int>(TetShape::COUNT);
	return static_cast<TetShape>(rand_num);
};
