#include <raylib.h>

#include "Application.h"
#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Quad.h"

int main()
{
    Application app;
    Vector3 interPt = {};
    Vector3 interNormal = {};
    Segment segment = { {}, {2.f, 2.f, 1.f} };
    Plane plane = { {0.f, 2.f, 0.f}, 0.f };
    Sphere sphere;
    Cylinder cylinder = { {0.f, 0.f, 0.f}, {3.f, 3.f, 0.f}, 1.f };
    Quad quad = { {0.f, 0.f, 0.f}, {2.f, 2.f, 2.f}, {1.f, 1.f} };
    
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

        plane.drawIntersection(segment, plane, interPt, interNormal);
        //sphere.myDrawSphere(30.f, 30.f);
        //quad.myDrawRectangle(quad.center, quad.unitNormal, quad.extensions);
        //cylinder.myDrawCylinder(cylinder.ptA, cylinder.ptB, cylinder.radius);

        EndMode3D();

        app.cameraControls();

        DrawFPS(700, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}