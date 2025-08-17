#include "MapMaker.hpp"

MapMaker::MapMaker() {
	for (int i = 0; i < WIDTH - 1; i++) {
		for (int j = 0; j < HEIGHT - 1; j++) {
			initialMap[i][j] == EMPTY;
			map[i][j] = EMPTY;
		}
	}

	occupied = false;

	grass.setOrigin(grass.getSize() / 2.f);
	grassForTop.setOrigin(grass.getSize() / 2.f);
	stone.setOrigin(stone.getSize() / 2.f);
	sand.setOrigin(sand.getSize() / 2.f);
	woodLog.setOrigin(woodLog.getSize() / 2.f);
	brick.setOrigin(brick.getSize() / 2.f);

	matrixBox.setSize(sf::Vector2f(660.f, 660.f));
	matrixBox.setFillColor(sf::Color::Transparent);
	matrixBox.setOutlineThickness(5.f);
	matrixBox.setOutlineColor(sf::Color::Red);
	matrixBox.setPosition(20.f, 0.f);

	clearButton.setSize(sf::Vector2f(200.f, 100.f));
	clearButton.setFillColor(sf::Color::White);
	clearButton.setOutlineThickness(5.f);
	clearButton.setOutlineColor(sf::Color::Red);

	clearButtonTxt.setFont(font);
	clearButtonTxt.setFillColor(sf::Color::Black);
	clearButtonTxt.setCharacterSize(45.f);
	clearButtonTxt.setString("Clear");

	eraseButton.setSize(sf::Vector2f(200.f, 100.f));
	eraseButton.setFillColor(sf::Color::White);
	eraseButton.setOutlineThickness(5.f);
	eraseButton.setOutlineColor(sf::Color::Red);

	eraseButtonTxt.setFont(font);
	eraseButtonTxt.setFillColor(sf::Color::Black);
	eraseButtonTxt.setCharacterSize(45.f);
	eraseButtonTxt.setString("Erase");

	grassButton.setSize(sf::Vector2f(200.f, 100.f));
	grassButton.setFillColor(sf::Color::White);
	grassButton.setOutlineThickness(5.f);
	grassButton.setOutlineColor(sf::Color::Red);

	grassButtonTxt.setFont(font);
	grassButtonTxt.setFillColor(sf::Color::Black);
	grassButtonTxt.setCharacterSize(45.f);
	grassButtonTxt.setString("Grass");

	stoneButton.setSize(sf::Vector2f(200.f, 100.f));
	stoneButton.setFillColor(sf::Color::White);
	stoneButton.setOutlineThickness(5.f);
	stoneButton.setOutlineColor(sf::Color::Red);

	stoneButtonTxt.setFont(font);
	stoneButtonTxt.setFillColor(sf::Color::Black);
	stoneButtonTxt.setCharacterSize(45.f);
	stoneButtonTxt.setString("Stone");

	sandButton.setSize(sf::Vector2f(200.f, 100.f));
	sandButton.setFillColor(sf::Color::White);
	sandButton.setOutlineThickness(5.f);
	sandButton.setOutlineColor(sf::Color::Red);

	sandButtonTxt.setFont(font);
	sandButtonTxt.setFillColor(sf::Color::Black);
	sandButtonTxt.setCharacterSize(45.f);
	sandButtonTxt.setString("Sand");

	woodLogButton.setSize(sf::Vector2f(200.f, 100.f));
	woodLogButton.setFillColor(sf::Color::White);
	woodLogButton.setOutlineThickness(5.f);
	woodLogButton.setOutlineColor(sf::Color::Red);

	woodLogButtonTxt.setFont(font);
	woodLogButtonTxt.setFillColor(sf::Color::Black);
	woodLogButtonTxt.setCharacterSize(45.f);
	woodLogButtonTxt.setString("Wood");

	brickButton.setSize(sf::Vector2f(200.f, 100.f));
	brickButton.setFillColor(sf::Color::White);
	brickButton.setOutlineThickness(5.f);
	brickButton.setOutlineColor(sf::Color::Red);

	brickButtonTxt.setFont(font);
	brickButtonTxt.setFillColor(sf::Color::Black);
	brickButtonTxt.setCharacterSize(45.f);
	brickButtonTxt.setString("Brick");

	font.loadFromFile(assets.fontAsset);

	grassTexture = std::make_unique<sf::Texture>();
	dirtTexture = std::make_unique<sf::Texture>();
	stoneTexture = std::make_unique<sf::Texture>();
	sandTexture = std::make_unique<sf::Texture>();
	woodLogTexture = std::make_unique<sf::Texture>();
	brickTexture = std::make_unique<sf::Texture>();

	grassTexture->loadFromFile(assets.grassAsset);
	dirtTexture->loadFromFile(assets.dirtAsset);
	stoneTexture->loadFromFile(assets.stoneAsset);
	sandTexture->loadFromFile(assets.sandAsset);
	woodLogTexture->loadFromFile(assets.woodLogAsset);
	brickTexture->loadFromFile(assets.brickAsset);
}

