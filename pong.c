#include "raylib.h"

#define PONGRADIUS 10.0f
#define PLAYERSPEED 100.0f
#define PLAYERECWIDTH 50
#define PLAYERECHEIGHT 200

const int screenWidth = 600;
const int screenHeight = 800;

int main(){

  Rectangle PlayerOneRec = { (float)screenWidth/2 - 250.0f, (float)screenHeight/2 , PLAYERECWIDTH , PLAYERECHEIGHT};
  Rectangle PlayerTwoRec = { (float)screenWidth/2 + 200.0f , (float)screenHeight/2 , PLAYERECWIDTH , PLAYERECHEIGHT};

    
  InitWindow(screenWidth, screenHeight, "Pong Game");
  SetTargetFPS(60);
  while(!WindowShouldClose()){
    float dt = GetFrameTime();
    BeginDrawing();
      ClearBackground(RAYWHITE);
      // For Player 1
      if(IsKeyDown(KEY_W)){
        PlayerOneRec.y -= PLAYERSPEED * dt;
      }
      if(IsKeyDown(KEY_S)){
        PlayerOneRec.y += PLAYERSPEED * dt;
      }

      // For Player 2 
      if(IsKeyDown(KEY_UP)){
        PlayerTwoRec.y -= PLAYERSPEED *  dt;
      }
      if(IsKeyDown(KEY_DOWN)){
        PlayerTwoRec.y += PLAYERSPEED * dt;
      }

      // Collison Detection
      if(PlayerOneRec.y + PLAYERECHEIGHT >= screenHeight) PlayerOneRec.y = screenHeight - PLAYERECHEIGHT ;
      if(PlayerOneRec.y <= 0) PlayerOneRec.y = 0;


      if(PlayerTwoRec.y + PLAYERECHEIGHT >= screenHeight) PlayerTwoRec.y = screenHeight - PLAYERECHEIGHT ;
      if(PlayerTwoRec.y <= 0) PlayerTwoRec.y = 0;
      DrawRectangle(PlayerOneRec.x, PlayerOneRec.y,PlayerOneRec.width, PlayerOneRec.height, RED);
      DrawRectangle(PlayerTwoRec.x, PlayerTwoRec.y,PlayerTwoRec.width, PlayerTwoRec.height, RED);
    EndDrawing();
  }
  CloseWindow();
}
