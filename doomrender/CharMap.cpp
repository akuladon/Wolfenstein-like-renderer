#include "CharMap.h"

CharMap::CharMap(int mw, int mh) : mapWidth(mw < 1 ? 1 : mw), mapHeight(mh < 1 ? 1 : mh) {
	Map.resize(mapWidth*mapHeight);
	Map.assign(mapWidth * mapHeight, ' ');
}

char CharMap::getPoint(int x, int y) {
	if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
		return ' ';
	}
	return Map.at(y * mapWidth + x);
}

void CharMap::setPoint(int x, int y, char c) {
	if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
		return;
	}
	Map.at(y * mapWidth + x) = c;
}

void CharMap::draw() {
	for (int i = mapHeight - 1; i >= 0; i--) {
		for (int j = 0; j < mapWidth; j++) {
			std::cout << ' ' << Map.at(i * mapWidth + j);
		}
		std::cout << std::endl;
	}
}