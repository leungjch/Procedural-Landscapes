#include "SFML/Graphics.hpp"
#include "midpointDisplacement.h"
#include <vector>
class Terrain : public sf::ConvexShape
{
public:
	Terrain();
	Terrain(sf::Color colorTop, sf::Color colorBot, double roughness, int n, double range);
	void init(sf::Color colorTop, sf::Color colorBot, double roughness, int n, double range);
};
std::vector<Terrain> generateTerrain(int numOfTerrain, double roughness, int n, double range);