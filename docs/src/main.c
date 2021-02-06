#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#ifdef OS_WEB
#include <emscripten/emscripten.h>
#endif

#define WIDTH 800
#define HEIGHT 600

Camera3D camera3D = {0};
Camera2D camera2D = {0};
Vector3 cube_position = {0.0f, 2.0f, 0.0f};
Vector3 tree_position = {0.0f, 2.0f, 0.0f};
Texture2D hero = {0};
Texture2D map = {0};

float heroSpeed = 0.1f;

void update_frame()
{
    BeginDrawing();
    {

        ClearBackground(WHITE);
        DrawFPS(10, 10);

        BeginMode3D(camera3D);
        {
            // DrawCube(cube_position, 1, 1, 1, RED);
            DrawGrid(10, 1);
            DrawCubeTexture(map, (Vector3){0.f, 0.f, 0.f}, 10, 0.1f, 10, WHITE);
            if(Vector3Distance(camera3D.position, cube_position) <= Vector3Distance(camera3D.position, tree_position)) {
                DrawBillboard(camera3D, hero, tree_position, 2.0f, WHITE);
                DrawBillboard(camera3D, hero, cube_position, 2.0f, WHITE);
            } else {
                DrawBillboard(camera3D, hero, cube_position, 2.0f, WHITE);
                DrawBillboard(camera3D, hero, tree_position, 2.0f, WHITE);
            }
        }
        EndMode3D();

        if (IsKeyDown(KEY_KP_ADD))
            camera3D.fovy += 1.0f;
        if (IsKeyDown(KEY_KP_SUBTRACT))
            camera3D.fovy -= 1.0f;

        if (IsKeyDown(KEY_LEFT))
            cube_position.x -= heroSpeed;
        if (IsKeyDown(KEY_RIGHT))
            cube_position.x += heroSpeed;
        if (IsKeyDown(KEY_UP))
            cube_position.z -= heroSpeed;
        if (IsKeyDown(KEY_DOWN))
            cube_position.z += heroSpeed;
    }
    EndDrawing();
}

int main(void)
{
#ifdef OS_Windows_NT
    printf("Windows dettected\n");
#elif defined OS_Linux
    printf("LINUS dettected\n");
#elif defined OS_Darwin
    printf("MacOS dettected\n");
#endif

    InitWindow(WIDTH, HEIGHT, "Isometric world");
    SetTargetFPS(60);

    hero = LoadTexture("assets/billboard.png");
    map = LoadTexture("assets/map.png");

    SetTextureFilter(hero, FILTER_BILINEAR);
    SetTextureFilter(map, FILTER_BILINEAR);

    camera3D.fovy = 10.0f;
    camera3D.target = (Vector3){.0f, .0f, .0f};
    camera3D.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera3D.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera3D.type = CAMERA_ORTHOGRAPHIC;

#ifdef OS_WEB
    emscripten_set_main_loop(update_frame, 0, 1);
#else
    while (!WindowShouldClose())
    {
        update_frame();
    }
#endif
    CloseWindow();

    return 0;
}