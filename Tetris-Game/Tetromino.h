#ifndef TETROMINO_H
#define TETROMINO_H

#include <iostream>
#include <vector>
#include "Point.h"


// Enum representing the available Tetromino colors.
enum class TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE };


// Enum representing the 7 classic Tetromino shapes.
enum TetShape { S, Z, L, J, O, I, T, COUNT };

// Namespace holding constant values related to Tetromino grid logic.
namespace const_vals {
    constexpr int block_size = 4;
    const Point start_grid(-3, 3);
    const Point end_grid(3, -3);
}

/// <summary>
/// Represents a single Tetromino piece in the Tetris game,
/// including its shape, color, and the positions of its individual blocks.
/// Provides functionality for rotation, shape assignment, and console display.
/// </summary>
class Tetromino {
private:
    TetColor color;                   // Color of the Tetromino
    TetShape shape;                   // Shape type of the Tetromino

protected:
    std::vector<Point> blockLocs;     // Locations of individual blocks that make up the Tetromino

public:
    /// <summary>
    /// Default constructor that initializes a Tetromino with default shape and color.
    /// </summary>
    Tetromino();

    /// <summary>
    /// Gets the color of the Tetromino.
    /// </summary>
    /// <returns>TetColor value</returns>
    TetColor getColor() const;

    /// <summary>
    /// Gets the shape type of the Tetromino.
    /// </summary>
    /// <returns>TetShape enum</returns>
    TetShape getShape() const;

    /// <summary>
    /// Sets the shape of the Tetromino and updates its block positions accordingly.
    /// </summary>
    /// <param name="shape">The TetShape to assign</param>
    void setShape(const TetShape& shape);

    /// <summary>
    /// Rotates the Tetromino's blocks 90 degrees clockwise.
    /// </summary>
    void rotateClockwise();

    /// <summary>
    /// Outputs the Tetromino block positions to the console for debugging or visualization.
    /// </summary>
    void printToConsole() const;


    /// <summary>
    /// Returns a random TetShape by generating a random number within the range of available shapes.
    /// </summary>
    /// <returns>A random TetShape.</returns>
    static TetShape getRandomShape();

    /// <summary>
    /// Allows unit testing class to access private members.
    /// </summary>
    friend class TestSuite1;
};

#endif
// !POINT_H