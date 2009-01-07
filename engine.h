
#include <cstdlib>
#include <ctime>
#include "imageLoad.h"
#include "menu.h"
#include "player_status - menu.h"
#include "statusChange.h"
#include "collisionCheck.h"
#include "LoadMap.h"
#include "camera.h"
#include "particles.h"
#include "smoke-particles.h"
#include "glitter-particles.h"
#include "items.h"
#include "ncp.h"
#include "NcpBehemoth.h"
#include "missle.h"
#include "player.h"

class engine
{
      public:
             engine();
             ~engine();

             int heartBeat(SDL_Event event);

             void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
             int init(const int screen_width, const int screen_height);
             void load_map();
             void draw_player_menus();
             void place_ncps();

             SDL_Surface *levelSurface;

      private:
              int SCREEN_WIDTH;
              int SCREEN_HEIGHT;
              int SCREEN_BPP;
              int LEVEL_WIDTH;
              int LEVEL_HEIGHT;

              int ticks;
              int startTick;
              int fps;

              TTF_Font * font;

              SDL_Surface *playerSurface;
              SDL_Surface *screen;

              SDL_Surface *swift_buffer;
              SDL_Surface *ncp_hitpoints_display;



              SDL_Rect levelRect;
              SDL_Rect object_local;

              items healthItems;
              status_change status_code;
              player player_one;
              NCP *generic_ncp[2];
              imageLoad allImageLoad;
              collision check_collision;
              smoke testParticle;
              map_load map_loader;
              camera main_camera;
              player_status_menu main_player_frame;

              debug engine_debug;
              };

engine::engine()
{
   engine_debug.debug_file_init();
   engine_debug.write_to_file("engine constructor started.");
   SCREEN_WIDTH = 650;
   SCREEN_HEIGHT = 480;
   SCREEN_BPP = 32;

   LEVEL_WIDTH = 3200;
   LEVEL_HEIGHT = 1200;

   fps = SDL_GetTicks();

   player_one = player(0, 0, 1);
   generic_ncp[0] = new Behemoth(480, 315);
   generic_ncp[1] = new Behemoth(936, 390);
   playerSurface = NULL;
   swift_buffer = NULL;
   screen = NULL;
   levelSurface = NULL;

   if( SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
       engine_debug.write_to_file("!--SDL failed to initialize.");
       }
   else
       engine_debug.write_to_file("SDL sucessfully initialized.");

   engine_debug.write_to_file("engine constructor finished.");
}

engine::~engine()
{
   delete(generic_ncp);
   TTF_Quit();
   SDL_Quit();
      }


int engine::init( const int screen_width, const int screen_height )
{
     engine_debug.write_to_file("engine.init() started");
     startTick = SDL_GetTicks();

     if( TTF_Init() == -1 ){
         engine_debug.write_to_file("!--TTF_Init() error.");
         }

     font = TTF_OpenFont( "ACTIVA.TTF", 10 );
     if( font == NULL ){
         engine_debug.write_to_file("TTF_OpenFont() error");
         exit(1);
         }

     levelSurface = SDL_LoadBMP("sprites/buffer.bmp");

     if(levelSurface == NULL){
         engine_debug.write_to_file("!--SDL_LoadBMP() *levelSurface* failed to create.");
         system("start debug.txt");
         exit(1);
         }
     screen = SDL_SetVideoMode( screen_width, screen_height, 32, SDL_HWSURFACE);

     if( screen == NULL){
         engine_debug.write_to_file("!--SDL_SetVideoMode() *screen* failed to create.");
         exit(1);
         }

     swift_buffer = allImageLoad.load_image("sprites/buff.gif");

     main_camera.init(LEVEL_WIDTH, LEVEL_HEIGHT, screen_width, screen_height);

     main_player_frame.main_init(screen);

     testParticle.main_init(100, 100, levelSurface);

     map_loader.init(levelSurface);

     player_one.playerInit();
     generic_ncp[0]->ncpInit();
     generic_ncp[1]->ncpInit();

     healthItems.item_init(200, 200, levelSurface);

     generic_ncp[0]->setScreenSurface(levelSurface);
     generic_ncp[1]->setScreenSurface(levelSurface);

     player_one.setScreenSurface(levelSurface);
     engine_debug.write_to_file("engine.init() finished ");
     return 0;
     }



void engine::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
     SDL_Rect offset;
     offset.x = x;
     offset.y = y;
     if(SDL_BlitSurface( source, NULL, destination, &offset ) == -1){
         engine_debug.write_to_file("!--SDL_BlitSurface() error");
         }
     }



int engine::heartBeat(SDL_Event event)
{
     load_map();

     for( int i = 0; i < 2 ; i++){
         if(generic_ncp[i]->isDeathItemPickedUp() == false){
            generic_ncp[i]->pulse(player_one.get_player_rect(), status_code ) ;
            player_one.player_state_change( status_code );
            }
         }

     if( healthItems.player_has_not_attained_item() ) {
         testParticle.show_particles(200, 200);
         healthItems.show_item(player_one.get_player_rect(), status_code);
         }


     player_one.player_state_change( status_code );
     player_one.pulse(event, generic_ncp);
     main_camera.update_camera(player_one.get_player_rect());

     if( SDL_Flip( screen ) < 0 ) {
         engine_debug.write_to_file("!--SDL_Flip() error");
         }


     if(   (SDL_GetTicks() - startTick) < ( 1000 / 25)   ){
            SDL_Delay( ( 1000 / 25) - (SDL_GetTicks() - startTick) );
        }

     startTick = SDL_GetTicks();
     return 0;
     }



void engine::load_map()
{
    map_loader.load_map();
    if( SDL_BlitSurface(levelSurface, &main_camera.get_camera_rect(), screen, NULL) < 0){
        engine_debug.write_to_file("!--Error SDL_BlitSurface(levelSurface, screen)");
        }

    apply_surface(main_camera.get_camera_x(), main_camera.get_camera_y(), swift_buffer, levelSurface);
    place_ncps();
    draw_player_menus();
}


void engine::draw_player_menus()
{
    main_player_frame.show_menu(player_one.get_player_hitpoints());
}


void engine::place_ncps()
{
     SDL_Color textColor = { 255, 255, 255 };

     for(int i = 0; i < 2; i++){
        if(generic_ncp[i]->isNcpAlive() == true){
            char ncp_hitpoints[10];
            itoa(generic_ncp[i]->get_ncp_hitpoints(), ncp_hitpoints, 10);
            ncp_hitpoints_display = TTF_RenderText_Solid( font, ncp_hitpoints, textColor);
            apply_surface(generic_ncp[i]->get_ncp_x(), generic_ncp[i]->get_ncp_y(), ncp_hitpoints_display, levelSurface);
            }
        }
}
