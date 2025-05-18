#ifndef GRIDTETROMINO_H
#define GRIDTETROMINO_H

#include "Tetromino.h"


/**
 * @class GridTetromino
 * @brief Represents a Tetromino piece with grid-based positioning on a game board.
 *
 * The GridTetromino class extends the basic Tetromino functionality by adding:
 *  - A grid location (`gridLoc`) on the game board to track the position of the tetromino .
 *  - Methods to set and retrieve the grid location of tetromino.
 *  - A method to obtain a vector of block locations mapped to the current grid location.
 *
 * This allows the tetromino to be positioned on a grid, making it easier to integrate
 * into a game board for games like Tetris.
 */
class GridTetromino : public Tetromino
{
private:
	/// <summary>
	/// Represents the current position of this tetromino on the grid (gameboard) as [x, y].
	/// This location updates each time the tetromino moves.
	/// </summary>
	Point gridLoc;


public:
	/// <summary>
	/// Constructor initializes gridLoc to (0, 0)
	/// </summary>
	GridTetromino();


	/// <summary>
	/// Retrieves the current grid location of the tetromino.
	/// </summary>
	/// <returns>A const reference to the gridLoc (of type Point), representing the tetromino's position on the grid.</returns>
	const Point& getGridLoc() const;


	/// <summary>
	/// Sets the grid location of the tetromino to the specified coordinates.
	/// </summary>
	/// <param name="x">The x-coordinate of the new grid location.</param>
	/// <param name="y">The y-coordinate of the new grid location.</param>
	void setGridLoc(const int x, const int y);


	/// <summary>
	/// Sets the grid location of the tetromino to the specified Point.
	/// </summary>
	/// <param name="gridLoc">A Point representing the new grid location.</param>
	void setGridLoc(const Point& pt);


	/// <summary>
	/// Moves the grid location of the tetromino by the specified offsets.
	/// </summary>
	/// <param name="xOffset">The x offset (distance) to move: (1,0) moves right, (-1,0) moves left.</param>
	/// <param name="yOffset">The y offset (distance) to move: (0,1) moves down.</param>
	void move(const int xOffset, const int yOffset);

	/// <summary>
	/// Builds and returns a vector of Points representing the block locations relative to the grid location.
	/// </summary>
	/// <remarks>
	/// Maps each point in the inherited blockLocs vector to the current gridLoc of this tetromino.
	/// For example, if blockLocs contains a point [x, y] and gridLoc is [5, 6],
	/// the resulting mapped point would be [5 + x, 6 + y].
	/// </remarks>
	/// <returns>A vector of Points, each adjusted to the grid location.</returns>
	const std::vector<Point> getBlockLocsMappedToGrid() const;

	/// <summary>
	/// Allows unit testing class to access private members.
	/// </summary>
	friend class TestSuite3;
};

#endif /* GRIDTETROMINO_H */