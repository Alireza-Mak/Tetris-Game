#ifndef POINT_H
#define POINT_H
#include <string>

class Point {
private:
	int x;
	int y;
public:
	// default constructor
	Point() : x(0), y(0) {}; // default constructor
	Point(int x, int y) : x(x), y(y) {}; // constructor with 2 params
	int getX() const { return x; }; // get x
	int getY() const { return y; }; // get y
	void setX(int x); // set x
	void setY(int y); // set y
	void swapXY(); // swap x and y
	void multiplyX(int factor); // multiply x by factor
	void multiplyY(int factor); // multiply y by factor
	std::string toString() const; // to string
};

#endif
