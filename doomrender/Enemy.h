#pragma once
#include "Entity.h"
#include <cmath>

//I called it an enemy just because this was the first implemented entity. The only thing it can do is run in circles
class Enemy :
    public Entity
{
    float t = 0;
    float d;
    float xs;
    float ys;
public:
    Enemy(float xc, float yc, char inc, float dc);
    void Update(float dt) override;
    ~Enemy();
};

