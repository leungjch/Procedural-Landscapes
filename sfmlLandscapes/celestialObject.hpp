#include "SFML/Graphics.hpp"
class CelestialObject : public sf::CircleShape
{
public:
	CelestialObject();
	CelestialObject(float radius);
	sf::Texture texture;
};
std::vector<CelestialObject> generateCelestialObjects(std::vector<sf::Texture>& TextureManager, int maxStars, int maxPlanets, int maxSuns);