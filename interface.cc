
enum TScreen {
  MAIN_MENU,
  GAME_SCREEN
};

void LoadFonts(){
  // printf("[DEBUG] call LoadFonts\n");
  esat::DrawSetTextFont("assets/fonts/zx_spectrum-7.ttf");
}

// TODO: fix color bg
void MainMenu(){
  // printf("[DEBUG] call MainMenu\n");
  DrawHeader();

  esat::DrawSetTextSize(20);
  esat::DrawText(60, 70, "JETPAC GAME SELECTION");

  esat::DrawText(60, 110, "1  1 PLAYER GAME");
  esat::DrawText(60, 140, "2  2 PLAYER GAME");
  esat::DrawText(60, 170, "3  KEYBOARD");
  esat::DrawText(60, 200, "4  KEMPSTON JOYSTICK"); // not selectable

  esat::DrawText(60, 250, "5  START GAME");
  
  esat::DrawText(10, 350, "@1983 A.C.G. ALL RIGHTS RESERVED");
}

// Test sprites
void GameScreen(){

}

// function to select the screen to show
void ScreenSelector(TScreen current_screen){
  switch (current_screen){
    case MAIN_MENU:
      // printf("[DEBUG] Main menu selected\n");
      MainMenu();
      break;
    case GAME_SCREEN:
      GameScreen();
      break;
    default:
      printf("[DEBUG] not screen\n");
      break;
  }  
}

void TestMousePosition(){
  if(esat::MouseButtonDown(0))
    printf("[DEBUG] Mouse position: %f, %f\n", (float) esat::MousePositionX(), (float) esat::MousePositionY());
}


