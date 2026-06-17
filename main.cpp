#include "raylib.h"


typedef struct Player{
	Vector2 pos = { .x = 0.0f, .y = 490.0f };
	Vector2 direction = { .x = 0.0f, .y = 0.0f };
	float speed = 600.0f;
	Rectangle PlayerRec = { .x = pos.x, .y = pos.y, .width = 10.0f, .height = 100.0f };
}Player;

typedef struct CPU {
	Vector2 pos = {.x = 1920.0f - 11.0f, .y = 540.0f - 50.0f};
	Vector2 direction = { .x = 0.0f, .y = 0.0f };
	float speed = 600.0f;
	Rectangle cpuRec = { .x = pos.x , .y = pos.y , .width = 10.0f , .height = 100.0f };
}CPU;

typedef struct Ball {
	Vector2 center;
	Vector2 direction;
	float speed = 500.0f;
	float radius;

	void invertDirection() {
		direction.x *= -1;
		direction.y *= -1;
	}
	void inCenter() {
		center.x = 1920 / 2;
		center.y = 1080 / 2;
	}
	void WallCollide(int height)
	{
		if (center.y >= height) {
			direction.y = -1;
		}
		if (center.y <= 0) {
			direction.y = 1;
		}
	}

}Ball;

typedef struct Colliders {
	Rectangle left;
	Rectangle right;
}Colliders;

typedef struct GameState {
	bool win = false;
	bool gameOver = false;
	bool reset = false;
	bool pause = false;
}GameState;

typedef struct Score {
	int playerScore;
	int cpuScore;
}Score;





/*
* TODO later:
* implement-> game over screen, bot behaviur in "cpu player",
*	organize code in other files 
* drawing -> make textures for game objects in aseprite
* final state implement -> textures and audio system
* final final implement -> make something funny in the end
*/
int main() 
{
	int widthWindow = 1920;
	int heightWindow = 1080;
	int meiodatela = 1920 / 2;
	int meiodomeio = (1920 / 2) / 2;
	InitWindow(widthWindow,heightWindow, "Pong");
	SetTargetFPS(60);


	Player p1;
	CPU cpu;
	GameState gameState;
	Ball ball{
		.center = {.x = (float)widthWindow / 2, .y = (float)heightWindow / 2},
		.direction = {.x = 1, .y = 1},
		.radius = 10.0f
	};
	
	Colliders colliders{
		.left{.x = 0.0, .y = 0.0,.width = 1, .height = 1080 },
		.right{.x = 1920, .y = 0.0,.width = 1, .height = 1080}
	};
	Score points{
		.playerScore = 0,
		.cpuScore = 0
	};
	
	while (!WindowShouldClose())
	{	
		//input
		if (p1.pos.y <= 0) {
			p1.direction.y = IsKeyDown(KEY_DOWN);
		}
		else if (p1.pos.y >= 1000) {
			p1.direction.y = IsKeyDown(KEY_UP) * -1;
		}
		else {
			p1.direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
		}

		cpu.direction.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

		// moviment
		float deltaTime = GetFrameTime();
		p1.pos.y += p1.direction.y * p1.speed * deltaTime;
		p1.PlayerRec.y = p1.pos.y;

		cpu.pos.y += cpu.direction.y * p1.speed * deltaTime;
		cpu.cpuRec.y = cpu.pos.y;

		//ball moviment
		ball.WallCollide(heightWindow);
		ball.center.x += ball.direction.x * ball.speed * deltaTime;
		ball.center.y += ball.direction.y * ball.speed * deltaTime;

		//collision 
		bool collisionBallPlayer = CheckCollisionCircleRec(ball.center, ball.radius, p1.PlayerRec);
		bool collisionBallCpu = CheckCollisionCircleRec(ball.center, ball.radius, cpu.cpuRec);
		bool collisionBallLeft = CheckCollisionCircleRec(ball.center, ball.radius, colliders.left);
		bool collisionBallRight = CheckCollisionCircleRec(ball.center, ball.radius, colliders.right);

		if (collisionBallPlayer) {	
			ball.invertDirection();
		}
		if (collisionBallCpu) {
			ball.invertDirection();
		}

		if (collisionBallLeft) {
			gameState.reset = true;
			points.cpuScore++;
			ball.invertDirection();
		}
		else if (collisionBallRight) {
			gameState.reset = true;
			points.playerScore++;
			ball.invertDirection();
		}
		else {
			gameState.reset = false;
		}

		//Conditions Game
		if (gameState.reset) {
			ball.inCenter();
		}
		if (points.playerScore == 10) {
			gameState.win == true;
		}
		if (points.cpuScore == 10) {
			gameState.gameOver == true;
		}
		if (gameState.gameOver) {
			//draw game over screen
			break;
		}

		//draw
		BeginDrawing();
		ClearBackground(BLACK);

		//colliders for debug
		//DrawRectangleRec(colliders.left, RED);
		//DrawRectangleRec(colliders.right, RED); 
		
		//points
		DrawText(TextFormat("%i", points.playerScore),(1920/2)/2 ,0, 100, WHITE);
		DrawText(TextFormat("%i", points.cpuScore), (1920+920)/2, 0, 100, WHITE);
		//middle line
		DrawLine(1920/2, 0, 1920/2, 1080, WHITE);
		//objects in game
		DrawCircleV(ball.center, ball.radius, WHITE);
		DrawRectangleRec(p1.PlayerRec, WHITE);
		DrawRectangleRec(cpu.cpuRec, WHITE);

		EndDrawing();
	}

	CloseWindow();
}