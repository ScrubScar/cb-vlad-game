
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "debug-file.h"
#include "MapOne.h"
#include "engine.h"
using namespace std;

int main( int argc, char* args[] )
{
    bool quit = false;
    SDL_Event event;
    engine Game;
    if(Game.init(640, 480) == 1){
        return 1;
    }


    Uint8 *keystates = SDL_GetKeyState(NULL);
    while( quit == false ) {
           while( SDL_PollEvent( &event ) )
           {
                  if( event.type == SDL_QUIT )
                  {
                      quit = true;
                      }

                   if( keystates[SDLK_ESCAPE])
                   {
                       quit = true;
                       }
                  }

                  Game.heartBeat(event);
           }
    system("start debug.txt");
    return 0;
}


