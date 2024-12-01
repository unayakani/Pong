#include "raylib.h"
#include <stdbool.h>
#include <time.h>

int main() {
	const int SCREEN_WIDTH       = 1920;
	const int SCREEN_HEIGHT      = 1080;
	const int RECT_WIDTH		 = 30;
	const int RECT_HEIGHT		 = 200;
	const int PONG_DIMENSION	 = 30;
	const int MOVE_AMOUNT_PONG	 = 1;
	const int MOVE_AMOUNT_PLAYER = 2;
	bool pongMovingDown, pongMovingUp, pongMovingLeft, pongMovingRight;
	pongMovingDown  = true;
	pongMovingUp    = false;
	pongMovingLeft  = true;
	pongMovingRight = false;
	struct timespec ts = {0, 2500000L};

	Vector2 Player1 = { (int)(SCREEN_WIDTH/2 - 900)             , (int)(SCREEN_HEIGHT/2 - RECT_HEIGHT/2)    };
	Vector2 Player2 = { (int)(SCREEN_WIDTH/2 + 900 - RECT_WIDTH), (int)(SCREEN_HEIGHT/2 - RECT_HEIGHT/2)    };
	Vector2 Pong    = { (int)(SCREEN_WIDTH/2 - PONG_DIMENSION/2), (int)(SCREEN_HEIGHT/2 - PONG_DIMENSION/2) };

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	InitAudioDevice();

	Music music = LoadMusicStream("cool-powerful-hard-rock-243776.mp3");
	PlayMusicStream(music);

	SetTargetFPS(0);

	while (!WindowShouldClose()) {
		nanosleep(&ts, NULL);

		UpdateMusicStream(music);
		DrawText("Player 1 - W , S", 12, 10, 30, GRAY);
		DrawText("Player 2 - UP, DOWN", 1588, 10, 30, GRAY);

		Rectangle Player1RectBefore = { Player1.x, Player1.y, RECT_WIDTH    , RECT_HEIGHT };
		Rectangle Player2RectBefore = { Player2.x, Player2.y, RECT_WIDTH    , RECT_HEIGHT };
		Rectangle TopBar			= { -10, -10, 1940, 10 };
		Rectangle BottomBar			= { -10, 1080, 1940, 10 };

		if (IsKeyDown(KEY_W)	&& !CheckCollisionRecs(Player1RectBefore, TopBar	)) Player1.y -= MOVE_AMOUNT_PLAYER;
		if (IsKeyDown(KEY_S)	&& !CheckCollisionRecs(Player1RectBefore, BottomBar	)) Player1.y += MOVE_AMOUNT_PLAYER;
		if (IsKeyDown(KEY_UP)	&& !CheckCollisionRecs(Player2RectBefore, TopBar	)) Player2.y -= MOVE_AMOUNT_PLAYER;
		if (IsKeyDown(KEY_DOWN) && !CheckCollisionRecs(Player2RectBefore, BottomBar )) Player2.y += MOVE_AMOUNT_PLAYER;

		Rectangle Player1Rect = { Player1.x, Player1.y, RECT_WIDTH    , RECT_HEIGHT   };
		Rectangle Player2Rect = { Player2.x, Player2.y, RECT_WIDTH    , RECT_HEIGHT   };
		Rectangle PongRect    = { Pong.x   , Pong.y   , PONG_DIMENSION, PONG_DIMENSION};

		if (pongMovingDown && !pongMovingUp) {
			if (Pong.y + PONG_DIMENSION < SCREEN_HEIGHT) {
				Pong.y += MOVE_AMOUNT_PONG;
			} else if (Pong.y + PONG_DIMENSION == SCREEN_HEIGHT) {
				pongMovingDown = false;
				pongMovingUp   = true;
			}
		} else if (pongMovingUp && !pongMovingDown) {
			if (Pong.y > 0) {
				Pong.y -= MOVE_AMOUNT_PONG;
			} else if (Pong.y == 0) {
				pongMovingUp   = false;
				pongMovingDown = true;
			}
		}

		if (!CheckCollisionRecs(PongRect, Player1Rect) && pongMovingLeft) {
			Pong.x -= MOVE_AMOUNT_PONG;
		} else if (!CheckCollisionRecs(PongRect, Player1Rect) && pongMovingRight) {
			Pong.x += MOVE_AMOUNT_PONG;
		} else if (CheckCollisionRecs(PongRect, Player1Rect) && pongMovingLeft) {
			pongMovingLeft  = false;
			pongMovingRight = true;
			Pong.x += MOVE_AMOUNT_PONG;
		} else if (!CheckCollisionRecs(PongRect, Player1Rect) && pongMovingRight) {
			Pong.x += MOVE_AMOUNT_PONG;
		}

		if (!CheckCollisionRecs(PongRect, Player2Rect) && pongMovingRight) {
			Pong.x += MOVE_AMOUNT_PONG;
		} else if (!CheckCollisionRecs(PongRect, Player2Rect) && pongMovingLeft) {
			Pong.x -= MOVE_AMOUNT_PONG;
		} else if (CheckCollisionRecs(PongRect, Player2Rect) && pongMovingRight) {
			pongMovingRight  = false;
			pongMovingLeft   = true;
			Pong.x -= MOVE_AMOUNT_PONG;
		} else if (!CheckCollisionRecs(PongRect, Player2Rect) && pongMovingLeft) {
			Pong.x -= MOVE_AMOUNT_PONG;
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
