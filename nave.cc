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

esat::SpriteHandle nave1, nave2, nave3;
esat::SpriteHandle rosa;

int g_pink_x, g_pink_y;
int g_head_x = 600, g_head_y = 704;
int g_body_x = 600, g_body_y = 736;
int g_tail_x = 600, g_tail_y = 768;
int g_speed = 2;


void CargarSprites(){
    nave1 = esat::SpriteFromFile("./SPRITES/NAVE/cabeza_nave_1_2x.png");
    nave2 = esat::SpriteFromFile("./SPRITES/NAVE/cuerpo_nave_1_2x.png");
    nave3 = esat::SpriteFromFile("./SPRITES/NAVE/cola_nave_1_2x.png");
    rosa = esat::SpriteFromFile("rosa.png");
}
void Dibujar(){
    esat::DrawSprite(rosa, g_head_x, g_head_y);
    esat::DrawSprite(nave1, g_head_x, g_head_y);

    esat::DrawSprite(rosa, g_body_x, g_body_y);
    esat::DrawSprite(nave2, g_body_x, g_body_y);

    esat::DrawSprite(rosa, g_tail_x, g_tail_y);
    esat::DrawSprite(nave3, g_tail_x, g_tail_y);

}
void MoverNave(){
  if(esat::IsKeyDown ('P')){
    while (g_head_y != 100)
    {
          g_head_y -= g_speed;
          g_body_y -= g_speed;
          g_tail_y -= g_speed;
    }
    

  }



}
void Liberar(){
    esat::SpriteRelease(nave1);
    esat::SpriteRelease(nave2);
    esat::SpriteRelease(nave2);
    esat::SpriteRelease(rosa);
}
int esat::main(int argc, char **argv) {

	esat::WindowInit(KWindow_Width, KWindow_Height);
	esat::WindowSetMouseVisibility(true);
    CargarSprites();
	srand((unsigned)time(nullptr));
	last_time = esat::Time();

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

    Dibujar();
    MoverNave();

    // Finish drawing
    esat::DrawEnd();
    // Control frame speed (fps)
    do{
      current_time = esat::Time();
    }while((current_time - last_time) <= 1000.0/fps);
    esat::WindowFrame();
  }
    
  // Destroy window
  Liberar();
  esat::WindowDestroy();
  return 0;
}
