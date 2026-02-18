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
// #include "colisiones.cc"
#define spritewidth 34
#define spriteheight 50
#define windowX 800
#define windowY 800

// FPS
double delta_time;
unsigned char fps = 25;
double current_time;
double last_time;
struct Sprites
{
  esat::SpriteHandle sprite;
};

struct Jugador
{
  esat::Vec2 pos;
  esat::Vec2 dir;
  float speed;
  bool isMoving;
  bool isShooting;
  bool mirandoDerecha;
  bool volando;
  // object config_colision;
};
struct Bala
{
  esat::Vec2 pos;
  esat::Vec2 dir;
  float speed;
  bool activa;
  float tiempo_vida;
};

Sprites *AsignarMemoriaSprites(int cantidad)
{
  return (Sprites *)malloc(cantidad * sizeof(Sprites));
}
Bala *AsignarMemoriaBalas(int cantidad)
{
  return (Bala *)malloc(cantidad * sizeof(Bala));
}
// ________________________________
// INSTANCIAR
// ________________________________

void InstanciarSpritesColores(Sprites *punteroSprites)
{
  punteroSprites[0].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/amarillo1.png");
  punteroSprites[1].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/rojo1.png");
  punteroSprites[2].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/azul1.png");
  punteroSprites[3].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/verde1.png");
}
void InstanciarSpritesPlayer(Sprites *punteroSprites)
{
  // suelo
  punteroSprites[0].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player1right.png");
  punteroSprites[1].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player2right.png");
  punteroSprites[2].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player3right.png");
  punteroSprites[3].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player4right.png");
  punteroSprites[4].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player1.png");
  punteroSprites[5].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player2.png");
  punteroSprites[6].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player3.png");
  punteroSprites[7].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/player4.png");
  // aire
  punteroSprites[8].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/right1.png");
  punteroSprites[9].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/right2.png");
  punteroSprites[10].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/right3.png");
  punteroSprites[11].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/right4.png");
  punteroSprites[12].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/left1.png");
  punteroSprites[13].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/left2.png");
  punteroSprites[14].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/left3.png");
  punteroSprites[15].sprite = esat::SpriteFromFile("SPRITES/JUGADOR/left4.png");
}

void InstanciarPlayer(Jugador *player)
{
  player->pos.x = windowX / 2;
  player->pos.y = windowY - spriteheight;
  player->dir = {0, 0};
  player->isMoving = false;
  player->isShooting = false;
  player->volando = false;
  player->speed = 5.0f;
  player->mirandoDerecha = true;
}

void InstanciarBalas(Bala *bala)
{
  for (int i = 0; i < 20; i++)
  {
    bala[i].activa = false;
  }
}
// ________________________________
// BALAS
// ________________________________

void CrearDisparos(Bala *bala, Jugador player)
{
  if (esat::IsSpecialKeyDown(esat::kSpecialKey_Space))
  {
    for (int i = 0; i < 20; i++)
    {
      if (!bala[i].activa)
      {
        bala[i].activa = true;
        bala[i].pos.x = player.pos.x + (spritewidth / 2);
        bala[i].pos.y = player.pos.y + (spriteheight / 2);
        bala[i].speed = 16.0f;
        bala[i].tiempo_vida = 0.0f;
        if (player.mirandoDerecha)
          bala[i].dir = {1, 0};
        else
        {
          bala[i].dir = {-1, 0};
          bala[i].pos.x = player.pos.x - (spritewidth / 2);
        }
        break;
      }
    }
  }
}

void ActualizarDisparos(Bala *bala, Jugador player)
{
  float duracion_bala = 3.0f;

  for (int i = 0; i < 20; i++)
  {
    if (bala[i].activa)
    {
      bala[i].pos.x += bala[i].dir.x * bala[i].speed;
      //! si sale de pantalla (funcion carlos)

      bala[i].tiempo_vida += delta_time;
      if (bala[i].tiempo_vida >= duracion_bala)
      {
        bala[i].activa = false;
      }
    }
  }
}

void DibujarDisparos(Bala *bala)
{
  for (int i = 0; i < 20; i++)
  {
    if (bala[i].activa)
    {
      float balas[8] = {bala[i].pos.x, bala[i].pos.y, bala[i].pos.x + 50, bala[i].pos.y, bala[i].pos.x + 50, bala[i].pos.y + 2, bala[i].pos.x, bala[i].pos.y + 2};
      esat::DrawSetFillColor(255, 255, 255);
      esat::DrawSolidPath(balas, 4);
    }
  }
}

// ________________________________
// DIBUJADO
// ________________________________

