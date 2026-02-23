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
#include "colisiones.h"
//#include "jugador.cc"

// Windows dimensions with default values
const int KWindow_Width = 800;
const int KWindow_Height = 800;

// FPS
double delta_time;
unsigned char fps = 25;
double current_time;
double last_time;

enum Direction
{
  UP,
  DOWN,
  STATIC
};

struct Sprites
{
  esat::SpriteHandle sprite;
};

struct Nave
{
  float vel;
  esat::Vec2 pos;
  Direction direccion;
  int height = 32, fuelAmount;
  //COL::object nave_config;
};


struct ParteNave{
  esat::Vec2 pos;
  COL::object parteNaveConfig;
};

struct point{
    float x, y;
};

struct shape{
    point *vert = nullptr;
    int num_point = 5; 
};

shape *base = nullptr, *plataforma1 = nullptr, *plataforma2 = nullptr;

void FormarPlataformas(float posX, float posY, float width, point *vert){
    vert = (point*) malloc(sizeof(point)*4);

    vert->x = posX;
    vert->y = posY;

    (vert+1)->x = posX + width;
    (vert+1)->y = posY;

    (vert+2)->x = posX + width;
    (vert+2)->y = posY + (width/4);

    (vert+3)->x = posX;
    (vert+3)->y = posY + (width/4);

    esat::DrawSolidPath(&(vert->x), 4, true);
}

Sprites *InstanciarSpritesNave(int numSprite)
{
  return (Sprites *)malloc(sizeof(Sprites) * numSprite);
}

void InitSpriteNave(Sprites *punteroSprites)
{
  punteroSprites[0].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cabeza_nave_1_2x.png");
  punteroSprites[1].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cuerpo_nave_1_2x.png");
  punteroSprites[2].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cola_nave_1_2x.png");
  punteroSprites[3].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cabeza_nave_2_2x.png");
  punteroSprites[4].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cuerpo_nave_2_2x.png");
  punteroSprites[5].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cola_nave_2_2x.png");
  punteroSprites[6].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cabeza_nave_3_2x.png");
  punteroSprites[7].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cuerpo_nave_3_2x.png");
  punteroSprites[8].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cola_nave_3_2x.png");
  punteroSprites[9].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cabeza_nave_4_2x.png");
  punteroSprites[10].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cuerpo_nave_4_2x.png");
  punteroSprites[11].sprite = esat::SpriteFromFile("./SPRITES/NAVE/cola_nave_4_2x.png");
  punteroSprites[12].sprite = esat::SpriteFromFile("./SPRITES/NAVE/fondo_blanco.png");
  punteroSprites[13].sprite = esat::SpriteFromFile("./SPRITES/NAVE/fondo_rosa.png");
  punteroSprites[14].sprite = esat::SpriteFromFile("./SPRITES/NAVE/explosion_1_2x.png");
  punteroSprites[15].sprite = esat::SpriteFromFile("./SPRITES/NAVE/explosion_2_2x.png");
}

// void InstanciarNave(Nave *nave)
// {
//   const int terrain_height = 16;
//   nave->vel = 100;
//   nave->pos.x = KWindow_Width / 2;
//   nave->pos.y = KWindow_Height - (nave->height * 3) - terrain_height;
//   nave->fuelAmount = 0;
//   nave->direccion = Direction::STATIC;
// }

void InstanciarPartesDeLaNave(ParteNave *parteNave){
    ParteNave cabeza;
    cabeza.parteNaveConfig.width = 130;
    cabeza.parteNaveConfig.height = 418;
    parteNave[0] = cabeza;

    ParteNave cuerpo;
    cuerpo.parteNaveConfig.width = 330;
    cuerpo.parteNaveConfig.height = 498;
    parteNave[1] = cuerpo;

    ParteNave cola;
    cola.parteNaveConfig.width = KWindow_Width / 2;
    cola.parteNaveConfig.height = KWindow_Height-48;
    parteNave[2] = cola;
}

void DibujarNave(ParteNave *parteNave, Sprites *punteroSprites){
    int height = 32;

    for(int i=0; i<3; i++){
        esat::DrawSprite(punteroSprites[12].sprite, parteNave[i].parteNaveConfig.width, parteNave[i].parteNaveConfig.height);
    }

    for(int i=0; i<3; i++){
        esat::DrawSprite(punteroSprites[i].sprite, parteNave[i].parteNaveConfig.width, parteNave[i].parteNaveConfig.height);
    }
}

