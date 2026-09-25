#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PONGRADIUS 20.0f
#define PLAYERSPEED 200.0f
#define PLAYERECWIDTH 50
#define PLAYERECHEIGHT 200

const int screenWidth = 600;
const int screenHeight = 800;
int playerOneScore = 0;
int playerTwoScore = 0;
char scoreText[20];

void ResetBall(Vector2 *position ,Vector2 *velocity ,float InitialVelocity){

  playerOneScore = 0;
  playerTwoScore = 0;

  position->x = (float)screenWidth/2;
  position->y = (float)screenHeight/2;

  float randomServeAngle = GetRandomValue(-45, 45); 
  float radServeAngle = randomServeAngle * (PI/180);

  // calculating Velocities
  
  velocity->x = InitialVelocity * cosf(radServeAngle);
  velocity->y = -InitialVelocity * sinf(radServeAngle);

  if(GetRandomValue(0,1) == 0){
    velocity->x = -velocity->x;
  }
};

void ResetPlayerPos(Rectangle *PlayerOnePos ,Rectangle *PlayerTwoPos){
  PlayerOnePos->x = (float)screenWidth/2 - 250.0f;
  PlayerTwoPos->x = (float)screenWidth/2 + 200.0f;
  PlayerOnePos->y = PlayerTwoPos->y = (float)screenHeight/2 - (float)PLAYERECHEIGHT/2;
}

int main(){
  srand(time(NULL));
  Rectangle PlayerOneRec = { (float)screenWidth/2 - 250.0f, (float)screenHeight/2 - (float)PLAYERECHEIGHT/2 , PLAYERECWIDTH , PLAYERECHEIGHT};
  Rectangle PlayerTwoRec = { (float)screenWidth/2 + 200.0f , (float)screenHeight/2 - (float)PLAYERECHEIGHT/2 , PLAYERECWIDTH , PLAYERECHEIGHT};

  float throwAngle = 30 * (PI/180);
  float pongInitialVelocity = 400.0f;

  Vector2 PongPosition = { (float)screenWidth/2 , (float)screenHeight/2 };
  Vector2 PongVelocity = { pongInitialVelocity * cosf(throwAngle) , -pongInitialVelocity*sinf(throwAngle) };

  ResetBall(&PongPosition, &PongVelocity, pongInitialVelocity);

  InitWindow(screenWidth, screenHeight, "Pong Game");
  SetTargetFPS(60);

  while(!WindowShouldClose()){
    float dt = GetFrameTime();
    BeginDrawing();
      ClearBackground(RAYWHITE);
      // For Player 1
      if(IsKeyDown(KEY_W)) PlayerOneRec.y -= PLAYERSPEED * dt;
      if(IsKeyDown(KEY_S)) PlayerOneRec.y += PLAYERSPEED * dt;
      
      // For Player 2 
      if(IsKeyDown(KEY_UP)) PlayerTwoRec.y -= PLAYERSPEED *  dt;
      if(IsKeyDown(KEY_DOWN)) PlayerTwoRec.y += PLAYERSPEED * dt;
      

      // Collison Detection
      if(PlayerOneRec.y + PLAYERECHEIGHT >= screenHeight) PlayerOneRec.y = screenHeight - PLAYERECHEIGHT ;
      if(PlayerOneRec.y <= 0) PlayerOneRec.y = 0;


      if(PlayerTwoRec.y + PLAYERECHEIGHT >= screenHeight) PlayerTwoRec.y = screenHeight - PLAYERECHEIGHT ;
      if(PlayerTwoRec.y <= 0) PlayerTwoRec.y = 0;


      // Pong ball movement

      PongPosition.x += PongVelocity.x * dt;
      PongPosition.y += PongVelocity.y * dt;
      
      // Wall Bouncing
      
      if((PongPosition.y - PONGRADIUS <= 0) || (PongPosition.y + PONGRADIUS >= screenHeight)){
        PongVelocity.y = -PongVelocity.y;
      }

      // Pong Collison handling
    
      if(CheckCollisionCircleRec(PongPosition, PONGRADIUS,  PlayerOneRec)){
        PongVelocity.x = fabsf(PongVelocity.x); 
        playerOneScore += 1;
      }
      if(CheckCollisionCircleRec(PongPosition, PONGRADIUS,  PlayerTwoRec)){
        PongVelocity.x = -fabsf(PongVelocity.x); 
        playerTwoScore += 1;
      }

      if ((PongPosition.x + PONGRADIUS >= screenWidth) || (PongPosition.x - PONGRADIUS <= 0)) {
        ResetBall(&PongPosition ,&PongVelocity , pongInitialVelocity);
        ResetPlayerPos(&PlayerOneRec, &PlayerTwoRec);        
      }

      sprintf(scoreText,"%d | %d", playerOneScore , playerTwoScore);

      // Drawing
      DrawText(scoreText, screenWidth/2 - 40 , 50 , 30, BLUE);
      DrawCircleV(PongPosition, PONGRADIUS , DARKGREEN);
      DrawRectangle(PlayerOneRec.x, PlayerOneRec.y,PlayerOneRec.width, PlayerOneRec.height, RED);
      DrawRectangle(PlayerTwoRec.x, PlayerTwoRec.y,PlayerTwoRec.width, PlayerTwoRec.height, RED);
    EndDrawing();
  }
  CloseWindow();
}


