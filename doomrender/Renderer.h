#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <vector>
#include <utility>
#include <thread>
#include <Windows.h>
#include <algorithm>

#include "CharMap.h"
#include "Entity.h"


class Renderer
{
	//Screen size (symbol count)
	const int screenWidth;
	const int screenHeight;
	CharMap* const map;
	std::vector<Entity*>* entityList;
	float TraceMap(float x, float y, float rot);
	void FillColumns(int start, int end);
	void FillColumn(int x, int ceiling, int floor, char ch, WORD col);
public:
	float xLoc = 0;
	float yLoc = 0;
	float rotation = 0;


	std::vector<char> renderBuffer;
	std::vector<float> zBuffer;
	std::vector<WORD> colorBuffer;
	void Render();
	void Draw();
	void ResizeWindow();
	Renderer(int w, int h, CharMap* mapC, std::vector<Entity*> * enList);
};

