#include <stdio.h>
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"

#define PLAYER_SPEED 5.0f
#define PLAYER_ROT_SPEED 2.0f

typedef struct Player {
    Vector3 playerPosition;
    Vector3 playerSize;
    Vector3 playerDir;
    float rotation;
} playerBot;


int main()
{

    const int screenWidth = 1000;
    const int screenHeight = 650;
    
    InitWindow(screenWidth, screenHeight, "Game_window");

    struct Player playerBot;
    
    playerBot.playerPosition = (Vector3){ 0.0f, 1.0f, 2.0f };
    playerBot.playerSize = (Vector3) { 1.0f, 2.0f, 1.0f };
    playerBot.playerDir =(Vector3) {0.0f, 0.0f, 0.0f};
    Vector3 velocity = {0.0f};
    Color playerColor = GREEN;

    float rotationg;
    bool collision = false;

    SetTargetFPS(60);

    // Defining Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    DisableCursor();

    while (!WindowShouldClose())
    {
	float dt = GetFrameTime();
	
	// movement
	playerBot.playerDir = Vector3Normalize(playerBot.playerDir);
	float rotation = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT) * PLAYER_ROT_SPEED;
	playerBot.rotation += rotation;

	if (IsKeyDown(KEY_UP))
	{
	    Vector3 go_front = MatrixRotateZ((Vector3){rotation * DEG2RAD});
	    velocity.z = -PLAYER_SPEED * dt;
	    playerBot.playerPosition = Vector3Add(playerBot.playerPosition, velocity);
	}


	
	// update
	playerBot.playerPosition.x += playerBot.playerDir.x * PLAYER_SPEED * dt;
	playerBot.playerPosition.z += playerBot.playerDir.z * PLAYER_SPEED * dt;
	

	BeginDrawing();
		
	ClearBackground(RAYWHITE);

	BeginMode3D(camera);

	// Draw player
	DrawCubeV(playerBot.playerPosition,playerBot.playerSize, playerColor);

	DrawGrid(10, 1.0f);

	EndMode3D();

	EndDrawing();
    }

    CloseWindow();


    return 0;
}



