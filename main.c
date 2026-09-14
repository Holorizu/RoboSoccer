#include "raylib.h"
#include "raymath.h"
#include <math.h>

#define PLAYER_SPEED 20.0f
//#define PLAYER_ACCEL 3.0f
#define PLAYER_ROT_SPEED 6.0f

typedef struct {
    float x, y, z;
} vec;

vec getfor(float direction)
{
    vec forward;
    forward.x = sinf(direction);
    forward.y = 0.0f;
    forward.z = cosf(direction);

    return forward;
}


int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "RoboSoccer");

    Vector3 playerPosition = { 0.0f, 1.0f, 0.0f};
    Vector3 playerSize = { 2.0f, 2.0f, 2.0f};
    float direction = 0.0f;
    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 2.0f, 5.0f, 10.0f};
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model player = LoadModelFromMesh(GenMeshCube( 1.0f, 1.0f, 1.0f));
    Model ball = LoadModelFromMesh(GenMeshSphere( 1.0f, 20, 20));

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
	    
	float dt = GetFrameTime();

	if (IsKeyDown(KEY_UP))
	{
	    vec go_forward  = getfor(direction);
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
	    vec go_forward  = getfor(direction);
	    playerPosition.x += go_forward.x * PLAYER_SPEED * dt;
	    playerPosition.z += go_forward.z * PLAYER_SPEED * dt;	    
	}	    
		
	player.transform = MatrixRotateXYZ((Vector3){ 0,direction, 0});
	     
	BeginDrawing();

	ClearBackground (RAYWHITE);

	BeginMode3D(camera);

	camera.target = playerPosition;
	DrawModelEx(player, playerPosition, (Vector3){ 0.0f, 1.0f, 0.0f },direction * DEG2RAD, playerSize, GREEN);
	DrawModel(ball, (Vector3){ 3.0f, 0.0f, -5.0f }, 1.0f, BLUE);
	
	DrawGrid(10, 10.0f);

	EndMode3D();

	DrawFPS(10,10);

	EndDrawing();

    }

    UnloadModel(player);
    UnloadModel(ball);    
    CloseWindow();


    return 0;
}


