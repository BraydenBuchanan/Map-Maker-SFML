#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

#include "MapMaker.hpp"
#include "Assets.hpp"

using namespace std::chrono_literals;

static float VIEW_HEIGHT = 1512.f;

static void resizedView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(660, 660), "Map Maker");
	sf::Event event;

	window.setFramerateLimit(60.f);

	Assets assets;

	MapMaker mapMaker;
	mapMaker.clear();

	mapMaker.setClearUIPosition();
	mapMaker.setEraseUIPosition();
	mapMaker.setGrassUIPosition();
	mapMaker.setStoneUIPosition();
	mapMaker.setSandUIPosition();
	mapMaker.setWoodLogUIPosition();
	mapMaker.setBrickUIPosition();

	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	sf::RectangleShape dragView(sf::Vector2f(50.f, 50.f));
	dragView.setPosition(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f);
	dragView.setFillColor(sf::Color::Transparent);

	bool isDragging = false;

	bool emptyToggle = false;
	bool grassToggle = false;
	bool stoneToggle = false;
	bool sandToggle = false;
	bool woodLogToggle = false;
	bool brickToggle = false;

	sf::Font font;
	font.loadFromFile(assets.fontAsset);

	sf::Text instructions;
	instructions.setFont(font);
	instructions.setCharacterSize(30.f);
	instructions.setFillColor(sf::Color::White);
	instructions.setString("Press I/O to zoom in and out, drag using right click");
	instructions.setPosition(12.f, -42.f);

	while (window.isOpen()) {
		window.clear(sf::Color::Black);

		sf::Vector2i pos = sf::Mouse::getPosition(window);
		sf::Vector2f posView = window.mapPixelToCoords(pos);

		while (window.pollEvent(event)) {
			int posX = floor(posView.x / mapMaker.cellSize);
			int posY = floor(posView.y / mapMaker.cellSize);

			if (mapMaker.eraseButtonPressed(posView)) {
				std::this_thread::sleep_for(.2s);
				emptyToggle = !emptyToggle;

				grassToggle = false;
				stoneToggle = false;
				sandToggle = false;
				woodLogToggle = false;
				brickToggle = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && emptyToggle)
				mapMaker.erase(posX, posY);

			if (mapMaker.grassButtonPressed(posView)) {
				std::this_thread::sleep_for(.2s);
				grassToggle = !grassToggle;

				stoneToggle = false;
				sandToggle = false;
				woodLogToggle = false;
				brickToggle = false;
				emptyToggle = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && grassToggle)
				mapMaker.placeGrass(posX, posY);

			if (mapMaker.stoneButtonPressed(posView)) {
				std::this_thread::sleep_for(.2s);
				stoneToggle = !stoneToggle;

				grassToggle = false;
				sandToggle = false;
				woodLogToggle = false;
				brickToggle = false;
				emptyToggle = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stoneToggle)
				mapMaker.placeStone(posX, posY);

			if (mapMaker.sandButtonPressed(posView)) {
				std::this_thread::sleep_for(.2s);
				sandToggle = !sandToggle;

				grassToggle = false;
				stoneToggle = false;
				woodLogToggle = false;
				brickToggle = false;
				emptyToggle = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sandToggle)
				mapMaker.placeSand(posX, posY);

			if (mapMaker.woodLogButtonPressed(posView)) {
				std::this_thread::sleep_for(.2s);
				woodLogToggle = !woodLogToggle;

				grassToggle = false;
				stoneToggle = false;
				sandToggle = false;
				brickToggle = false;
				emptyToggle = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && woodLogToggle)
				mapMaker.placeWoodLog(posX, posY);

			if (mapMaker.brickButtonPressed(posView)) {
				std::this_thread::sleep_for(.2s);
				brickToggle = !brickToggle;

				grassToggle = false;
				stoneToggle = false;
				sandToggle = false;
				woodLogToggle = false;
				emptyToggle = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && brickToggle)
				mapMaker.placeBrick(posX, posY);

			sf::Vector2i lastMousePos;

			int objectOffsetX = 0;
			int objectOffsetY = 0;

			if (event.type == event.Closed)
				window.close();

			else if (event.type == event.Resized)
				resizedView(window, view);

			else if (event.type == event.MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					isDragging = true;
					lastMousePos = sf::Mouse::getPosition(window);

					objectOffsetX = lastMousePos.x - dragView.getPosition().x;
					objectOffsetY = lastMousePos.y - dragView.getPosition().y;
				}
			}

			else if (event.type == event.MouseMoved && isDragging) {
				sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
				dragView.setPosition((currentMousePos.x - objectOffsetX), (currentMousePos.y - objectOffsetY));
			}

			else if (event.type == event.MouseButtonReleased)
				isDragging = false;
		}

		float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			VIEW_HEIGHT -= 5.f;
			view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
		}
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
			VIEW_HEIGHT += 5.f;
			view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
		}

		if (mapMaker.isMouseOverClearButton(posView))
			mapMaker.changeClearButtonColor(sf::Color(180, 180, 180));
		else
			mapMaker.changeClearButtonColor(sf::Color::White);

		if (mapMaker.isMouseOverEraseButton(posView))
			mapMaker.changeEraseButtonColor(sf::Color(180, 180, 180));
		else
			mapMaker.changeEraseButtonColor(sf::Color::White);

		if (mapMaker.isMouseOverGrassButton(posView))
			mapMaker.changeGrassButtonColor(sf::Color(180, 180, 180));
		else
			mapMaker.changeGrassButtonColor(sf::Color::White);

		if (mapMaker.isMouseOverStoneButton(posView))
			mapMaker.changeStoneButtonColor(sf::Color(180, 180, 180));
		else
			mapMaker.changeStoneButtonColor(sf::Color::White);

		if (mapMaker.isMouseOverSandButton(posView))
			mapMaker.changeSandButtonColor(sf::Color(180, 180, 180));
		else
			mapMaker.changeSandButtonColor(sf::Color::White);

		if (mapMaker.isMouseOverWoodLogButton(posView))
			mapMaker.changeWoodLogButtonColor(sf::Color(180, 180, 180));
		else
			mapMaker.changeWoodLogButtonColor(sf::Color::White);

		if (mapMaker.isMouseOverBrickButton(posView))
			mapMaker.changeBrickButtonColor(sf::Color(180, 180, 180));
		else
			mapMaker.changeBrickButtonColor(sf::Color::White);

		if (mapMaker.clearButtonPressed(posView))
			mapMaker.clear();

		mapMaker.Update();
		view.setCenter(dragView.getPosition());

		window.clear(sf::Color::Black);
		
		window.setView(view);
		mapMaker.Draw(window);
		window.draw(dragView);
		window.draw(instructions);

		window.display();
	}
}