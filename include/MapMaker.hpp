#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <memory>

#include "Assets.hpp"

#define HEIGHT 35
#define WIDTH 36

enum ID {
	EMPTY = 0,
	GRASS = 1,
	GRASS_FOR_TOP = 2,
	STONE = 3,
	SAND = 4,
	WOOD_LOG = 5,
	BRICK = 6,
	SPACE = 7
};

class MapMaker {
public:
	MapMaker();

	void Update();

	void placeGrass(int posX, int posY);
	void placeStone(int posX, int posY);
	void placeSand(int posX, int posY);
	void placeWoodLog(int posX, int posY);
	void placeBrick(int posX, int posY);
	void erase(int posX, int posY);

	// MAP MAKER UI
	void setClearUIPosition();
	void changeClearButtonColor(sf::Color color) { clearButton.setFillColor(color); }
	bool isMouseOverClearButton(sf::Vector2f pos) { return clearButton.getGlobalBounds().contains(sf::Vector2f(pos)); }
	bool clearButtonPressed(sf::Vector2f pos);

	void setEraseUIPosition();
	void changeEraseButtonColor(sf::Color color) { eraseButton.setFillColor(color); }
	bool isMouseOverEraseButton(sf::Vector2f pos) { return eraseButton.getGlobalBounds().contains(sf::Vector2f(pos)); }
	bool eraseButtonPressed(sf::Vector2f pos);

	void setGrassUIPosition();
	void changeGrassButtonColor(sf::Color color) { grassButton.setFillColor(color); }
	bool isMouseOverGrassButton(sf::Vector2f pos) { return grassButton.getGlobalBounds().contains(sf::Vector2f(pos)); }
	bool grassButtonPressed(sf::Vector2f pos);

	void setStoneUIPosition();
	void changeStoneButtonColor(sf::Color color) { stoneButton.setFillColor(color); }
	bool isMouseOverStoneButton(sf::Vector2f pos) { return stoneButton.getGlobalBounds().contains(sf::Vector2f(pos)); }
	bool stoneButtonPressed(sf::Vector2f pos);

	void setSandUIPosition();
	void changeSandButtonColor(sf::Color color) { sandButton.setFillColor(color); }
	bool isMouseOverSandButton(sf::Vector2f pos) { return sandButton.getGlobalBounds().contains(sf::Vector2f(pos)); }
	bool sandButtonPressed(sf::Vector2f pos);

	void setWoodLogUIPosition();
	void changeWoodLogButtonColor(sf::Color color) { woodLogButton.setFillColor(color); }
	bool isMouseOverWoodLogButton(sf::Vector2f pos) { return woodLogButton.getGlobalBounds().contains(sf::Vector2f(pos)); }
	bool woodLogButtonPressed(sf::Vector2f pos);

	void setBrickUIPosition();
	void changeBrickButtonColor(sf::Color color) { brickButton.setFillColor(color); }
	bool isMouseOverBrickButton(sf::Vector2f pos) { return brickButton.getGlobalBounds().contains(sf::Vector2f(pos)); }
	bool brickButtonPressed(sf::Vector2f pos);

	/**************************************************/

	void clear();
	void Draw(sf::RenderWindow& window);
public:
	float cellSize = 20.f;
private:
	int map[WIDTH][HEIGHT];
	int initialMap[WIDTH][HEIGHT];

	sf::RectangleShape grass;
	sf::RectangleShape grassForTop;
	sf::RectangleShape stone;
	sf::RectangleShape sand;
	sf::RectangleShape woodLog;
	sf::RectangleShape brick;

	sf::RectangleShape matrixBox;

	sf::RectangleShape clearButton;
	sf::Text clearButtonTxt;

	sf::RectangleShape eraseButton;
	sf::Text eraseButtonTxt;

	sf::RectangleShape grassButton;
	sf::Text grassButtonTxt;

	sf::RectangleShape stoneButton;
	sf::Text stoneButtonTxt;

	sf::RectangleShape sandButton;
	sf::Text sandButtonTxt;

	sf::RectangleShape woodLogButton;
	sf::Text woodLogButtonTxt;

	sf::RectangleShape brickButton;
	sf::Text brickButtonTxt;

	sf::Font font;

	std::unique_ptr<sf::Texture> grassTexture;
	std::unique_ptr<sf::Texture> dirtTexture;
	std::unique_ptr<sf::Texture> stoneTexture;
	std::unique_ptr<sf::Texture> sandTexture;
	std::unique_ptr<sf::Texture> woodLogTexture;
	std::unique_ptr<sf::Texture> brickTexture;

	Assets assets;

	bool occupied;
};