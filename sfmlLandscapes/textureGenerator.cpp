#include "SFML/Graphics.hpp"
#include "textureGenerator.hpp"
#include "colorGenerator.hpp"
#include "midpointDisplacement.h"
#include "terrain.h"
#include <random>
/*void generateTerrainGradient()
{

}*/
/*void generatePlanetTexture()
{

}*/
sf::Texture generateGasGiantTexture(int maxBands, float radius)
{
	// return object
	sf::Texture ret;
	sf::RenderTexture tex;
	ret.create(radius * 2, radius * 2);
	tex.create(radius * 2, radius * 2);
	tex.clear(colorGenerator(sf::Color::White));
	// setting up random
	std::random_device seed;
	std::mt19937 rng(seed());

	// temp vector which will be placed onto texture
	std::vector<sf::ConvexShape> temp;

	// number of bands
	std::uniform_int_distribution<> randBands(1, maxBands);
	// for generating roughness (the bands should look fairly smooth)
	std::uniform_int_distribution<> roughness(2, 2.5);
	int numBands = randBands(rng);

	for (int i = 0; i < numBands; i++)
	{
		sf::ConvexShape band;
		band.setPointCount(pow(2, 6) + 3);
		std::vector<std::pair<double, double>> points = midpointDisplacement(radius * 2, 0 + (radius * 2 / numBands*(i + 1)), roughness(rng), 6, radius / (i + 1));
		band.setPoint(0, sf::Vector2f(radius * 2, radius * 2));
		band.setPoint(1, sf::Vector2f(0, radius * 2));
		int counter = 2;
		// set the main terrain points
		for (double i = 0; i < points.size(); i++, counter++)
		{
			band.setPoint(counter, sf::Vector2f(points[i].first, points[i].second));
		}
		band.setFillColor(colorGenerator(sf::Color::White));
		tex.draw(band);
	}
	ret = tex.getTexture();
	return ret;
}
