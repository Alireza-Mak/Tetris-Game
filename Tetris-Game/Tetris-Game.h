#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "Gameboard.h"
#include "GridTetromino.h"
#include <SFML/Graphics.hpp>
#include<cassert>
#include <SFML/Audio.hpp>

/// <summary>
/// Contains constants related to scoring and display position in the game.
/// Includes score values for clearing rows and default score,
/// as well as X and Y coordinates for score display.
/// </summary>
namespace SCORE_INFO {
	const int ONE_ROW = 40;
	const int TWO_ROWS = 100;
	const int THREE_ROWS = 300;
	const int FOUR_ROWS = 1200;
	const int DEFAULT_SCORE = 0;
	const int X_POS = 425;
	const int Y_POS = 325;
}

/// <summary>
/// Contains constants for game sound effects and music, including file names, directory path,
/// and default music volume level.
/// </summary>

namespace SONGS {
	const std::string SOUND_DIRECTORY = "sfx/";
	const std::string DROP_BLOCK = "blockDrop.ogg";
	const std::string ROTATE_BLOCK = "blockRotate.ogg";
	const std::string ROW_COMPLETED = "levelUp.ogg";
	const std::string GAME_OVER = "gameOver.ogg";
	const std::string TETRIS_MUSIC = "tetrisMusic.ogg";
	const int MUSIC_VOLUME = 10;
}

/**
 * @class TetrisGame
 * @brief Manages core Tetris game logic, rendering, and controls for a single player.
 *
 * This class encapsulates the essentials for an individual Tetris game instance,
 * including board setup, tetromino management, user input handling, and drawing
 * routines. Designed to support multiplayer scenarios, it operates independently
 * of shared resources managed in main.cpp (e.g., background and tetromino sprites).
  */
class TetrisGame
{
public:
	// STATIC CONSTANTS
	static const int BLOCK_WIDTH;						// pixel width of a tetris block, init to 32
	static const int BLOCK_HEIGHT;						// pixel height of a tetris block, int to 32
	static const double MAX_SECONDS_PER_TICK;			// the slowest "tick" rate (in seconds), init to 0.75
	static const double MIN_SECONDS_PER_TICK;			// the fastest "tick" rate (in seconds), init to 0.20
	static const int SCORE_FONT_SIZE;					// the font size of the score text display
	static const double SCORE_TICK_REDUCTION_FACTOR;	// Higher values make the game speed increase slower with score
	static const float GHOST_ALPHA;						// Transparency level for the ghost piece (between 0 and 1)

private:	
	// MEMBER VARIABLES

	// State members ---------------------------------------------
	int score;									// the current game score.
    Gameboard board;							// the gameboard (grid) to represent where all the blocks are.
    GridTetromino nextShape;					// the tetromino shape that is "on deck".
    GridTetromino currentShape;					// the tetromino that is currently falling.
	GridTetromino ghostShape;					// the tetromino that is a ghost on the board.
	
	// Graphics members ------------------------------------------
	sf::Sprite& blockSprite;		// the sprite used for all the blocks.
	sf::RenderWindow& window;		// the window that we are drawing on.
	const Point gameboardOffset;	// pixel XY offset of the gameboard on the screen
	const Point nextShapeOffset;	// pixel XY offset to the nextShape

	sf::Font scoreFont;				// SFML font for displaying the score.
	sf::Text scoreText;				// SFML text object for displaying the score

	sf::SoundBuffer buffer;         // Stores audio data for short sound effects
	sf::Sound soundRotateBlock;     // Plays block rotation sound effect
	sf::Music music;                // Plays background music in a loop

									
	// Time members ----------------------------------------------
	// Note: a "tick" is the amount of time it takes a block to fall one line.
	double secondsPerTick = MAX_SECONDS_PER_TICK; // the seconds per tick (changes depending on score)	

