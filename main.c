#include <stdio.h>
#include "raylib.h"


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

static int gamepadIndex = 0;
static ActionInput actionInputs[MAX_ACTION] = {0};


static bool IsActionPressed(int action);
static bool IsActionReleased(int action);
static bool IsActionDown(int action);
static void SetActionsDefault(void);
static void SetActionsCursor(void);



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



	// Defining idk (i just wanna move the cube)
	char actionSet = 0;
	SetActionsDefault();
	bool releaseAction = false;

	Vector3 position = (Vector3){0.0f, 0.0f, 0.0f};
        Vector3 size = (Vector3){40.0f, 40.0f, 40.0f};




	while (!WindowShouldClose())
	{

	    if (IsActionPressed(ACTION_UP))
		position.y -= 2;
	    if (IsActionPressed(ACTION_DOWN))
		position.y += 2;
	    if (IsActionPressed(ACTION_DOWN))
		position.x -= 2;
	    if (IsActionPressed(ACTION_DOWN))
		position.x += 2;


            releaseAction = false;

	    

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


static bool IsActionPressed(int action)
{
	bool result = false;

	if (action < MAX_ACTION)
		result = (IsKeyPressed(actionInputs[action].key));

	return result;
}


static bool IsActionReleased(int action)
{
	bool result = false;

	if (action < MAX_ACTION)
		result = (IsKeyPressed(actionInputs[action].key));

	return result;
}

static bool IsActionDown(int action)
{
	bool result = false;

	if (action < MAX_ACTION)
		result = (IsKeyPressed(actionInputs[action].key));

	return result;
}

static void SetActionsDefault(void)
{
	actionInputs[ACTION_UP].key = KEY_UP;
	actionInputs[ACTION_DOWN].key = KEY_DOWN;
	actionInputs[ACTION_LEFT].key = KEY_LEFT;
	actionInputs[ACTION_RIGHT].key = KEY_RIGHT;
	actionInputs[ACTION_BRAKE].key = KEY_SPACE;
}
