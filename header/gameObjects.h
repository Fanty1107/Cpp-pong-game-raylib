#pragma once
#include"raylib.h"

struct Player {
	Vector2 pos;
	Vector2 direction;
	float speed;
	Rectangle PlayerRec;
	Player();
};

struct CPU {
	Vector2 pos;
	Vector2 direction;
	float speed;
	Rectangle cpuRec;
	CPU();
};

struct Ball {
	Vector2 center;
	Vector2 direction;
	float speed;
	float radius;
	void invertDirection();
	void inCenter();
	void WallCollide(int height);
	Ball(int widthWindow, int heightWindow);
};

struct Colliders {
	Rectangle left;
	Rectangle right;
	Colliders();
};

struct GameState {
	bool win;
	bool gameOver;
	bool reset;
	bool pause;
	GameState();
};

struct Score {
	int playerScore;
	int cpuScore;
	Score();
};