#include "SFML/Graphics.hpp"
#include "background.h"
#include "constants.h"
#include <random>
extern int height;
extern int width;
Background::Background() {}

void Background::init(sf::Color colorTop, sf::Color colorBot)
{
	// generate random sky color
	setPrimitiveType(sf::Quads);
	append(sf::Vertex(sf::Vector2f(0, 0), colorTop));
	append(sf::Vertex(sf::Vector2f(width, 0), colorTop));
	append(sf::Vertex(sf::Vector2f(width, height), colorBot));
	append(sf::Vertex(sf::Vector2f(0, height), colorBot));
}
void generateStars()
{
	// generate stars, if randomly chosen
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_real_distribution<double> zero_to_one(0.0, 1.0);
	// 50% chance of stars
	if (zero_to_one(rng) > 0.50)
	{

	}
}