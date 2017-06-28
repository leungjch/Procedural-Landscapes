#include "SFML/Graphics.hpp"
#include "constants.h"
class Background : public sf::VertexArray
{
public:
	Background();
	void init(sf::Color colorTop, sf::Color colorBot);

};