void MapMaker::Update() {
	for (int i = 0; i < HEIGHT - 1; i++) {
		for (int j = 0; j < WIDTH - 1; j++) {
			if (initialMap[i][j] == SAND) {
				if (map[i][j + 1] == EMPTY) {
					map[i][j] = EMPTY;
					map[i][j + 1] = SAND;
				}

				else if (map[i + 1][j + 1] == EMPTY) {
					map[i][j] = EMPTY;
					map[i + 1][j + 1] = SAND;
				}

				else if (map[i - 1][j + 1] == EMPTY) {
					map[i][j] = EMPTY;
					map[i - 1][j + 1] = SAND;
				}

				if (map[i - 1][j + 1] == SAND && map[i + 1][j + 1] == SAND) {
					bool choice = rand() % 2;

					if (choice)
						map[i - 1][j + 1] = SAND;
					else
						map[i + 1][j + 1] = SAND;
				}
			}
		}
	}
}

void MapMaker::placeGrass(int posX, int posY) { 
	if (posX >= 0 && posX < WIDTH && posY > 0 && posY < HEIGHT && map[posX][posY] == 0)
		map[posX][posY] = GRASS;

	else if (posX >= 0 && posX < WIDTH && posY == 0 && map[posX][posY] == 0)
		map[posX][posY] = GRASS_FOR_TOP;
}

void MapMaker::placeStone(int posX, int posY) {
	if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT && map[posX][posY] == 0)
		map[posX][posY] = STONE;
}

void MapMaker::placeSand(int posX, int posY) {
	if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT && map[posX][posY] == 0)
		map[posX][posY] = SAND;
}

void MapMaker::placeWoodLog(int posX, int posY) {
	if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT && map[posX][posY] == 0)
		map[posX][posY] = WOOD_LOG;
}

void MapMaker::placeBrick(int posX, int posY) {
	if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT && map[posX][posY] == 0)
		map[posX][posY] = BRICK;
}

void MapMaker::erase(int posX, int posY) {
	if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT)
		map[posX][posY] = EMPTY;
}

