#include <raylib.h>

#include "Application.h"
#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Quad.h"

int main()
{
    Application app;
    Plane plane = {{ 0, 2, 0 }, 0};
    Sphere sphere;
    Cylinder cylinder;
    Quad quad;
    
    app.initWindow();

    Camera3D camera = app.initCamera();

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        if (IsKeyDown('Z'))
            camera.target = { 0.0f, 0.0f, 0.0f };

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        app.drawGrid();

        //plane.drawPlane(plane.normal);
        sphere.drawSphere();

        EndMode3D();

        app.cameraControls();

        DrawFPS(700, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}