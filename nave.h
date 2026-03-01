#ifndef NAVE_H
#define NAVE_H

#include <esat/sprite.h>
#include <esat/draw.h>
#include "colisiones.h"

struct Jugador; // forward declaration

enum Direction
{
    UP,
    DOWN,
    STATIC
};

struct Nave
{
    float vel;
    esat::Vec2 pos;
    Direction direccion;
    int height;
    int fuelAmount;
    COL::object nave_config;
};

struct Sprites
{
    esat::SpriteHandle sprite;
};

struct ParteNave
{
    esat::Vec2 pos;
    COL::object parteNaveConfig;
    bool colocada;
    bool recogido;
    bool colisionNave;
};

// --- Nave ---
// Sprites *InstanciarSpritesNave(int numSprite);
void InitSpriteNave(Sprites *punteroSprites);
void InstanciarNave(Nave *nave);
void MoverNave(Nave *nave, COL::object P, bool *visible, int* vidas);
bool NaveEstaArriba(Nave *nave);
void RellenarFuelNave(Nave *nave);
void DibujarNave(Nave *nave, Sprites *punteroSprites, ParteNave *punteroParteNave);

// --- Partes nave ---
void InstanciarPartesDeLaNave(ParteNave *parteNave);
void ActualizarColisionParteNave(ParteNave *parteNave);
void MoverParte(ParteNave *parteNave, Nave *nave);
void ColisionColocarPartes(Nave *nave, ParteNave *parte_nave, Jugador *player);
void ActualizarPosParteNave(ParteNave *parteNave, Jugador *player);
void ColisionPartesNaveJugador(ParteNave *parteNave, Jugador *player);
void DibujarPartesNave(ParteNave *parteNave, Sprites *punteroSprites);

#endif