void MapMaker::setClearUIPosition() {
	clearButton.setPosition(360.f, 680.f);

	clearButtonTxt.setPosition(clearButton.getPosition().x + (clearButton.getSize().x - clearButtonTxt.getLocalBounds().width) / 2.f,
		clearButton.getPosition().y + (clearButton.getSize().y - clearButtonTxt.getLocalBounds().height) / 2.7f);
}
bool MapMaker::clearButtonPressed(sf::Vector2f pos) {
	if (isMouseOverClearButton(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		return true;
	return false;
}
void MapMaker::clear() {
	for (int i = 0; i < WIDTH - 1; i++) {
		for (int j = 0; j < HEIGHT - 1; j++) {
			initialMap[i][j] = EMPTY;
			map[i][j] = EMPTY;
		}
	}
}

void MapMaker::setEraseUIPosition() {
	eraseButton.setPosition(140.f, 680.f);

	eraseButtonTxt.setPosition(eraseButton.getPosition().x + (eraseButton.getSize().x - eraseButtonTxt.getLocalBounds().width) / 2.2f,
		eraseButton.getPosition().y + (eraseButton.getSize().y - eraseButtonTxt.getLocalBounds().height) / 2.8f);
}
bool MapMaker::eraseButtonPressed(sf::Vector2f pos) {
	if (isMouseOverEraseButton(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void MapMaker::setGrassUIPosition() {
	grassButton.setPosition(-205.f, 0.f);

	grassButtonTxt.setPosition(grassButton.getPosition().x + (grassButton.getSize().x - grassButtonTxt.getLocalBounds().width) / 2.2f,
		grassButton.getPosition().y + (grassButton.getSize().y - grassButtonTxt.getLocalBounds().height) / 2.8f);
}
bool MapMaker::grassButtonPressed(sf::Vector2f pos) {
	if (isMouseOverGrassButton(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void MapMaker::setStoneUIPosition() {
	stoneButton.setPosition(-205.f, 117.f);

	stoneButtonTxt.setPosition(stoneButton.getPosition().x + (stoneButton.getSize().x - stoneButtonTxt.getLocalBounds().width) / 2.2f,
		stoneButton.getPosition().y + (stoneButton.getSize().y - stoneButtonTxt.getLocalBounds().height) / 2.8f);
}
bool MapMaker::stoneButtonPressed(sf::Vector2f pos) {
	if (isMouseOverStoneButton(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void MapMaker::setSandUIPosition() {
	sandButton.setPosition(-205.f, 237.f);

	sandButtonTxt.setPosition(sandButton.getPosition().x + (sandButton.getSize().x - sandButtonTxt.getLocalBounds().width) / 2.2f,
		sandButton.getPosition().y + (sandButton.getSize().y - sandButtonTxt.getLocalBounds().height) / 2.8f);
}
bool MapMaker::sandButtonPressed(sf::Vector2f pos) {
	if (isMouseOverSandButton(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void MapMaker::setWoodLogUIPosition() {
	woodLogButton.setPosition(-205.f, 355.f);

	woodLogButtonTxt.setPosition(woodLogButton.getPosition().x + (woodLogButton.getSize().x - woodLogButtonTxt.getLocalBounds().width) / 2.2f,
		woodLogButton.getPosition().y + (woodLogButton.getSize().y - woodLogButtonTxt.getLocalBounds().height) / 2.8f);
}
bool MapMaker::woodLogButtonPressed(sf::Vector2f pos) {
	if (isMouseOverWoodLogButton(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void MapMaker::setBrickUIPosition() {
	brickButton.setPosition(-205.f, 475.f);

	brickButtonTxt.setPosition(brickButton.getPosition().x + (brickButton.getSize().x - brickButtonTxt.getLocalBounds().width) / 2.2f,
		brickButton.getPosition().y + (brickButton.getSize().y - brickButtonTxt.getLocalBounds().height) / 2.8f);
}
bool MapMaker::brickButtonPressed(sf::Vector2f pos) {
	if (isMouseOverBrickButton(pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void MapMaker::Draw(sf::RenderWindow& window) {
	for (int i = 0; i < WIDTH - 1; i++) {
		map[i][33] = SPACE;

		for (int j = 0; j < HEIGHT - 1; j++) {
			map[0][j] = SPACE;
			map[34][j] = SPACE;

			if (map[i][j] == GRASS) {
				grass.setPosition(i * cellSize, j * cellSize);
				grass.setSize(sf::Vector2f(cellSize, cellSize));
				window.draw(grass);
			}

			else if (map[i][j] == GRASS_FOR_TOP) {
				grassForTop.setPosition(i * cellSize, j * cellSize);
				grassForTop.setSize(sf::Vector2f(cellSize, cellSize));
				grassForTop.setTexture(grassTexture.get());
				window.draw(grassForTop);
			}

			else if (map[i][j] == STONE) {
				stone.setPosition(i * cellSize, j * cellSize);
				stone.setSize(sf::Vector2f(cellSize, cellSize));
				stone.setTexture(stoneTexture.get());
				window.draw(stone);
			}

			else if (map[i][j] == SAND) {
				sand.setPosition(i * cellSize, j * cellSize);
				sand.setSize(sf::Vector2f(cellSize, cellSize));
				sand.setFillColor(sf::Color(237, 224, 203));
				sand.setTexture(sandTexture.get());
				window.draw(sand);
			}

			else if (map[i][j] == WOOD_LOG) {
				woodLog.setPosition(i * cellSize, j * cellSize);
				woodLog.setSize(sf::Vector2f(cellSize, cellSize));
				woodLog.setTexture(woodLogTexture.get());
				window.draw(woodLog);
			}

			else if (map[i][j] == BRICK) {
				brick.setPosition(i * cellSize, j * cellSize);
				brick.setSize(sf::Vector2f(cellSize, cellSize));
				brick.setTexture(brickTexture.get());
				window.draw(brick);
			}

			if (map[i][j] == GRASS || map[i][j] == GRASS_FOR_TOP)
				grass.setTexture(dirtTexture.get());

			else if (map[i][j] != GRASS) 
				grass.setTexture(grassTexture.get());

			else if (map[i][0] == GRASS)
				map[i][j] = GRASS_FOR_TOP;

			initialMap[i][j] = map[i][j];
		}
	}

	window.draw(matrixBox);
	
	window.draw(clearButton);
	window.draw(clearButtonTxt);
	window.draw(eraseButton);
	window.draw(eraseButtonTxt);
	window.draw(grassButton);
	window.draw(grassButtonTxt);
	window.draw(stoneButton);
	window.draw(stoneButtonTxt);
	window.draw(sandButton);
	window.draw(sandButtonTxt);
	window.draw(woodLogButton);
	window.draw(woodLogButtonTxt);
	window.draw(brickButton);
	window.draw(brickButtonTxt);
}
