#pragma once

//Abstract class for entities
class Entity
{
protected:
	float x;
	float y;
	char infill;
public:
	float getX() { return x; }
	float getY() { return y; }
	char getFill() { return infill; }
	virtual void Update(float dt) = 0;
	Entity(float xc, float yc, char inc) : x(xc), y(yc), infill(inc) {}
	virtual ~Entity() = default;
};

