#ifndef AUDIO_H
#define AUDIO_H

enum audio
{
    enemyDies,
    fallObject,
    getFuel,
    getItem,
    shoot,
    landing,
    start,
    intro,
    menu,
    launch
};

void AudioInit();
void FreeAudio();
void PlayAudio(audio selectAudio);

#endif