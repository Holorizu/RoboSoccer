#include <stdio.h>
#include "raylib.h"

int main() 
{

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Game_window");
	SetTargetFPS(60);

	// Defining Camera 	
	Camera3D camera =  {0};
	camera.position = (Vector3) {10.0f, 10.0f, 10.0f};     // Camera Position
	camera.target = (Vector3) {0.0f, 0.0f, 0.0f};          // Camera Looking point
	camera.up = (Vector3) {0.0f, 1.0f, 0.0f};			   // Camera up Vector (Rotation Towards Target)
	camera.fovy = 45.0f;								   // Camera FOV Y axis?
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 cubePosition ={0.0f, 0.0f, 0.0f}; 
	DisableCursor();


	while (!WindowShouldClose())
	{

		UpdateCamera(&camera, CAMERA_FREE);				   // Camera updating 	

		if (IsKeyPressed(KEY_Z)) camera.target = (Vector3) {0.0f, 0.0f, 0.0f};


		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

			DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, MAGENTA);
			DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);

			DrawGrid(10, 1.0f);

		EndMode3D();

		EndDrawing();
	}

	CloseWindow();


	return 0;
}
