#pragma once
#include"raylib.h"
typedef struct Player {
	Vector2 pos;
	Vector2 direction;
	float speed;
	Rectangle PlayerRec;
}Player;

typedef struct CPU {
	Vector2 pos;
	Vector2 direction;
	float speed;
	Rectangle cpuRec;
}CPU;

typedef struct Ball {
	Vector2 center;
	Vector2 direction;
	float speed;
	float radius;
}Ball;

typedef struct Colliders {
	Rectangle left;
	Rectangle right;
}Colliders;

typedef struct GameState {
	bool win;
	bool gameOver;
	bool reset;
	bool pause;
}GameState;

typedef struct Score {
	int playerScore;
	int cpuScore;
}Score;