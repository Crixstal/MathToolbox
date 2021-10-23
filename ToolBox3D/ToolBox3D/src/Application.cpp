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

        if (stateChanger > 6)
            stateChanger = 0;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        --stateChanger;

        if (stateChanger < 0)
            stateChanger = 6;
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

        default: break;
    }
}

void Application::drawIntersection()
{
    Vector3 interPt = {};
    Vector3 interNormal = {};
    Segment segment = { {-2.0f, -2.0f, -1.0f}, {2.0f, 2.0f, 1.0f} };
    static Plane plane ({ 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
    static Quad quad({}, Quaternion{0.f, 1.f, 0.f, 0.f}, { 1.0f, 2.0f });
    static Sphere sphere ({}, 1.0f, QuaternionIdentity());
    Cylinder cyl ({}, { 0.0f, 3.0f, 0.0f }, 1.0f, isInfinite, QuaternionIdentity());
    static Capsule caps ({}, { 0.0f, 3.0f, 0.0f }, 1.0f);
    static Box box ({}, { 1.0f, 1.0f, 1.0f }, QuaternionIdentity());
    static Round_Box roundBox({}, { 1.0f, 1.0f, 1.0f }, QuaternionIdentity(), 0.5f);
   
    float time = GetTime();

    switch (state)
    {
        case State::PLANE: 
            plane.normal = normalize({ cosf(time),  2 * sinf(time), 1.0f});
            plane.distance = 2 * cosf(time);
            plane.drawIntersection(segment, interPt, interNormal);
            break;

        case State::QUAD:
            move(quad.center, quad.quaternion);
            //quad.center = { 2 * cosf(time), cosf(time), 2.5f * sinf(time) };
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
            //box.center = { 2 * sinf(time), cosf(time), sinf(time) };
            move(box.center, box.quaternion);
            box.drawIntersection(segment, interPt, interNormal);
            break;

        case State::ROUND_BOX:
            //roundBox.center = { 2 * cosf(time), cosf(time), 2.5f * sinf(time) };
            move(roundBox.center, roundBox.quaternion);
            roundBox.drawIntersection(segment, interPt, interNormal);
            break;

        default: break;
    }
}

void Application::move(Vector3& toMove, Quaternion& quaternion)
{
    Vector3 rotation = Vector3RotateByQuaternion(Vector3{ 0.f, 1.f, 0.f }, quaternion);

    if (IsKeyDown(KEY_S))
        toMove.z -= 0.1f;
    else if (IsKeyDown(KEY_W))
        toMove.z += 0.1f;

    if (IsKeyDown(KEY_A))
        toMove.x -= 0.1f;
    else if (IsKeyDown(KEY_D))
        toMove.x += 0.1f;

    if (IsKeyDown(KEY_Q))
        toMove.y -= 0.1f;
    else if (IsKeyDown(KEY_E))
        toMove.y += 0.1f;

    // ROTATION

    if (IsKeyDown(KEY_J))
        rotation.x -= 0.1f;
    else if (IsKeyDown(KEY_L))
        rotation.x += 0.1f;

    if (IsKeyDown(KEY_K))
        rotation.z -= 0.1f;
    else if (IsKeyDown(KEY_I))
        rotation.z += 0.1f;

    if (IsKeyDown(KEY_U))
        rotation.y -= 0.1f;
    else if (IsKeyDown(KEY_O))
        rotation.y += 0.1f;

    quaternion = QuaternionFromVector3ToVector3(Vector3{ 0.f, 1.f, 0.f }, rotation);
}
