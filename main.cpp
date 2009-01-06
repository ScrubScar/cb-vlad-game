
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "MapOne.h"
#include "engine.h"

// git test to see how it changes files
using namespace std;

int main( int argc, char* args[] )
{
    bool quit = false;
    SDL_Event event;
    engine Game;
    Game.init(640, 480);


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
    return 0;
}


