// ESAT Libraries
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


// Windows dimensions with default values
const int KWindow_Width = 800;
const int KWindow_Height = 800;

// FPS
double delta_time;
unsigned char fps = 25;
double current_time;
double last_time;

enum EnemyType{
  fireball,
  cross,
  ship,
};

struct Enemy{
  esat::Vec2 dir;
  esat::Vec2* mask_points;
  esat::SpriteTransform st;
  float speed;
  EnemyType type;
  Enemy *next;
};

Enemy *enemy;
esat::SpriteHandle *AllSprites;
int nEnemy = 4;
bool AnimationSprite = 0;

void SetXinitPosition(Enemy *enemy){
  if(rand()%2 == 0){
    enemy->st.x = -esat::SpriteWidth(AllSprites[0]); 
    enemy->speed = 4;
  }
  else{
    enemy->st.x = KWindow_Width;
    enemy->speed = -4;
    enemy->st.scale_x = -enemy->st.scale_x;
    enemy->st.sprite_origin_x += esat::SpriteWidth(AllSprites[0]);
  }
}

void LoadEnemySprite(){
  AllSprites = (esat::SpriteHandle*)malloc(11*sizeof(esat::SpriteHandle));
  if(AllSprites != NULL){
    AllSprites[0] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo_1_1_2x.png");
    AllSprites[1] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo_1_2_2x.png");
    AllSprites[2] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo2_1_2x.png");
    AllSprites[3] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo2_2_2x.png");
    AllSprites[4] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo3_1_2x.png");
    AllSprites[5] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo3_2_2x.png");  
    AllSprites[6] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo4_2x.png");
    AllSprites[7] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo5_2x.png");
    AllSprites[8] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo6_2x.png");
    AllSprites[9] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo7_2x.png");
    AllSprites[10] = esat::SpriteFromFile("./SPRITES/ENEMIGOS/enemigo8_2x.png");
  }
}

void InitEnemyMask(Enemy* enemy){
  enemy->mask_points[0] = {enemy->st.x, enemy->st.y};
  enemy->mask_points[1] = {enemy->st.x + esat::SpriteWidth(AllSprites[0]), enemy->st.y};
  enemy->mask_points[2] = {enemy->st.x + esat::SpriteWidth(AllSprites[0]), enemy->st.y + esat::SpriteHeight(AllSprites[0])};
  enemy->mask_points[3] = {enemy->st.x, enemy->st.y + esat::SpriteHeight(AllSprites[0])};
}

void setDirection(Enemy* alien){
  switch (alien->type){
    case fireball:
      alien->dir = {0, (float)(1-rand()%3)};
    break;
    case cross:
      
    break;
    case ship:
      
    break;
  }
}

void initEnemy(Enemy* enemy){
  esat::SpriteTransformInit(&enemy->st);
  enemy->st.y = rand()%(KWindow_Height-50) + 50;
  SetXinitPosition(enemy);
  enemy->mask_points = (esat::Vec2*)malloc(4 * sizeof(esat::Vec2));
  InitEnemyMask(enemy);
  enemy->type = fireball;
  setDirection(enemy);
}

void InitAllEnemies(){
  enemy = (Enemy*)malloc(4*sizeof(Enemy));
  for(int i = 0; i < 4; ++i)
    initEnemy(&enemy[i]);
}
void MoveEnemy(){
  for(int i = 0; i<nEnemy; i++){
    enemy[i].st.x += enemy[i].speed;
    enemy[i].st.y += enemy[i].speed * enemy[i].dir.y;
    InitEnemyMask(&enemy[i]);
  }
}

void DrawEnemy(){
  for(int i = 0; i < nEnemy; i++){
    esat::DrawSetFillColor(255,0,0);
    esat::DrawSolidPath(&enemy[i].mask_points->x, 4);
    esat::DrawSprite(AllSprites[AnimationSprite], enemy[i].st);
  }
}

void CheckBorders(){
  for(int i = 0; i< nEnemy; i++){
    //si sale de pantalla 
    if(enemy[i].st.x < (-5.0f - esat::SpriteWidth(AllSprites[0]))){
      enemy[i].st.x = KWindow_Width;
    }
    else if(enemy[i].st.x > KWindow_Width+5.0f){
      enemy[i].st.x = 0.0f - esat::SpriteWidth(AllSprites[0]);
    }
  }
}


int esat::main(int argc, char **argv) {

	esat::WindowInit(KWindow_Width, KWindow_Height);
	esat::WindowSetMouseVisibility(true);

	srand(time(NULL));
	last_time = esat::Time();
  LoadEnemySprite();
  InitAllEnemies();

  // Main game loop
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
    // Calculate time elapsed since the last frame
    current_time = esat::Time();
    delta_time = (current_time - last_time) / 1000.0;
    // Limit delta_time to avoid large jumps
    if (delta_time > 0.1) delta_time = 0.1;
    
    last_time = current_time;

    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    MoveEnemy();
    DrawEnemy();
    CheckBorders();

    // Finish drawing
    esat::DrawEnd();
    // Control frame speed (fps)
    do{
      current_time = esat::Time();
    }while((current_time - last_time) <= 1000.0/fps);
    AnimationSprite = !AnimationSprite;
    esat::WindowFrame();
  }

  // Destroy window
  esat::WindowDestroy();
  return 0;
}