void MoverNave(Nave *nave)
{
    const int terrain_height = 16;
    if(nave->fuelAmount == 6) nave->direccion = Direction::UP;
    switch (nave->direccion){
        case Direction::UP:
            nave->pos.y -= nave->vel * delta_time;
            if(nave->pos.y + nave->height * 2 <= nave->height){
                nave->direccion = Direction::DOWN; 
                nave->fuelAmount = 0;
            }
            break;
        
        case Direction::DOWN:
            nave->pos.y += nave->vel * delta_time;
            if(nave->pos.y + nave->height * 3 >= KWindow_Height - terrain_height){
                nave->pos.y = KWindow_Height - terrain_height - nave->height * 3;
                nave->direccion = Direction::STATIC;
            }
            break;
    }
    
}

void RellenarFuelNave(Nave *nave)
{
    // Detecta colision y player tiene fuel
    if(esat::IsKeyDown('B') || esat::IsKeyDown('b'))
        if(nave->fuelAmount <= 6) nave->fuelAmount++;
}

void FillVec2PtrPoints(esat::Vec2* explosion_path, Nave nave, int explosion_size){
    explosion_path[0] = {nave.pos.x, nave.pos.y + nave.height * 3};
    explosion_path[1] = {nave.pos.x + explosion_size, nave.pos.y + nave.height * 3};
    explosion_path[2] = {nave.pos.x + explosion_size, nave.pos.y + nave.height * 3 + explosion_size};
    explosion_path[3] = {nave.pos.x, nave.pos.y + nave.height * 3 + explosion_size};
}

// void DibujarNave(Nave *nave, Sprites *punteroSprites)
// {
//     const int terrain_height = 16, pink_sprite_height = 16, max_sprites = 6, explosion_size = 32, rocket_total_height = nave->height * 3;
    
//     //Blanco
//     for(int i = 0; i < 3; i++)
//         esat::DrawSprite(punteroSprites[12].sprite, nave->pos.x, nave->pos.y + nave->height * i);

//     //Rosa
//     for(int i = 0; i < nave->fuelAmount; i++){
//         int initFuelY = nave->pos.y + rocket_total_height - pink_sprite_height;
//         esat::DrawSprite(punteroSprites[13].sprite, nave->pos.x, initFuelY - (i * pink_sprite_height));
//     }

//     //Nave
//     for(int i = 0; i < 3; i++)
//         esat::DrawSprite(punteroSprites[i].sprite, nave->pos.x, nave->pos.y + nave->height * i);

//     if(KWindow_Height - terrain_height - nave->pos.y + rocket_total_height >= explosion_size){
//         esat::Vec2* explosion_path = (esat::Vec2*)malloc(4 * sizeof(esat::Vec2));
//         FillVec2PtrPoints(explosion_path, *nave, explosion_size);
//         esat::DrawSetFillColor(255,0,0);
//         esat::DrawSolidPath(&explosion_path->x, 4);
//         esat::DrawSprite(punteroSprites[14].sprite, explosion_path->x, explosion_path->y);
//     }
// }

int esat::main(int argc, char **argv){

  esat::WindowInit(KWindow_Width, KWindow_Height);
  esat::WindowSetMouseVisibility(true);

  srand((unsigned)time(nullptr));
  last_time = esat::Time();

  Sprites *punteroSprites = InstanciarSpritesNave(16);
  InitSpriteNave(punteroSprites);

  Nave *nave;

  ParteNave *parteNave;
  parteNave = (ParteNave*) malloc(sizeof(ParteNave)*3);
  //InstanciarNave(&nave);

  InstanciarPartesDeLaNave(parteNave);

  base = (shape*) malloc(sizeof(shape));
  plataforma1 = (shape*) malloc(sizeof(shape));
  plataforma2 = (shape*) malloc(sizeof(shape));

  // Main game loop
  while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape))
  {

    // Calculate time elapsed since the last frame
    current_time = esat::Time();
    delta_time = (current_time - last_time) / 1000.0;
    // Limit delta_time to avoid large jumps
    if (delta_time > 0.1)
      delta_time = 0.1;

    last_time = current_time;

    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);
    esat::DrawSetStrokeColor(255, 255, 0, 255);
    esat::DrawSetFillColor(255, 255, 0, 255);

    FormarPlataformas(0, KWindow_Height-16, KWindow_Width, base->vert);
    FormarPlataformas(100, KWindow_Height-350, 100, plataforma1->vert);
    FormarPlataformas(300, KWindow_Height-270, 100, plataforma2->vert);

    DibujarNave(parteNave, punteroSprites);

    // InitFuel(&nave, punteroSprites);
    //RellenarFuelNave(&nave);
    //MoverNave(&nave);
    //DibujarNave(&nave, punteroSprites);

    // Finish drawing
    esat::DrawEnd();
    // Control frame speed (fps)
    do
    {
      current_time = esat::Time();
    } while ((current_time - last_time) <= 1000.0 / fps);
    esat::WindowFrame();
  }

  // Destroy window
  esat::WindowDestroy();
  return 0;
}
