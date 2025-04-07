#include "Point.h"

void Point::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void Point::swapXY() {
	int temp = this->x;
	this->x = this->y;
	this->y = temp;
};

void Point::multiplyX(int factor) {
	this->x *= factor;
};

void Point::multiplyY(int factor) {
	this->y *= factor;

}

std::string Point::toString() const {
	return "["+ std::to_string(this->x) + "," + std::to_string(this->y) + "]";
};