#pragma once
#include "SFML/Graphics.hpp"
#include "key.h"
#include "iostream"
#include <future>
#include <chrono>

static int i = 0;

class input
{
	
public:
	sf::Clock inputTime;
	enum state
	{
		PRESSED,
		RELEASED,
		HOLD,

	};
	static bool isPressed(Key key, sf::Clock& clock);
	static bool isReleased(Key key);
	

};

