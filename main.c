#include "raylib.h"
#include "raymath.h"

#define PLAYER_SPEED 5.0f
#define PLAYER_ACCEL 3.0f

int main()
{

    Vector3 playerPosition = { 0.0f, 0.0f, 0.0f};
    Vector3 playerSize = { 1.0f, 1.0f, 1.0f};
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "RoboSoccer");

    Camera3D camera = { 0 };
    camera.position = (Vector3){2.0f, 5.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model player = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
    
    float dt = GetFrameTime();
    float rotation = 0.0f;
    
    SetTargetFPS(60);



    while (!WindowShouldClose())
    {
	rotation += 1.0f;

	DrawModelEx(player, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.5f, 1.0f, 0.0f },rotation, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);

	BeginDrawing();

	ClearBackground (RAYWHITE);

	BeginMode3D(camera);


	DrawGrid(10, 10.0f);

	EndMode3D();

	DrawFPS(10,10);

	EndDrawing();
	
    }

    UnloadModel(player);
    CloseWindow();


    return 0;
}


