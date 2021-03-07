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
    DrawLine3D({ 0, 0, 0 }, { 5,0,0 }, RED);
    DrawLine3D({ 0, 0, 0 }, { 0,5,0 }, GREEN);
    DrawLine3D({ 0, 0, 0 }, { 0,0,5 }, BLUE);
}

void Application::cameraControls()
{
    DrawRectangle(10, 10, 250, 110, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 250, 110, BLUE);
    DrawText("Free camera default controls:", 20, 20, 10, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, BLACK);
    DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, BLACK);
    DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, BLACK);
    DrawText("- Z to reset target to (0, 0, 0) (QWERTY)", 40, 100, 10, BLACK);
}

void Application::changeMode()
{
    DrawText("Click right/left to change mode", 400, 30, 10, BLACK);

    if (IsKeyPressed(KEY_RIGHT))
    {
        ++stateChanger;

        if (stateChanger > 7)
            stateChanger = 0;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        --stateChanger;

        if (stateChanger < 0)
            stateChanger = 7;
    }

    if (IsKeyPressed(KEY_UP))
        isInfinite = true;

    if (IsKeyPressed(KEY_DOWN))
        isInfinite = false;

    state = static_cast<State>(stateChanger);

    switch (state)
    {
        case State::PLANE:
            DrawText("Plane", 450, 10, 20, BLACK);
            break;

        case State::QUAD:
            DrawText("Quad", 450, 10, 20, BLACK);
            break;

        case State::SPHERE:
            DrawText("Sphere", 450, 10, 20, BLACK);
            break;

        case State::CYLINDER:
            DrawText("Cylinder", 450, 10, 20, BLACK);
            DrawText("Click up/down to change cylinder", 400, 40, 10, BLACK);

            if (isInfinite == true)
                DrawText("(infinite)", 536, 10, 20, BLACK);

            if (isInfinite == false)
                DrawText("(finite)", 536, 10, 20, BLACK);

            break;

        case State::CAPSULE:
            DrawText("Capsule", 450, 10, 20, BLACK);
            break;

        case State::BOX:
            DrawText("Box", 450, 10, 20, BLACK);
            break;

        case State::ROUND_BOX:
            DrawText("Round box", 450, 10, 20, BLACK);
            break;

        case State::BOUNCING_BALL:
            DrawText("Bouncing ball", 450, 10, 20, BLACK);
            break;

        default: break;
    }
}

void Application::drawIntersection()
{
    Vector3 interPt = {};
    Vector3 interNormal = {};
    Segment segment = { {-2.0f, -2.0f, -1.0f}, {2.0f, 2.0f, 1.0f} };
    Plane plane ({ 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
    Quad quad ({}, QuaternionIdentity(), { 1.0f, 2.0f });
    Sphere sphere ({}, 1.0f);
    Cylinder cyl ({}, { 0.0f, 3.0f, 0.0f }, 1.0f, isInfinite);
    Capsule caps ({}, { 0.0f, 3.0f, 0.0f }, 1.0f);
    Box box ({}, { 1.0f, 1.0f, 1.0f }, QuaternionIdentity());
    Round_Box roundBox({}, { 1.0f, 1.0f, 1.0f }, QuaternionIdentity());
   
    float time = GetTime();

    switch (state)
    {
        case State::PLANE: 
            plane.normal = normalize({ cosf(time),  2 * sinf(time), 1.0f});
            plane.distance = 2 * cosf(time);
            plane.drawIntersection(segment, interPt, interNormal);
            break;

        case State::QUAD:
            quad.center = { 2 * cosf(time), cosf(time), 2.5f * sinf(time) };
            quad.drawIntersection(segment, interPt, interNormal);
            break;

        case State::SPHERE: 
            sphere.center = { sinf(time), cosf(time), sinf(time) };
            sphere.drawIntersection(segment, 20, 20, interPt, interNormal);
            break;

        case State::CYLINDER:
            cyl.ptP = { 2 * sinf(GetTime()), -1.f, 2 * sinf(GetTime()) };
            cyl.ptQ = { 2 * sinf(GetTime()) / 2, 2.f, cosf(GetTime()) };
            cyl.drawIntersection(segment, interPt, interNormal);
            break;

        case State::CAPSULE:
            caps.ptP = { 2 * sinf(GetTime()), -1.f, 2 * sinf(GetTime()) };
            caps.ptQ = { 2 * sinf(GetTime()) / 2, 2.f, cosf(GetTime()) };
            caps.drawIntersection(segment, interPt, interNormal);
            break;

        case State::BOX:
            box.center = { 2 * sinf(time), cosf(time), sinf(time) };
            box.drawIntersection(segment, interPt, interNormal);
            break;

        case State::ROUND_BOX:
            //roundBox.center = { 2 * cosf(time), cosf(time), 2.5f * sinf(time) };
            roundBox.myDrawRoundBox();
            break;

        case State::BOUNCING_BALL:
            break;

        default: break;
    }
}