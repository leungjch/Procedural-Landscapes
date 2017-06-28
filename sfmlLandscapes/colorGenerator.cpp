#include "SFML/Graphics.hpp"
#include <random>
sf::Color colorGenerator(sf::Color mixInput)
{
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_int_distribution<> random_color(0,255);
	sf::Color color = sf::Color((random_color(rng)+mixInput.r)/2, (random_color(rng)+mixInput.g)/2, (random_color(rng)+mixInput.b)/2);
	return color;
}