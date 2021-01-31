#include "Application.h"

void Application::initWindow()
{
	int screenWidth = 800;
	int screenHeight = 450;
	
	InitWindow(screenWidth, screenHeight, "Math Tool Box 3D");
}

Camera3D Application::initCamera()
{
    Camera3D camera {
        { 0.0f, 10.0f, 10.0f }, // Camera position
        { 0.0f, 0.0f, 0.0f },   // Camera looking at point
        { 0.0f, 1.0f, 0.0f },   // Camera up vector (rotation towards target)
        45.0f,                  // Camera field-of-view Y
        CAMERA_PERSPECTIVE      // Camera mode type
    };

    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);

    return camera;
}

void Application::drawGrid()
{
    DrawGrid(10, 1.f);
    DrawLine3D({ 0, -5, 0 }, { 0,5,0 }, GRAY);

    // Gizmo
    DrawLine3D({ 0, 0, 0 }, { 0,5,0 }, GREEN);
    DrawLine3D({ 0, 0, 0 }, { 5,0,0 }, RED);
    DrawLine3D({ 0, 0, 0 }, { 0,0,5 }, BLUE);
}

void Application::cameraControls()
{
    DrawRectangle(10, 10, 320, 110, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 320, 110, BLUE);
    DrawText("Free camera default controls:", 20, 20, 10, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
    DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
    DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
    DrawText("- Z to reset position to (0, 0, 0)", 40, 100, 10, DARKGRAY);
}