#pragma once

#include <vector>
#include <Windows.h>
//Abstract class for entities
class Entity
{
protected:
	float x;
	float y;
	std::vector<char> infill;
	WORD color;
public:
	float getX() { return x; }
	float getY() { return y; }
	WORD getColor() { return color; }
	std::vector<char>* getFill() { return &infill; }
	virtual void Update(float dt) = 0;
	Entity(float xc, float yc, std::vector<char> inc, WORD col) : x(xc), y(yc), infill(inc), color(col) {}
	virtual ~Entity() = default;
};

