#include "../header/gameObjects.h"

Player::Player() {
	pos = { .x = 0.0f, .y = 490.0f };
	direction = { .x = 0.0f, .y = 0.0f };
	speed = 600.0f;
	PlayerRec = { .x = pos.x, .y = pos.y, .width = 10.0f, .height = 100.0f };
};

CPU::CPU() {
	pos = { .x = 1920.0f - 11.0f, .y = 540.0f - 50.0f };
	direction = { .x = 0.0f, .y = 0.0f };
	speed = 600.0f;
	cpuRec = { .x = pos.x , .y = pos.y , .width = 10.0f , .height = 100.0f };
};

Ball::Ball(int widthWindow, int heightWindow) {
	center = {.x = (float)widthWindow / 2, .y = (float)heightWindow / 2};
	direction = {.x = 1.0f,.y = 1.0f};
	speed = 500.0f;
	radius = 15.0f;
}
void Ball::invertDirection() {
	direction.x *= -1;
	direction.y *= -1;
}
void Ball::inCenter() {
	center.x = 1920 / 2;
	center.y = 1080 / 2;
}
void Ball::WallCollide(int height)
{	
	if (center.y >= height) {
		direction.y = -1;
	}
	if (center.y <= 0) {
		direction.y = 1;
	}
}

Colliders::Colliders() {
	left = {.x = 0.0, .y = 0.0,.width = 1, .height = 1080 };
	right = { .x = 1920, .y = 0.0,.width = 1, .height = 1080 };
};

GameState::GameState() {
	win = false;
	gameOver = false;
	reset = false;
	pause = false;
};
Score::Score() {
	playerScore = 0;
	cpuScore = 0;
};