	double secondsSinceLastTick{ 0.0 };			// update this every game loop until it is >= secsPerTick,
												// we then know to trigger a tick.  Reduce this var (by a tick) & repeat.
	bool shapePlacedSinceLastGameLoop{ false };	// Tracks whether we have placed (locked) a shape on
												// the gameboard in the current gameloop	
public:
	// MEMBER FUNCTIONS

	/// <summary>
	/// Initializes a new TetrisGame instance, setting up the game state, loading the font,
	/// and configuring the score text display.
	/// <param name="window">Reference to the SFML RenderWindow for drawing.</param>
	/// <param name="blockSprite">Reference to the SFML Sprite used to render each Tetris block.</param>
	/// <param name="gameboardOffset">Offset position of the gameboard on the screen.</param>
	/// <param name="nextShapeOffset">Offset position for displaying the next shape (on-deck).</param>
	/// </summary>
	TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset);

	/// <summary>
	/// Draws all game elements, including the gameboard, current and next tetromino shapes,
	/// and the score. This function is called every game loop to refresh the display.
	/// </summary>
	void draw();								

	/// <summary>
	/// Handles keypress events for game controls, including up, left, right, down, and space.
	/// Processes player input during the game loop.
	/// <param name="keypress">The keypress event to be processed.</param>
	/// </summary>
	void onKeyPressed(sf::Event event);


	/// <summary>
	/// Called every game loop to handle the timing for game ticks and tetromino placement. 
	/// Advances the game by one tick if enough time has passed since the last tick.
	/// <param name="secondsSinceLastLoop">Time elapsed since the last game loop.</param>
	/// <summary>
	void processGameLoop(float secondsSinceLastLoop);

	/// <summary>
	/// Advances the game state by one tick, attempting to move the current tetromino down by one row.
	/// If the move is not possible, the tetromino is locked in place on the gameboard.
	/// </summary>
	void tick();

