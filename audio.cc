#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>

#include <esat_extra/soloud/soloud.h>
#include <esat_extra/soloud/soloud_wav.h>

#include <stdio.h>

unsigned char fps=25;
double current_time,last_time;

enum audio{
  enemyDies,
  fallObject,
  getFuel,
  getItem,
  shoot,
  landing,
  start
};

enum backgroundAudio{
  intro,
  menu,
  inGame
};

SoLoud::Soloud soloud;    // Engine core
// necesitaremos mass que solo uno ya que mas de 1 audio en contemporanea
SoLoud::Wav sonido, back; // Como el spritehandle pero para sonido

void PlayAudio(audio selectAudio){
  // carga un file audio
  switch(selectAudio){
    case enemyDies: sonido.load("./assets/audio/enemydies.wav"); printf("0 ");  break;
    case fallObject:sonido.load("./assets/audio/fallobject.wav");  printf("1 ");break;
    case getFuel:   sonido.load("./assets/audio/get_fuel.wav");  printf("2 ");  break;
    case getItem:   sonido.load("./assets/audio/get_item.wav");  printf("3 ");  break;
    case shoot:     sonido.load("./assets/audio/shoot.wav");  printf("6 ");     break;
    case landing:   sonido.load("./assets/audio/startgameplay.wav");  printf("8 ");break;
    case start:     sonido.load("./assets/audio/shoot.wav");  printf("9 ");     break;
  }
  if(sonido.getLength() == 0.0){printf("no load");}
  printf(" %f ",sonido.getLength());
  soloud.play(sonido);    // play
}

// de esto no estoy seguro
void PlayBackgroundMusic(backgroundAudio selectAudio){
  switch (selectAudio)
  {
    case intro:
      back.load("./assets/audio/intro.wav");
    break;
    case menu: 
      back.load("./assets/audio/menu_intro.wav");
    break;
    case inGame:
      back.load("./assets/audio/spacedep1.wav"); 
    break;
  }
  // tengo que repasar la parte del loop
  back.setLooping(true);
  soloud.play(back);    // play
}


int esat::main(int argc, char **argv) {
  soloud.init();
  
	esat::WindowInit(800,600);
	WindowSetMouseVisibility(true);

  PlayBackgroundMusic(inGame);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
    
    last_time = esat::Time(); 
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
    
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Keypad_0)){
      PlayAudio(enemyDies);
    }
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Keypad_1)){
      PlayAudio(fallObject);
    }
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Keypad_2)){
      PlayAudio(getFuel);
    }
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Keypad_3)){
      PlayAudio(getItem);
    }
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Keypad_6)){
      PlayAudio(shoot);
    } 
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Keypad_8)){
      PlayAudio(landing);
    }    
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Keypad_9)){
      PlayAudio(start);
    }    
    
    esat::DrawEnd();
    
    //Control fps 
    do{
      current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    esat::WindowFrame();
  }
  soloud.deinit();
  esat::WindowDestroy();
  return 0;
}