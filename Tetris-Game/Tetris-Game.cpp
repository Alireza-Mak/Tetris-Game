#include"Tetris-Game.h"

const int TetrisGame::BLOCK_WIDTH = 32;
const int TetrisGame::BLOCK_HEIGHT = 32;
const double TetrisGame::MAX_SECONDS_PER_TICK = 0.75;
const double TetrisGame::MIN_SECONDS_PER_TICK = 0.20;
const int TetrisGame::SCORE_FONT_SIZE = 18;

TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset):
	window{ window }, blockSprite{ blockSprite }, gameboardOffset{ gameboardOffset }, nextShapeOffset{ nextShapeOffset }
{
	reset();
	// setup our font for drawing the score
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf"))
	{
		assert(false && "Missing font: RedOctober.ttf");
	};
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(SCORE_FONT_SIZE);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(SCORE_INFO::X_POS, SCORE_INFO::Y_POS);
};

void TetrisGame::draw() {
	drawGameboard();
};

void TetrisGame::onKeyPressed(sf::Event event) {};

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {};

void TetrisGame::tick() {};

void TetrisGame::reset() {};

void TetrisGame::pickNextShape() {};

bool TetrisGame::spawnNextShape() { return true; };

bool TetrisGame::attemptRotate(GridTetromino& shape) { return true; };

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) { return true; };

void TetrisGame::drop(GridTetromino& shape) {};

void TetrisGame::lock(const GridTetromino& shape) {};


void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color, float alpha) const {
	int colorIndex = static_cast<int>(color);
	blockSprite.setTextureRect(sf::IntRect(BLOCK_WIDTH * colorIndex, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
	float xPos = topLeft.getX() + xOffset * BLOCK_WIDTH;
	float yPos = topLeft.getY() + yOffset * BLOCK_HEIGHT;
	blockSprite.setPosition(sf::Vector2f(xPos, yPos));
	blockSprite.setColor(sf::Color(255, 255, 255, alpha * 255));
	window.draw(blockSprite);

};

void TetrisGame::drawGameboard() {
	board.setContent(5, 5, 2);
	for (size_t y = 0; y < board.MAX_Y; y++)
	{
		for (size_t x = 0; x < board.MAX_X; x++) {
			if (board.getContent(x, y) != board.EMPTY_BLOCK) {
				drawBlock(gameboardOffset, x, y, static_cast<TetColor>(board.getContent(x, y))); // Example usage
			}
		}
	}
};

void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft, float alpha) const {};

void TetrisGame::updateScoreDisplay() {};

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const { return true; };

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const { return true; };

void TetrisGame::determineSecondsPerTick(){};
