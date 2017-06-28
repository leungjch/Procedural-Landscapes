#include <random>
#include "colorGenerator.hpp"
#include "textureGenerator.hpp"
#include "celestialObject.hpp"
#include "SFML/Graphics.hpp"
#include "constants.h"
#include <vector>
extern int height;
extern int width;
//generate celestial objects (stars, planets (rocky/gas), moon, sun)

CelestialObject::CelestialObject() {}
CelestialObject::CelestialObject(float radius) 
{
	setRadius(radius);
}
std::vector<CelestialObject> generateCelestialObjects(std::vector<sf::Texture>& TextureManager, int maxStars, int maxPlanets, int maxSuns)
{
	// create return object
	std::vector<CelestialObject> ret;

	// set up random
	std::random_device seed;
	std::mt19937 rng(seed());

	// determining probability
	std::uniform_real_distribution<double> zero_to_one(0.0, 1.0);

	// radii ranges
	std::uniform_real_distribution<double> starRadius(0.0, 2.5);
	std::uniform_real_distribution<double> sunRadius(50, 600);
	std::uniform_real_distribution<double> planetRadius(0.0, 200);

	// position ranges
	std::uniform_real_distribution<double> randHeight(0.0, height/2);
	std::uniform_real_distribution<double> randWidth(0.0, width);

	// number of object range
	std::uniform_int_distribution<> numStars(0, maxStars);
	std::uniform_int_distribution<> numSuns(0, maxSuns);
	std::uniform_int_distribution<> numPlanets(0, maxPlanets);

	// rotation of planet range
	std::uniform_int_distribution<> randAngle(0, 360);

	//std::uniform_int_distribution<> numSuns(0, maxSuns);
	// generate stars (33% chance)
	if (zero_to_one(rng) < 0.33)
	{
		int stars = numStars(rng);
		for (int i = 0; i < stars; i++)
		{
			CelestialObject tempStar = CelestialObject(starRadius(rng));
			tempStar.texture;
			tempStar.setPosition(randWidth(rng), randHeight(rng));
			ret.push_back(tempStar);
		}
	}
	// generate sun (50% chance
	if (zero_to_one(rng) > 0.75)
	{
		int suns = numSuns(rng);
		for (int i = 0; i < suns; i++)
		{
			CelestialObject tempSun = CelestialObject(sunRadius(rng));
			tempSun.setPosition(randWidth(rng), randHeight(rng));
			tempSun.setFillColor(colorGenerator(sf::Color::Yellow));
			
			ret.push_back(tempSun);
		}
	}
	// generate planets (33% chance)
	if (zero_to_one(rng) < 0.33)
	{
		int planets = numPlanets(rng);
		for (int i = 0; i < planets; i++)
		{
			// shape
			CelestialObject tempPlanet = CelestialObject(planetRadius(rng));
			tempPlanet.setPosition(randWidth(rng), randHeight(rng));
			tempPlanet.setFillColor(colorGenerator(sf::Color::White));
			tempPlanet.setRotation(randAngle(rng));
			// generate a rocky planet
			if (zero_to_one(rng) < 0.5)
			{
				sf::Texture texture;
				texture = generateGasGiantTexture(7, tempPlanet.getRadius());
				TextureManager.push_back(texture);
				tempPlanet.setTexture(&TextureManager.back());
			}
			// generate a gas giant
			else
			{
				sf::Texture texture;
				texture = generateGasGiantTexture(7, tempPlanet.getRadius());
				TextureManager.push_back(texture);
				tempPlanet.setTexture(&TextureManager.back());
			}
			ret.push_back(tempPlanet);

		}
	}
	return ret;
}