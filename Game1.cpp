// Game1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <array>
#include <iostream>
#include <raylib.h>

typedef struct Player {

	Rectangle pos_size{ 948,20,50,100 };

	float x_vel = 0;
	float y_vel = 0;

	float speed = 400;
	float acc = 44;
	float decc = 28;

	float grav = 40;
	float term_vel = 600;

	bool isJumping = false;
	bool isGrounded = false;

} Player;

Rectangle platforms[] = {
	{ 0, 700, 1600, 800 },
	{ 1000, 0, 100, 800 },
	{ 200, 0, 100, 800 }
	//{200,400,1600,100}
};

Color platform_color{ 255,255,255,255 };

void do_physics(Player* player) {

	float deltaTime = GetFrameTime();

	if (IsKeyDown(KEY_W)) {
		player->y_vel = -100;
	}
	if (IsKeyDown(KEY_A) && player->x_vel > -player->speed) {
		player->x_vel -= player->acc;
	}
	if (IsKeyDown(KEY_D) && player->x_vel < player->speed) {
		player->x_vel += player->acc;
	}

	if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		if (player->x_vel > 0) {
			if (player->x_vel - (player->decc) < 0) {
				player->x_vel = 0;
			}
			else {
				player->x_vel -= player->decc;
			}
		}
		if (player->x_vel < 0) {
			if (player->x_vel + (player->decc) > 0) {
				player->x_vel = 0;
			}
			else {
				player->x_vel += player->decc;
			}
		}
	}
	player->pos_size.x += player->x_vel * deltaTime;

	if (!player->isGrounded) {
		player->y_vel += player->grav;
	}

	player->pos_size.y += player->y_vel * deltaTime;
}

void collision_detection(Player* player, Rectangle[]) {

	for (int i = 0; i < sizeof(platforms); i++) {
		if (CheckCollisionRecs(player->pos_size, platforms[i])) {
			if (player->y_vel > 0 && player->x_vel != 0) {
				player->y_vel = 0;
				//player->pos_size.y = platforms[i].y - player->pos_size.height;
				player->isGrounded = true;
			} 
			if (player->y_vel < 0) {
				player->y_vel = 0;
				//player->pos_size.y = platforms[i].y + platforms[i].height;
			}
			if (player->x_vel > 0) {
				player->x_vel = 0;
				//player->pos_size.x = platforms[i].x - player->pos_size.width;
			}
			if (player->x_vel < 0) {
				player->x_vel = 0;
				//player->pos_size.x = platforms[i].x + platforms[i].width;
			}
		}
	}
}

void draw_screen(Rectangle[], Player * player) {
	BeginDrawing();

		ClearBackground(BLACK);

		for (int i = 0; i < sizeof(platforms); i++) {
			DrawRectangle(platforms[i].x, platforms[i].y, platforms[i].width, platforms[i].height, platform_color);
		}

		DrawRectangleLines(player->pos_size.x, player->pos_size.y, player->pos_size.width, player->pos_size.height, { 255, 0, 0, 255 });

		DrawFPS(GetScreenWidth() - 200, GetScreenHeight() - 80);

	EndDrawing();
}

int main(void) 
{	
	InitWindow(1600, 800, "Game");

	SetTargetFPS(165);

	Player player;

	while (!WindowShouldClose()) {

		draw_screen(platforms, &player);

		collision_detection(&player, platforms);

		do_physics(&player);
	}

	CloseWindow();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
