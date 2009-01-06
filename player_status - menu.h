
class player_status_menu : public menu
{
      public:
          player_status_menu();
          virtual ~player_status_menu();

          void init();
          void show_menu(int player_hitpoints);

      private:
              SDL_Surface *statusFrame;
              SDL_Surface *healthBar;
              SDL_Surface *manaBar;

              SDL_Rect statusFrameRect;
              SDL_Rect hitpointTextRect;
              SDL_Rect healthBarRect;
              SDL_Rect healthBarPosition;

              int frame_position_x;
              int frame_position_y;
};

player_status_menu::player_status_menu()
{
       ;
}

player_status_menu::~player_status_menu()
{
       ;
}

void player_status_menu::init()
{
     statusFrame = image_loader.load_image("sprites/statusBarBg.gif");
     healthBar = image_loader.load_image("sprites/healthGauge.gif");
     manaBar = image_loader.load_image("sprites/manaGauge.gif");

     statusFrameRect.x = 0;
     statusFrameRect.y = 0;
     hitpointTextRect.x = 0;
     hitpointTextRect.y = 0;

     healthBarPosition.x = 50;
     healthBarPosition.y = 10;

     healthBarRect.x = 0;
     healthBarRect.y = 0;
     healthBarRect.w = 10;
     healthBarRect.h = 8;
}

void player_status_menu::show_menu(int player_hitpoints)
{
    healthBarRect.w = player_hitpoints;
    SDL_BlitSurface(statusFrame, NULL, screen, &statusFrameRect );
    SDL_BlitSurface(healthBar, &healthBarRect, screen, &healthBarPosition);
    image_loader.apply_surface( 95, 8, surface_from_integer(player_hitpoints), screen);
}
