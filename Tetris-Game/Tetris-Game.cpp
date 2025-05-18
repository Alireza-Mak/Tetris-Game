#include <iostream>
#include "Gameboard.h"
#include "TestSuite1.h"
#include "TestSuite2.h"
#include <SFML/Graphics.hpp>


int main()
{
	// A test suite is a collection of tests that are run to verify the functionality of Tetromino Class.
	TestSuite1::runTestSuite1();

	// A test suite is a collection of tests that are run to verify the functionality of Gameboard Class.
	TestSuite2::runTestSuite2();

    // Simple SFML test to confirm graphics rendering works on x86 systems.
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

	return  0;
}
