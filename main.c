#include "raylib.h"
#include <stdbool.h>

int main() {
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
	const int RECT_WIDTH = 30;
	const int RECT_HEIGHT = 200;
	const int PONG_DIMENSION = 30;
	const int MOVE_AMOUNT_PONG = 5;
	const int MOVE_AMOUNT_PLAYER = 8;
	bool pongMovingDown, pongMovingUp;
	pongMovingDown = true; pongMovingUp = false;

	Vector2 Player1 = { (int)(SCREEN_WIDTH/2 - 900             ), (int)(SCREEN_HEIGHT/2 - RECT_HEIGHT/2) };
	Vector2 Player2 = { (int)(SCREEN_WIDTH/2 + 900 - RECT_WIDTH), (int)(SCREEN_HEIGHT/2 - RECT_HEIGHT/2) };
	Vector2 Pong    = { (int)(SCREEN_WIDTH/2 - PONG_DIMENSION/2), (int)(SCREEN_HEIGHT/2 - PONG_DIMENSION/2)};

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// DrawRectangle(-10, -10, 1940, 10, WHITE);
		// DrawRectangle(-10, 1080, 1940, 10, WHITE);

		if (IsKeyDown(KEY_W))    Player1.y -= MOVE_AMOUNT_PLAYER;
		if (IsKeyDown(KEY_S))    Player1.y += MOVE_AMOUNT_PLAYER;
		if (IsKeyDown(KEY_UP))   Player2.y -= MOVE_AMOUNT_PLAYER;
		if (IsKeyDown(KEY_DOWN)) Player2.y += MOVE_AMOUNT_PLAYER;

		Rectangle Player1Rect = { Player1.x, Player1.y, RECT_WIDTH, RECT_HEIGHT};
		Rectangle Player2Rect = { Player2.x, Player2.y, RECT_WIDTH, RECT_HEIGHT};

		if (pongMovingDown && !pongMovingUp) {
			if (Pong.y + PONG_DIMENSION < SCREEN_HEIGHT) {
				Pong.y += MOVE_AMOUNT_PONG;
			} else if (Pong.y + PONG_DIMENSION == SCREEN_HEIGHT) {
				pongMovingDown = false;
				pongMovingUp = true;
			}
		} else if (pongMovingUp && !pongMovingDown) {
			if (Pong.y > 0) {
				Pong.y -= MOVE_AMOUNT_PONG;
			} else if (Pong.y == 0) {
				pongMovingUp = false;
				pongMovingDown = true;
			}
		}

		BeginDrawing();
			ClearBackground(BLACK);

			DrawRectangle(Player1.x, Player1.y, RECT_WIDTH, RECT_HEIGHT, GRAY);
			DrawRectangle(Player2.x, Player2.y, RECT_WIDTH, RECT_HEIGHT, GRAY);
			DrawRectangle(Pong.x, Pong.y, PONG_DIMENSION, PONG_DIMENSION, RAYWHITE);

		EndDrawing();

	}

	CloseWindow();
	return 0;
}