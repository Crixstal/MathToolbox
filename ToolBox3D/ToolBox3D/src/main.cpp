#include <raylib.h>

#include "Application.h"
#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Quad.h"
#include "Box.h"

int main()
{
    Application app;
    Vector3 interPt = {};
    Vector3 interNormal = {};

    Segment segment = { {}, {2.f, 2.f, 1.f} };

    Plane plane = { {1.f, 1.f, 0.f}, 1.f };

    Sphere sphere;

    Cylinder cylinder = { {0.f, 0.f, 0.f}, {3.f, 3.f, 0.f}, 1.f };

    Quad quad = { {0.f, 0.f, 0.f}, {2.f, 2.f, 2.f}, {1.f, 1.f, 1.f} };

    Quaternion quaternion = QuaternionFromAxisAngle({0, 1, 0}, PI);

    Box box = { {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f} };
    
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

        rlDisableBackfaceCulling();

        app.drawGrid();

        plane.normal = normalize({cosf(GetTime()), sinf(GetTime()), cosf(GetTime() / 3)});

        plane.drawIntersection(segment, plane, interPt, interNormal);
        //sphere.myDrawSphere(30.f, 30.f);
        //quad.myDrawQuad(quad.center, quad.unitNormal, quad.size, quaternion);
        //cylinder.myDrawCylinder(cylinder.ptA, cylinder.ptB, cylinder.radius);
        //box.myDrawBox(box.center, box.size);

        EndMode3D();

        app.cameraControls();

        DrawFPS(700, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}