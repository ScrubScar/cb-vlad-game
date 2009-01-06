
class menu
{
      public:
             menu();
             virtual ~menu();

             void main_init( SDL_Surface *main_screen );
             virtual void init();
             virtual void show_menu(int player_hitpoints);
             SDL_Surface * surface_from_integer( int integer_conversion_source );

      protected:
              SDL_Surface *screen;
              imageLoad image_loader;
              char character_conversion_buffer[20];
              SDL_Surface *surface_conversion_buffer;

              TTF_Font *font;
};

menu::menu()
{
;
}

menu::~menu()
{
             ;
}

void menu::init()
{
     ;
     }

void menu::main_init( SDL_Surface *main_screen )
{
     font = TTF_OpenFont( "ACTIVA.TTF", 10 );
     screen = main_screen;
     init();
}

void menu::show_menu(int player_hitpoints)
{
  ;
}

SDL_Surface * menu::surface_from_integer( int integer_conversion_source )
{
    SDL_Color textColor = { 255, 255, 0 };
    itoa( integer_conversion_source, character_conversion_buffer, 10);
    surface_conversion_buffer = TTF_RenderText_Solid( font, character_conversion_buffer, textColor);
    return surface_conversion_buffer;
}
