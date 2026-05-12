#include "Follower.h"

Follower::Follower(float xc, float yc, Renderer* player) : Entity(xc, yc, 'j') {
	_player = player;
}

void Follower::Update(float dt) {

	if (_player != nullptr) {
		px = _player->xLoc;
		py = _player->yLoc;
	}

	float dx = px - x;
	float dy = py - y;

	float d = std::sqrt(dx * dx + dy * dy);

	float ndx = 0;
	float ndy = 0;

	if (d != 0) {
		ndx = dx / d;
		ndy = dy / d;
	}

	Vx -= Vx * drag * dt / mass;
	Vy -= Vy * drag * dt / mass;

	Vx += ndx * forceMagnitude * dt / mass;
	Vy += ndy * forceMagnitude * dt / mass;

	

	x += Vx * dt;
	y += Vy * dt;
}