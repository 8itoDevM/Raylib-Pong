#include "raylib.h"



class Ball{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Update(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
        }

        if(x + radius >= GetScreenWidth() || x - radius <= 0){
            speed_x *= -1;
        }
    }
};

class Paddle{
protected:
    void LimitMovement(){
        if(y <= 0){
            y = 0;
        } else if(y >= GetScreenHeight() - height){
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE); 
    }

    void Update(){
        if(IsKeyDown(KEY_UP)){
            y -= speed;
        } else if(IsKeyDown(KEY_DOWN)){
            y += speed;
        }

        LimitMovement();
    }
};

class CpuPaddle : public Paddle{
public:
    void Update(int ball_y){
        if(y + height/2 >= ball_y){
            y -= speed;
        } else {
            y += speed;
        }

        LimitMovement();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main(){
    const int screen_width = 1280;
    const int screen_height = 720;

    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width  = 25;
    player.height = 120;
    player.x = screen_width - player.width -10;
    player.y = screen_height/2 -player.height/2;
    player.speed = 6;

    cpu.width  = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.speed = 6;

    InitWindow(screen_width, screen_height, "Pong");
    SetTargetFPS(60);

    // GameLoop
    while(WindowShouldClose() == false){
        BeginDrawing();

        // Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        }

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1;
        }

        ClearBackground(BLACK);

        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}