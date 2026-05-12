#pragma once

#include <iostream>
#include <vector>

//An array with some functions to work with it. It represents the game map
class CharMap
{
	const int mapWidth;
	const int mapHeight;
	std::vector<char> Map;
public:
	void setPoint(int x, int y, char c);
	char getPoint(int x, int y);
	void draw();
	CharMap(int mw, int mh);
};