void DibujarColoresJugador(Sprites *punteroSprites, Jugador jugador)
{
  static int frame_actual = 0;
  static float timer = 0.0f;
  float frame_time = 0.15f;

  timer += delta_time;
  if (timer >= frame_time)
  {
    timer = 0.0f;
    frame_actual = (frame_actual + 1) % 4;
  }
  esat::DrawSprite(punteroSprites[frame_actual].sprite, jugador.pos.x, jugador.pos.y);
}

void DibujarJugador(Sprites *punteroSprites, Jugador jugador)
{
  static int frame_local = 0;
  static float timer = 0.0f;
  float frame_time = 0.15f;

  timer += delta_time;

  if (timer >= frame_time && jugador.isMoving)
  {
    timer = 0.0f;
    frame_local = (frame_local + 1) % 4;
  }
  else if (!jugador.isMoving)
  {
    frame_local = 0;
  }

  int base = 0;
  if (!jugador.volando)
  {
    // SUELO
    base = jugador.mirandoDerecha ? 0 : 4;
  }
  else
  {
    // AIRE
    base = jugador.mirandoDerecha ? 8 : 12;
  }
  esat::DrawSprite(punteroSprites[base + frame_local].sprite, jugador.pos.x, jugador.pos.y);
}

//_____________________________
// LIMITES PANTALLA
//______________________________
void ControlarLimitesPantalla(Jugador *player, Bala *bala)
{
  //! (funcion carlos)
  if (player->pos.x > windowX)
    player->pos.x = -spritewidth;
  if (player->pos.x < -spritewidth)
    player->pos.x = windowX;
  if (player->pos.y >= windowY - spriteheight)
    player->pos.y = 0;
  if (player->pos.y <= 0)
    player->pos.y = windowY - spriteheight;

  for (int i = 0; i < 20; i++)
  {
    if (bala[i].pos.x > windowX)
      bala[i].pos.x = -50;
    if (bala[i].pos.x < -50) // lo que mida la bala, en este caso 50
      bala[i].pos.x = windowX;
  }
}
//_____________________________
// JUGADOR
//______________________________

void MoverJugador(Jugador *jugador, bool moverLeft, bool moverRight)
{
  if (!jugador->isMoving)
    return;
  if (moverLeft)
  {
    jugador->isMoving = true;
    jugador->pos.x -= jugador->speed;
  }
  if (moverRight)
  {
    jugador->isMoving = true;
    jugador->pos.x += jugador->speed;
  }
}
void Ascender_Gravedad(Jugador *jugador, bool ascendiendo)
{
  float suelo = windowY - spriteheight;
  if (ascendiendo)
    jugador->pos.y -= jugador->speed;
  else
    jugador->pos.y += jugador->speed;

  if (jugador->pos.y >= suelo)
  {
    jugador->pos.y = suelo;
    jugador->volando = false;
  }
  else
  {
    jugador->volando = true;
  }
}

int esat::main(int argc, char **argv)
{
  esat::WindowInit(windowX, windowY);
  esat::WindowSetMouseVisibility(true);

  srand((unsigned)time(nullptr));
  last_time = esat::Time();

  // puntero a sprites
  Sprites *spritesColores = AsignarMemoriaSprites(4);
  Sprites *spritesPersonaje = AsignarMemoriaSprites(16);
  Bala *punteroBalas = AsignarMemoriaBalas(20);
  InstanciarSpritesColores(spritesColores);
  InstanciarSpritesPlayer(spritesPersonaje);
  InstanciarBalas(punteroBalas);

  Jugador player;
  InstanciarPlayer(&player);

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

    bool moverLeft = (esat::IsKeyPressed('A') || esat::IsKeyPressed('a'));
    bool moverRight = (esat::IsKeyPressed('D') || esat::IsKeyPressed('d'));
    bool ascender = (esat::IsKeyPressed('W') || esat::IsKeyPressed('w'));
    Ascender_Gravedad(&player, ascender);
    ControlarLimitesPantalla(&player, punteroBalas);
    CrearDisparos(punteroBalas, player);
    ActualizarDisparos(punteroBalas, player);
    if (moverLeft || moverRight)
    {
      player.isMoving = true;
      MoverJugador(&player, moverLeft, moverRight);
      if (moverLeft)
        player.mirandoDerecha = false;
      else
        player.mirandoDerecha = true;
    }
    else
      player.isMoving = false;

    DibujarColoresJugador(spritesColores, player);
    DibujarJugador(spritesPersonaje, player);
    DibujarDisparos(punteroBalas);

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
