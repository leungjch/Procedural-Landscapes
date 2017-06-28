#include "SFML/Graphics.hpp"
#include "constants.h"
#include "background.h"
#include "terrain.h"
#include "celestialObject.hpp"
#include "midpointDisplacement.h"
#include <random>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include "colorGenerator.hpp"
extern int height;
extern int width;
int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Landscapes");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	std::vector<Terrain> terrain;
	Background background;
	std::vector<CelestialObject> celestialObjects;
	background.init(colorGenerator(sf::Color(rand()%255, rand()%255, rand()%255)), colorGenerator(sf::Color(rand() % 255, rand() % 255, rand() % 255)));


	int numOfScreenshots = 0;

	sf::Clock clock;
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_real_distribution<double> roughness_picker(0.1, 2.3);

	//sf::CircleShape circle(50);
	//sf::Texture texture;
	//texture.loadFromFile("screenshot_0.png");
	//circle.setTexture(&texture);

	// stores textures for terrain and celestial objects.
	// accessible by corresponding index
	std::vector<sf::Texture> TextureManager;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				TextureManager.clear();
				terrain = generateTerrain(10, 1.6, 8, height);
				background.init(colorGenerator(sf::Color(rand() % 255, rand() % 255, rand() % 255)), colorGenerator(sf::Color(rand() % 255, rand() % 255, rand() % 255)));
				celestialObjects = generateCelestialObjects(TextureManager, 500, 25, 25);
			}
			if (clock.getElapsedTime().asSeconds() > 15)
			{
				sf::Vector2u windowSize = window.getSize();
				sf::Texture texture;
				texture.create(windowSize.x, windowSize.y);
				texture.update(window);
				sf::Image screenshot = texture.copyToImage();
				std::string filename = "Screenshots/screenshot_" + std::to_string(numOfScreenshots) + ".png";
				screenshot.saveToFile(filename);
				numOfScreenshots++;
				clock.restart();
				TextureManager.clear();
				terrain = generateTerrain(10, 1.6, 8, height);
				background.init(colorGenerator(sf::Color(rand() % 255, rand() % 255, rand() % 255)), colorGenerator(sf::Color(rand() % 255, rand() % 255, rand() % 255)));
				celestialObjects = generateCelestialObjects(TextureManager, 500, 5, 2);
			}
		}
		
		window.clear();
		window.draw(background);
		// draw celestial objects
		for (int i = 0; i < celestialObjects.size(); i++)
		{
			window.draw(celestialObjects[i]);
		}
		// draw terrain
		for (int i = 0; i < terrain.size(); i++)
		{
			window.draw(terrain[i]);
		}
		//window.draw(circle);
		window.display();
	}
	return 0;
}