#include "raylib.h"
#include "raymath.h"
#include <math.h>


#define PLAYER_SPEED 20.0f
//#define PLAYER_ACCEL 3.0f
#define PLAYER_ROT_SPEED 6.0f

typedef struct {
    float x, y, z;
} vec;

Vector3 getfor(float yaw)
{
    Vector3 forward;
    forward.x = sinf(yaw);
    forward.y = 0.0f;
    forward.z = cosf(yaw);

    return forward;
}


int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "RoboSoccer");

    // PLayer
    Vector3 playerPosition = { 0.0f, 1.0f, 0.0f };
    Vector3 playerSize = { 2.0f, 2.0f, 2.0f };
    float direction = 0.0f;
    Color playerColor = GREEN;

    // Ball
    Vector3 ballPosition = { 3.0f, 0.0f, -5.0f };
    float ballRadius = 1.0f;
    Color ballColor = GREEN;

    // Ground
    Vector3 groundPosition = { 0.0f, -8.0f, 0.0f };
    Vector3 groundSize = { 20.0f , 0.5, 20.0f };
    
    
    // Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 2.0f, 3.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 70.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load Model
    Model player = LoadModelFromMesh(GenMeshCube( 1.0f, 1.0f, 1.0f ));
    Model socBall = LoadModelFromMesh(GenMeshSphere( 2.0f, 20, 20 ));

    SetTargetFPS(60);

    //phyics???????
    float Gravity = 10.0f;
    bool ballCollision = false;
    bool playerCollision = false;
    //bool canMove = false;


    while (!WindowShouldClose())
    {
	
	float dt = GetFrameTime();
	ballCollision = false;
	playerCollision = false;
	//canMove = false;


	// Controls
	if (IsKeyDown(KEY_UP))
	{
	    Vector3 go_forward  = getfor(direction);
	    playerPosition.x -= go_forward.x * PLAYER_SPEED * dt;
	    playerPosition.z -= go_forward.z * PLAYER_SPEED * dt;	    
	}
	if (IsKeyDown(KEY_LEFT))
	{
	    direction += PLAYER_ROT_SPEED * dt;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
	    direction -= PLAYER_ROT_SPEED * dt;
	}
	if (IsKeyDown(KEY_DOWN))
	{
	    Vector3 go_forward  = getfor(direction);
	    playerPosition.x += go_forward.x * PLAYER_SPEED * dt;
	    playerPosition.z += go_forward.z * PLAYER_SPEED * dt;	    
	}



        // Model Rotation	
	player.transform = MatrixRotateXYZ((Vector3){ 0,direction, 0});

	// applying the physics ig
	playerPosition.y -= Gravity * dt;
	ballPosition.y -=Gravity * dt;

        if (CheckCollisionBoxes(
                (BoundingBox){(Vector3){playerPosition.x - playerSize.x / 2,
                                        playerPosition.y - playerSize.y / 2,
                                        playerPosition.z - playerSize.z / 2},
                              (Vector3){playerPosition.x + playerSize.x / 2,
                                        playerPosition.y + playerSize.y / 2,
                                        playerPosition.z + playerSize.z / 2}},
                (BoundingBox){(Vector3){groundPosition.x - groundSize.x / 2,
                                        groundPosition.y - groundSize.y / 2,
                                        groundPosition.z - groundSize.z / 2},
                              (Vector3){groundPosition.x + groundSize.x / 2,
                                        groundPosition.y + groundSize.y / 2,
                                        groundPosition.z + groundSize.z / 2}}))
	{
	    playerCollision = true;
	    //canMove = true;
	}

	if (CheckCollisionBoxSphere(
                (BoundingBox){(Vector3){groundPosition.x - groundSize.x / 2,
                                        groundPosition.y - groundSize.y / 2,
                                        groundPosition.z - groundSize.z / 2},
                              (Vector3){groundPosition.x + groundSize.x / 2,
                                        groundPosition.y + groundSize.y / 2,
                                        groundPosition.z + groundSize.z / 2}},
		ballPosition, ballRadius))
	{
	    ballCollision = true;
	    //canMove = true;
	}

        if (playerCollision)
	{
	    playerPosition.y += Gravity * dt;
	 	    
	}
	if (ballCollision)
	{
	    ballPosition.y += Gravity * dt;
	    ballColor = WHITE;
	}

	
    
	BeginDrawing();

	ClearBackground (RAYWHITE);

	BeginMode3D(camera);

	camera.target = playerPosition;

	DrawModelEx(player, playerPosition, (Vector3){ 0.0f, 1.0f, 0.0f },direction * DEG2RAD, playerSize, playerColor);
	DrawModel(socBall, ballPosition, 1.0f, ballColor);

	DrawCube(groundPosition, groundSize.x, groundSize.y, groundSize.z, BLUE);
	
	DrawGrid(10, 10.0f);

	EndMode3D();

	DrawFPS(10,10);

	EndDrawing();

    }

    UnloadModel(player);
    UnloadModel(socBall);    
    CloseWindow();


    return 0;
}


