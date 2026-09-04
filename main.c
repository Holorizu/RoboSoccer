#include <stdio.h>
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"

#define MAX_COLUMNS 20
#define PLAYER_SPEED 5.0f
#define PLAYER_ROT_SPEED 2.0f

typedef struct Player {
    Vector3 position;
    Vector3 size;
    Vector3 rotation;
} Player_bot;


int main()
{

    const int screenWidth = 1000;
    const int screenHeight = 650;

    
    InitWindow(screenWidth, screenHeight, "Game_window");


    Vector3 playerPosition = { 0.0f, 1.0f, 2.0f };
    Vector3 playerSize = { 1.0f, 2.0f, 1.0f };
    Vector3 playerDir = {0.0f, 0.0f, 0.0f};
    Vector3 rotation = {0.0f, 0.0f, 0.0f};
    Color playerColor = GREEN;

    Vector3 enemyBoxPos = { -4.0f, 1.0f, 0.0f };
    Vector3 enemyBoxSize = { 2.0f, 2.0f, 2.0f };

    Vector3 enemySpherePos = { 4.0f, 0.0f, 0.0f };

    float enemySphereSize = 1.5f;
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
	playerDir.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        playerDir.z = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
	playerDir = Vector3Normalize(playerDir);

	// update
	playerPosition.x += playerDir.x * PLAYER_SPEED * dt;
	playerPosition.z += playerDir.z * PLAYER_SPEED * dt;
	

        // Check collisions player vs enemy-box
	collision = false;
	
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ playerPosition.x - playerSize.x/2,
                                     playerPosition.y - playerSize.y/2,
                                     playerPosition.z - playerSize.z/2 },
                          (Vector3){ playerPosition.x + playerSize.x/2,
                                     playerPosition.y + playerSize.y/2,
                                     playerPosition.z + playerSize.z/2 }},
            (BoundingBox){(Vector3){ enemyBoxPos.x - enemyBoxSize.x/2,
                                     enemyBoxPos.y - enemyBoxSize.y/2,
                                     enemyBoxPos.z - enemyBoxSize.z/2 },
                          (Vector3){ enemyBoxPos.x + enemyBoxSize.x/2,
                                     enemyBoxPos.y + enemyBoxSize.y/2,
                                     enemyBoxPos.z + enemyBoxSize.z/2 }})) collision = true;

        // Check collisions player vs enemy-sphere
        if (CheckCollisionBoxSphere(
            (BoundingBox){(Vector3){ playerPosition.x - playerSize.x/2,
                                     playerPosition.y - playerSize.y/2,
                                     playerPosition.z - playerSize.z/2 },
                          (Vector3){ playerPosition.x + playerSize.x/2,
                                     playerPosition.y + playerSize.y/2,
                                     playerPosition.z + playerSize.z/2 }},
            enemySpherePos, enemySphereSize)) collision = true;

        if (collision) playerColor = RED;
        else playerColor = GREEN;

	
	BeginDrawing();
		
	ClearBackground(RAYWHITE);

	BeginMode3D(camera);

	// Draw enemy-box
	DrawCube(enemyBoxPos, enemyBoxSize.x, enemyBoxSize.y, enemyBoxSize.z, GRAY);
	DrawCubeWires(enemyBoxPos, enemyBoxSize.x, enemyBoxSize.y, enemyBoxSize.z, DARKGRAY);

	// Draw enemy-sphere
	DrawSphere(enemySpherePos, enemySphereSize, GRAY);
	DrawSphereWires(enemySpherePos, enemySphereSize, 16, 16, DARKGRAY);

	// Draw player
	DrawCubeV(playerPosition, playerSize, playerColor);

	DrawGrid(10, 1.0f);

	EndMode3D();

	EndDrawing();
    }

    CloseWindow();


    return 0;
}



