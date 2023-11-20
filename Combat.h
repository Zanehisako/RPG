#pragma once
#include "Monster.h"
#include "Player.h"

class Combat
{

	Combat();

	bool inRange(Player* player,Monster* monster);
	
};

