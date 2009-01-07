
class particles
{
      public:
             particles();
             virtual ~particles();

             virtual void init_particles(int x, int y);
             void main_init(int x, int y, SDL_Surface* levelSurface);
             void show_particles(int x, int y);
             virtual void move_particles(int x, int y);
             void start_particles();
             void blit_particles();


      protected:
              SDL_Rect particleRect[10];
              SDL_Rect clippingRect;

              SDL_Surface *colorParticles;
              SDL_Surface *blackWhiteParticles;
              SDL_Surface *level_surface;

              int moveHeight[10];
              bool particleStarted[10];

              imageLoad imageLoader;

};

particles::particles()
{
    for(int i = 0; i < 10; i++){
            particleRect[i].x = 0;
            particleRect[i].y = 0;
            particleRect[i].w = 0;
            particleRect[i].h = 0;

            clippingRect.x = 0;
            clippingRect.y = 0;
            clippingRect.w = 0;
            clippingRect.h = 0;

            moveHeight[i] = 0;
            particleStarted[i] = false;
            }

    colorParticles = NULL;
    blackWhiteParticles = NULL;
    level_surface = NULL;
}

particles::~particles()
{
    for(int i = 0; i < 10; i++){
            particleRect[i].x = 0;
            particleRect[i].y = 0;
            particleRect[i].w = 0;
            particleRect[i].h = 0;

            clippingRect.x = 0;
            clippingRect.y = 0;
            clippingRect.w = 0;
            clippingRect.h = 0;

            moveHeight[i] = 0;
            particleStarted[i] = false;
            }

    colorParticles = NULL;
    blackWhiteParticles = NULL;
    level_surface = NULL;
}

void particles::main_init(int x, int y, SDL_Surface *levelSurface)
{
     level_surface = levelSurface;
     colorParticles = imageLoader.load_image("sprites/colorGradient.gif");
     blackWhiteParticles = imageLoader.load_image("sprites/blackWhiteGradient.gif");
     init_particles(x,y);
}


void particles::init_particles(int x, int y)
{
    return;
}

void particles::show_particles(int x, int y)
{
   start_particles();
   move_particles(x, y);
   blit_particles();
}


void particles::start_particles()
{
    for(int i =0; i < 10; i++){
        particleStarted[i] = true;
     }

}


void particles::move_particles(int x, int y)
{
    return;
}

void particles::blit_particles()
{
        for(int i = 0 ; i < 10 ; i++ ){
         if(particleStarted[i]){
             SDL_BlitSurface(colorParticles, &clippingRect, level_surface, &particleRect[i]);
             }
        }
}
