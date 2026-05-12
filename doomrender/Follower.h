#pragma once

#include <cmath>

#include "Entity.h"
#include "Renderer.h"

//Now this guy is a real enemy who follows you

class Follower :
    public Entity
{
    float Vx = 0;
    float Vy = 0;
    float mass = 10;
    float forceMagnitude = 10;
    float drag = 5;
    float px = 0;
    float py = 0;
    Renderer* _player;

public:
    Follower(float xc, float yc, Renderer* player);
    void Update(float deltaT) override;
};

