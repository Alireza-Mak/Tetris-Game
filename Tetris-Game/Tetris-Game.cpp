#include <iostream>
#include "Gameboard.h"
#include "TestSuite1.h"
#include "TestSuite2.h"



int main()
{
	// A test suite is a collection of tests that are run to verify the functionality of Tetromino Class.
	TestSuite1::runTestSuite1();

	// A test suite is a collection of tests that are run to verify the functionality of Gameboard Class.
	TestSuite2::runTestSuite2();

	return  0;
}
