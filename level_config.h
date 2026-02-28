#ifndef LEVEL_SYSTEM_H
#define LEVEL_SYSTEM_H

#include "enemigos.h"
#include "nave.h"

enum EnemyType
{
    ENEMY_1,
    ENEMY_2,
    ENEMY_3,
    ENEMY_4,
    ENEMY_5,
    ENEMY_6,
    ENEMY_7
};

struct LevelConfig
{
    int level_number;
    int enemies_to_spawn;
    EnemyType enemy_type;
    int nave_sprite_set;
};

LevelConfig GetLevelConfig(int level);

#endif