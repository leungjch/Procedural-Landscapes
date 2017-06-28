#include "SFML/Graphics.hpp"
#include "terrain.h"
#include <iostream>
#include <math.h>
#include "colorGenerator.hpp"
extern int width;
extern int height;
Terrain::Terrain() {}
Terrain::Terrain(sf::Color colorTop, sf::Color colorBot, double roughness, int n, double range)
{
	std::vector<std::pair<double, double>> map = midpointDisplacement(width, height, roughness, n, range);
	setPointCount(pow(2, n) + 3);
	// set the bottom points which are needed to complete the shape (bottom right/left)
	setPoint(0, sf::Vector2f(width, height*2));
	setPoint(1, sf::Vector2f(0, height*2));
	int counter = 2;
	// set the main terrain points
	for (double i = 0; i < map.size(); i++, counter++)
	{
		setPoint(counter, sf::Vector2f(map[i].first, map[i].second));
	}
	setFillColor(colorTop);
}
/*void Terrain::init(sf::Color colorTop, sf::Color colorBot, double roughness, int n, double range)
{
	std::vector<std::pair<double, double>> map = midpointDisplacement(width, height, roughness, n, range);
	setPointCount(pow(2, n)+3);
	setPoint(0, sf::Vector2f(width, height*2));
	setPoint(1, sf::Vector2f(0, height*2));
	int counter = 2;
	for (double i = 0; i < map.size(); i++, counter++)
	{
		std::cout << i << std::endl;
		std::cout << "Inserting " << map[i].first << ", " << map[i].second;
		setPoint(counter, sf::Vector2f(map[i].first, map[i].second));
	}
	setFillColor(sf::Color::Blue);
}*/
std::vector<Terrain> generateTerrain(int numOfTerrain, double roughness, int n, double range)
{
	std::vector<Terrain> ret;
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_real_distribution<double> roughness_picker(0.6, roughness);
	for (int i = 0; i < numOfTerrain; i++)
	{
		ret.push_back(Terrain(colorGenerator(sf::Color::White), colorGenerator(sf::Color::White), roughness_picker(rng), 8, double(range / (2 + i))));
	}
	return ret;
}