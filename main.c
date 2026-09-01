#include <stdio.h>
#include "raylib.h"
#include "rcamera.h"

#define MAX_COLUMNS 20

// Defining Controls ig (i just wanna be able to move the cube

typedef enum ActionType {
    NO_ACTION = 0,
    ACTION_UP,
    ACTION_DOWN,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_BRAKE,
    MAX_ACTION
} ActionType;


typedef struct ActionInput {
    int key;
    int button;
} ActionInput;


int main()
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    


    InitWindow(screenWidth, screenHeight, "Game_window");

    float playerX = 100;
    float playerY = 300;
    float velocityY = 0;

    Vector3 playerPosition = { 0.0f, 1.0f, 2.0f };
    Vector3 playerSize = { 1.0f, 2.0f, 1.0f };
    Color playerColor = GREEN;

    Vector3 enemyBoxPos = { -4.0f, 1.0f, 0.0f };
    Vector3 enemyBoxSize = { 2.0f, 2.0f, 2.0f };

    Vector3 enemySpherePos = { 4.0f, 0.0f, 0.0f };

    float enemySphereSize = 1.5f;
    bool collision = false;

    SetTargetFPS(60);

    // Defining Camera
    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };


    DisableCursor();

    // Defining idk (i just wanna move the cube)
    char actionSet = 0;
    bool releaseAction = false;

    Vector3 position = (Vector3){0.0f, 0.0f, 0.0f};
    Vector3 size = (Vector3){40.0f, 40.0f, 40.0f};


    while (!WindowShouldClose())
    {
	float deltaTime = GetFrameTime();

	// update

	// movement
	if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 0.2f;
        else if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 0.2f;
        else if (IsKeyDown(KEY_DOWN)) playerPosition.z += 0.2f;
        else if (IsKeyDown(KEY_UP)) playerPosition.z -= 0.2f;
	
	collision = false;

        // Check collisions player vs enemy-box
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



