#ifndef DATA_H
#define DATA_H

#include <cstdio>
#include "jugador.h"

// Guarda uno o dos jugadores en el archivo
void SavePlayerDataToFile(Jugador *player1, Jugador *player2 = nullptr);

// Carga datos de un jugador concreto según su player_id
void LoadPlayerDataFromFile(Jugador *player, int player_id = 1);

// Borra el archivo de guardado
void DeletePlayerDataFiles();

#endif