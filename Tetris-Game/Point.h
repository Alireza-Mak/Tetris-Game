#include <iostream>
#ifndef POINT_H
#define POINT_H

#include <string>

/// <summary>
/// Point class represents a 2D coordinate with integer x and y values.
/// Provides basic operations for coordinate manipulation, useful in grid-based games like Tetris.
/// </summary>
class Point {
private:
    int x; ///< X-coordinate
    int y; ///< Y-coordinate

public:
    /// <summary>
    /// Default constructor initializing point at (0, 0)
    /// </summary>
    Point() : x(0), y(0) {};

    /// <summary>
    /// Constructor initializing point with given x and y values
    /// </summary>
    /// <param name="x">Initial X-coordinate</param>
    /// <param name="y">Initial Y-coordinate</param>
    Point(int x, int y) { setXY(x, y); };

    /// <summary>
    /// Gets the X-coordinate
    /// </summary>
    /// <returns>Value of x</returns>
    int getX() const { return x; };

    /// <summary>
    /// Gets the Y-coordinate
    /// </summary>
    /// <returns>Value of y</returns>
    int getY() const { return y; };

    /// <summary>
    /// Sets the X-coordinate
    /// </summary>
    /// <param name="x">New X value</param>
    void setX(int x) { this->x = x; };

    /// <summary>
    /// Sets the Y-coordinate
    /// </summary>
    /// <param name="y">New Y value</param>
    void setY(int y) { this->y = y; };

    /// <summary>
    /// Sets both X and Y coordinates
    /// </summary>
    /// <param name="x">New X value</param>
    /// <param name="y">New Y value</param>
    void setXY(int x, int y);

    /// <summary>
    /// Swaps the X and Y coordinate values
    /// </summary>
    void swapXY();

    /// <summary>
    /// Multiplies the X-coordinate by a factor
    /// </summary>
    /// <param name="factor">Multiplier for X</param>
    void multiplyX(int factor);

    /// <summary>
    /// Multiplies the Y-coordinate by a factor
    /// </summary>
    /// <param name="factor">Multiplier for Y</param>
    void multiplyY(int factor);

    /// <summary>
    /// Converts the point to a string in the format "(x, y)"
    /// </summary>
    /// <returns>String representation of the point</returns>
    std::string toString() const;

    /// <summary>
    /// Grants access to private members for testing
    /// </summary>
    friend class TestSuite1;

    /// <summary>
    /// Allows unit testing class to access private members.
    /// </summary>
    friend class TestSuite3;
};

#endif
// POINT_H