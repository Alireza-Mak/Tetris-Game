#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"

/// <summary>
/// Represents the Tetris-style gameboard, storing block content
/// and managing operations like filling, clearing, and rendering the grid.
/// </summary>
class Gameboard
{
public:
    static const int MAX_X = 10;
    static const int MAX_Y = 19;
    static const int EMPTY_BLOCK = -1;

private:
    int grid[MAX_Y][MAX_X];
    const Point spawnLoc{ MAX_X / 2, 0 };

public:
    /// <summary>
    /// Initializes the grid with EMPTY_BLOCK.
    /// </summary>
    Gameboard();

    /// <summary>
    /// Fills the entire gameboard with EMPTY_BLOCK.
    /// </summary>
    void empty();

    /// <summary>
    /// Prints the contents of the grid to the console for debugging.
    /// </summary>
    void printToConsole() const;

    /// <summary>
    /// Retrieves the content at a specific Point on the grid.
    /// </summary>
    /// <param name="point">The Point to retrieve content from.</param>
    /// <returns>Content value at the given point.</returns>
    int getContent(const Point& point) const;

    /// <summary>
    /// Retrieves the content at specific x, y coordinates on the grid.
    /// </summary>
    /// <param name="x">X-coordinate.</param>
    /// <param name="y">Y-coordinate.</param>
    /// <returns>Content value at the given coordinates.</returns>
    int getContent(int x, int y) const;

    /// <summary>
    /// Sets the content at a specific Point on the grid.
    /// </summary>
    /// <param name="point">The Point to set content at.</param>
    /// <param name="content">Content value to set.</param>
    void setContent(const Point& point, int content);

    /// <summary>
    /// Sets the content at specific x, y coordinates on the grid.
    /// </summary>
    /// <param name="x">X-coordinate.</param>
    /// <param name="y">Y-coordinate.</param>
    /// <param name="content">Content value to set.</param>
    void setContent(int x, int y, int content);

    /// <summary>
    /// Sets the content at a list of Points on the grid.
    /// </summary>
    /// <param name="points">List of Points to set content at.</param>
    /// <param name="content">Content value to set.</param>
    void setContent(const std::vector<Point> points, int content);

    /// <summary>
    /// Checks if all valid Points in a list are empty.
    /// </summary>
    /// <param name="points">List of Points to check.</param>
    /// <returns>True if all valid points are EMPTY_BLOCK, otherwise false.</returns>
    bool areAllLocsEmpty(const std::vector<Point> points) const;

    /// <summary>
    /// Removes all completed rows from the grid.
    /// </summary>
    /// <returns>The number of completed rows removed.</returns>
    int removeCompletedRows();

    /// <summary>
    /// Gets the spawn location of new tetrominos.
    /// </summary>
    /// <returns>The spawn Point.</returns>
    const Point& getSpawnLoc() const;

private:
    bool isValidPoint(const Point& point) const;
    bool isValidPoint(int x, int y) const;
    bool isRowCompleted(int row) const;
    void fillRow(int row, int content);
    std::vector<int> getCompletedRowIndices() const;
    void copyRowIntoRow(int sourceRow, int targetRow);

    /// <summary>
    /// Removes a specific row by shifting all rows above it down.
    /// </summary>
    /// <param name="row">The row index to remove.</param>
    void removeRow(int row);

    /// <summary>
    /// Removes multiple rows from the grid.
    /// </summary>
    /// <param name="rows">Vector of row indices to remove.</param>
    void removeRows(const std::vector<int> rows);

    /// <summary>
    /// Adds the main function for the purpose of testing
    /// </summary>
    friend int main();

    /// <summary>
	/// Adds the TestSuite2 class for the purpose of testing
    /// </summary>
    friend class TestSuite2;
};

#endif /* GAMEBOARD_H */

