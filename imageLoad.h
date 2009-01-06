#include <string>
using namespace std;
class imageLoad
{
      public:
             imageLoad();
             ~imageLoad();

             SDL_Surface * load_image(string filename);
             void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination );

      private:
                SDL_Surface* loadedImage ;
                SDL_Surface* optimizedImage;
             };

imageLoad::imageLoad()
{
    loadedImage = NULL;
    optimizedImage = NULL;
}

imageLoad::~imageLoad()
{
    loadedImage = NULL;
    optimizedImage = NULL;
}

SDL_Surface * imageLoad::load_image(std::string filename)
{
   loadedImage = IMG_Load( filename.c_str() );
    if( loadedImage != NULL )
    {
         optimizedImage = SDL_DisplayFormat( loadedImage );
         SDL_FreeSurface( loadedImage );
         }
    return optimizedImage;
}

void imageLoad::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
     SDL_Rect offset;
     offset.x = x;
     offset.y = y;
     SDL_BlitSurface( source, NULL, destination, &offset );
}

