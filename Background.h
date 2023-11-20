#include <SFML/Graphics.hpp>
#include "iostream"

class Background
{
private:

	std::string location;
	sf::Vector2f scale;
	sf::Texture BackgroundTexture;

public:
	
	float position_x;
	float position_y;

	Background(float Position_x, float Position_y, sf::Vector2f Scale,std::string Location);
	sf::Sprite BackgroundSprite;
	
};

