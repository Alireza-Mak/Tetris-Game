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
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	window.draw(scoreText);
	drawGameboard();
};

void TetrisGame::onKeyPressed(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Up:
			attemptRotate(currentShape);
			break;
		case sf::Keyboard::Left:
			attemptMove(currentShape, -1, 0);
			break;
		case sf::Keyboard::Right:
			attemptMove(currentShape, 1, 0);
			break;
		case sf::Keyboard::Down:
			attemptMove(currentShape, 0, 1);
			break;
		case sf::Keyboard::Space:
			drop(currentShape);
			break;
		default:
			break;
		}
	}
};

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
	secondsSinceLastTick += secondsSinceLastLoop;
	if (secondsSinceLastTick > secondsPerTick) {
		tick();
		secondsSinceLastTick -= secondsPerTick;
	}
	if (shapePlacedSinceLastGameLoop) {
		shapePlacedSinceLastGameLoop = false;
		if (spawnNextShape()) {
			pickNextShape();
			int rowsRemoved = board.removeCompletedRows();
			if (rowsRemoved > 0) {
				int pointsAwarded;
				switch (rowsRemoved) {
				case 1: pointsAwarded = SCORE_INFO::ONE_ROW; break;
				case 2: pointsAwarded = SCORE_INFO::TWO_ROWS; break;
				case 3: pointsAwarded = SCORE_INFO::THREE_ROWS; break;
				case 4: pointsAwarded = SCORE_INFO::FOUR_ROWS; break;
				default: pointsAwarded = SCORE_INFO::DEFAULT_SCORE; break;
				}
				score += pointsAwarded;
				updateScoreDisplay();
			}
			determineSecondsPerTick();
		}
		else {
			reset();
		}
	}
};

void TetrisGame::tick() {
	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
	}
};

void TetrisGame::reset() {
	score = 0;
	updateScoreDisplay();
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();

};

void TetrisGame::pickNextShape() {
	nextShape.setShape(Tetromino::getRandomShape());
};

bool TetrisGame::spawnNextShape() { 
	currentShape = nextShape;
	currentShape.setGridLoc(board.getSpawnLoc());
	return isPositionLegal(currentShape);
};

bool TetrisGame::attemptRotate(GridTetromino& shape) { 
	GridTetromino temp = shape;
	temp.rotateClockwise();
	if (isPositionLegal(temp)) {
		shape.rotateClockwise();
		return true;
	}
	return false;
};

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {
	GridTetromino temp = shape;
	temp.move(x, y);

	if (isPositionLegal(temp)) {
		shape.move(x, y);
		return true;
	}
	return false;
};

void TetrisGame::drop(GridTetromino& shape) {
	while (attemptMove(shape, 0, 1));
};

void TetrisGame::lock(const GridTetromino& shape) {
	std::vector<Point> blockLocs = shape.getBlockLocsMappedToGrid();
	for (auto& loc : blockLocs)
	{
		board.setContent(loc, static_cast<int>(shape.getColor()));
	}
	shapePlacedSinceLastGameLoop = true;
};


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
	for (size_t y = 0; y < board.MAX_Y; y++)
	{
		for (size_t x = 0; x < board.MAX_X; x++) {
			if (board.getContent(x, y) != board.EMPTY_BLOCK) {
				drawBlock(gameboardOffset, x, y, static_cast<TetColor>(board.getContent(x, y)));
			}
		}
	}
};

void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft, float alpha) const {
	for (auto& loc : tetromino.getBlockLocsMappedToGrid()) {
		drawBlock(topLeft, loc.getX(), loc.getY(), tetromino.getColor(), alpha);
	}
};

void TetrisGame::updateScoreDisplay() {
	std::string result = "Score: " + std::to_string(score);
	scoreText.setString(result);
};

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const { 
	return board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid()) && isWithinBorders(shape);
};

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const { 
	for (auto& loc : shape.getBlockLocsMappedToGrid()) {
		int x = loc.getX();
		int y = loc.getY();
		if (x < 0 || x >= board.MAX_X || y >= board.MAX_Y) {
			return false;
		};
	}
	return true;
};

void TetrisGame::determineSecondsPerTick(){};
