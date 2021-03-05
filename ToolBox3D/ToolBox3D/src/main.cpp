#include <raylib.h>

#include "Application.h"

int main()
{
    Application app;
    
    app.initWindow();
    Camera3D camera = app.initCamera();

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        if (IsKeyDown('Z'))
            camera.target = {};
        
        BeginDrawing();
        
        app.changeMode();
        
        ClearBackground(DARKGRAY);
        
        BeginMode3D(camera);
        
        rlDisableBackfaceCulling();
        
        app.drawGrid();  
        app.drawIntersection();

        EndMode3D();
        
        app.cameraControls();
        DrawFPS(700, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}