private:
	/// <summary>
	/// Resets the game to its initial state, including score, gameboard, tick rate, 
	/// and setting up the current and next tetromino shapes.
	/// </summary>
	void reset();

	/// <summary>
	/// Assigns a new random shape to the `nextShape` tetromino.
	/// This function generates a random shape and sets it as the upcoming tetromino.
	/// </summary>
	void pickNextShape();
	
	/// <summary>
	/// Sets `currentShape` to `nextShape` and positions it at the spawn location.
	/// Checks if `currentShape` is in a valid position to start.
	/// <returns>True if `currentShape` is in a valid position, false otherwise.</returns>
	/// </summary>
	bool spawnNextShape();																	

	/// <summary>
	/// Attempts to rotate the given tetromino clockwise. Creates a temporary copy, rotates it, 
	/// and checks if the rotation is legal. If legal, applies the rotation to the original tetromino.
	/// <param name="shape">The tetromino to attempt to rotate.</param>
	/// <returns>True if the rotation was successful, false otherwise.</returns>
	/// </summary>
	bool attemptRotate(GridTetromino& shape);

	/// <summary>
	/// Attempts to move the tetromino by the specified x and y offsets. 
	/// Creates a temporary copy of the tetromino, moves it, and checks if the new position is legal. 
	/// If legal, applies the move to the original tetromino.
	/// <param name="shape">The tetromino to attempt to move.</param>
	/// <param name="x">The x offset for the move.</param>
	/// <param name="y">The y offset for the move.</param>
	/// <returns>True if the move was successful, false otherwise.</returns>
	/// </summary>
	bool attemptMove(GridTetromino& shape, int x, int y);

	/// <summary>
	/// Drops the tetromino down to the lowest possible position on the gameboard.
	/// <param name="shape">The tetromino to drop.</param>
	/// </summary>
	void drop(GridTetromino& shape);

	/// <summary>
	/// Locks the tetromino in place by copying its blocks' colors to the gameboard grid.
	/// Uses the tetromino's mapped locations to set the grid content, and marks that a shape 
	/// has been placed since the last game loop.
	/// <param name="shape">The tetromino to lock onto the gameboard.</param>
	/// </summary>
	void lock(const GridTetromino& shape);

	/// <summary>
	/// Updates the ghost shape by cloning the current shape and moving it downward until it reaches the lowest legal position.
	/// </summary>
	void updateGhostShape();

	/// <summary>
	/// Loads a sound file and plays it if successfully loaded.
	/// If the file is missing, an assertion error is triggered with a message.
	/// </summary>
	/// <param name="fileName">The name of the sound file to load, located in the "sfx/" folder.</param>
	void addSound(const std::string& fileName);
	
	// Graphics methods ==============================================
	
	/// <summary>
	/// Draws a single Tetris block sprite on the canvas at a specified position and with a specified color.
	/// The block position is calculated based on:
	///    1) The top-left corner offset of the gameboard (in pixels).
	///    2) An x and y offset into the gameboard (in blocks, not pixels), 
	///       which needs to be multiplied by BLOCK_WIDTH and BLOCK_HEIGHT to convert to pixels.
	/// <param name="topLeft">The top-left position of the gameboard in pixels.</param>
	/// <param name="xOffset">The x-offset of the block within the gameboard, in blocks.</param>
	/// <param name="yOffset">The y-offset of the block within the gameboard, in blocks.</param>
	/// <param name="color">The color of the Tetris block, which determines the texture portion to use.</param>
	/// <param name="alpha">The alpha transparency value for the block (default is 1.0 for fully opaque).</param>
	/// </summary>
	void drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color, float alpha = 1.0f) const;
										

	/// <summary>
	/// Draws all non-empty blocks on the gameboard by iterating through each cell in the grid. 
	/// For each block that isn't empty, it calls drawBlock() to render the block at the appropriate 
	/// screen position, using the specified gameboard offset and the color indicated in the gameboard content.
	/// </summary>
	void drawGameboard();
	
	/// <summary>
	/// Draws the given tetromino on the window by iterating through each of its blocks 
	/// and calling drawBlock() for each one. The topLeft point serves as the base position 
	/// from which individual block offsets are calculated.
	/// <param name="tetromino">The tetromino to draw, with its blocks mapped to the grid.</param>
	/// <param name="topLeft">The top-left position on the screen to use as a base point for drawing.</param>
	/// <param name="alpha">The alpha transparency value for the block (default is 1.0 for fully opaque).</param>
	/// </summary>
	void drawTetromino(const GridTetromino& tetromino, const Point& topLeft, float alpha = 1.0f) const;


	/// <summary>
	/// Updates the score display text with the current score. Converts the score to a string 
	/// and formats it to show "Score: ##", then updates the scoreText object for display.
	/// </summary>
	void updateScoreDisplay();

	// State & gameplay/logic methods ================================

	/// <summary>
	/// Checks if the tetromino can be placed legally at its current position on the gameboard.
	/// Uses Gameboard's areAllLocsEmpty() to verify that the tetromino's mapped locations are empty.
	/// <param name="shape">The tetromino to check for a valid position.</param>
	/// <returns>True if the position is within borders and the locations are empty; false otherwise.</returns>
	/// </summary>
	bool isPositionLegal(const GridTetromino& shape) const;


	/// <summary>
	/// Checks if the tetromino's blocks are within the gameboard borders.
	/// Returns false if any block is outside the left, right, or bottom edges of the board.
	/// <param name="shape">The tetromino to check.</param>
	/// <returns>True if all blocks are within the gameboard borders; false if any block is out of bounds.</returns>
	/// </summary>
	bool isWithinBorders(const GridTetromino& shape) const;


	/// <summary>
	/// Sets the game speed (seconds per tick) based on the player's score.
	/// Higher scores result in faster tick rates (lower secsPerTick values).
	/// </summary>
	void determineSecondsPerTick();

};

#endif /* TETRISGAME_H */

