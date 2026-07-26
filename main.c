#include <stdio.h>
#include "raylib.h"

int main() 
{

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Game_window");
	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}

	CloseWindow();


	return 0;
}
