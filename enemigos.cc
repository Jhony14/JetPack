// ESAT Libraries
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Group Libraries
#include "colisiones.h"


int esat::main(int argc, char **argv)
{

    esat::WindowInit(800, 800);
    WindowSetMouseVisibility(true);

    //////////////////////////////

    /////////////////////////////

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape))
    {

        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);

        ////////////////////////////////

        ////////////////////////////////

        esat::DrawEnd();
        esat::WindowFrame();
    }

    /////////////////////////

    /////////////////////////

    esat::WindowDestroy();

    return 0;
}