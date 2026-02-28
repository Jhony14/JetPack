#include "level_config.h"

LevelConfig GetLevelConfig(int level)
{

    LevelConfig config;

    config.level_number = level;

    // Cada nivel aumenta enemigos
    config.enemies_to_spawn = 3 + level;

    // Cada 4 niveles cambia tipo enemigo
    int stage = (level - 1) / 2;

    switch (stage)
    {
    case 0:
        config.enemy_type = ENEMY_1;
        config.nave_sprite_set = 0;
        break;

    case 1:
        config.enemy_type = ENEMY_2;
        config.nave_sprite_set = 1;
        break;

    case 2:
        config.enemy_type = ENEMY_3;
        config.nave_sprite_set = 2;
        break;
    case 3:
        config.enemy_type = ENEMY_4;
        config.nave_sprite_set = 2;
        break;
    case 4:
        config.enemy_type = ENEMY_5;
        config.nave_sprite_set = 2;
        break;
    case 5:
        config.enemy_type = ENEMY_6;
        config.nave_sprite_set = 2;
        break;
    case 6:
        config.enemy_type = ENEMY_7;
        config.nave_sprite_set = 2;
        break;

    default:
        config.enemy_type = ENEMY_1;
        config.nave_sprite_set = 3;
        break;
    }

    return config;
}