#include "TestSuite.h"
#include "Point.h"
#include "Tetromino.h"

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
	// run some sanity tests on our classes to ensure they're working as expected.
	TestSuite::runTestSuite();

	// Interactive test for manually verifying Tetromino shape changes and rotations.
	Tetromino tet;
    std::string input;

    std::cout << "Interactive Tetromino Tester\n";
    std::cout << "---------------------------------\n";
    std::cout << "Controls:\n";
    std::cout << "  r - Rotate clockwise\n";
    std::cout << "  s, z, l, j, o, i, t - Change shape\n";
    std::cout << "  q - Quit\n";
    std::cout << "---------------------------------\n";

    tet.printToConsole();

    while (true) {
        std::cout << "\nEnter input: ";
        std::getline(std::cin, input);
        if (input.empty()) continue;
        char command = input[0];

        switch (command) {
            case 'r':
                tet.rotateClockwise();
                break;
            case 's':
                tet.setShape(S);
                break;
            case 'z':
                tet.setShape(Z);
                break;
            case 'l':
                tet.setShape(L);
                break;
            case 'j':
                tet.setShape(J);
                break;
            case 'o':
                tet.setShape(O);
                break;
            case 'i':
                tet.setShape(I);
                break;
            case 't':
                tet.setShape(T);
                break;
            case 'q':
                std::cout << "Exiting tester.\n";
                return 0;
            default:
                std::cout << "Invalid input. Try again.\n";
        }

        // Display Tetromino state after action
        tet.printToConsole();
    }
}
