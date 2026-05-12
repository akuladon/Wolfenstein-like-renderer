#include "Enemy.h"

Enemy::Enemy(float xc, float yc, char inc, float dc) : Entity(xc, yc, inc) {
	d = dc;
	xs = xc;
	ys = yc;
}

void Enemy::Update(float dt) {
	t+= dt;
	x = xs + d * std::cos(t);
	y = ys + d * std::sin(t);

}
Enemy::~Enemy() {

}