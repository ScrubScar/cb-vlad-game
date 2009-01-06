
class particles
{
      public:
             particles();
             ~particles();

             void init_particles(int x, int y,SDL_Surface *levelSurface);
             void show_particles(int x, int y);
             void move_particle(int x, int y);
             void start_particles();
             void blit_particles();


      private:
              SDL_Rect particleRect[10];
              SDL_Rect clippingRect;

              SDL_Surface *colorParticles;
              SDL_Surface *blackWhiteParticles;
              SDL_Surface *currentSurface;
              SDL_Surface *level_surface;

              int swayLeft;
              int swayRight;
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
    currentSurface = NULL;
    level_surface = NULL;

    swayLeft = 0;
    swayRight = 0;
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
    currentSurface = NULL;
    level_surface = NULL;

    swayLeft = 0;
    swayRight = 0;
}

void particles::init_particles(int x, int y, SDL_Surface *levelSurface)
{
     level_surface = levelSurface;
     colorParticles = imageLoader.load_image("sprites/colorGradient.gif");
     blackWhiteParticles = imageLoader.load_image("sprites/blackWhiteGradient.gif");

     clippingRect.x = 0;
     clippingRect.y = 8;
     clippingRect.w = 2;
     clippingRect.h = 2;

     for(int i = 0; i < 10; i++)
     {
         particleRect[i].x = x;
         particleRect[i].y = y;
         particleRect[i].w = 2;
         particleRect[i].h = 2;

         particleStarted[i] = false;
         moveHeight[i] = 20;
         }
     swayLeft = 0;
     swayRight = 0;
}

void particles::show_particles(int x, int y)
{
   start_particles();
   move_particle(x, y);
   blit_particles();
}


void particles::start_particles()
{
    for(int i =0; i < 10; i++){
        particleStarted[i] = true;
     }

}


void particles::move_particle(int x, int y)
{
        srand((unsigned)time(0));
        for(int i = 0; i < 10; i++){
                particleRect[i].x = x + i*2;
                if(particleStarted[i] ==  true) {
                        if(moveHeight[i] >= (rand()%15) + 10){
                            particleRect[i].y = y;
                            moveHeight[i] = 0;
                            particleStarted[i] = false;
                            }

                        else {
                              int holdRand = (rand()%3)+1;
                              if(holdRand < 0){ holdRand = 1;}
                              particleRect[i].y = particleRect[i].y - holdRand;
                              }

                         moveHeight[i]++;
                         clippingRect.y++;

                         if(clippingRect.y > 20){
                             clippingRect.y = 15;
                             }
                }
         }
}

void particles::blit_particles()
{
        for(int i = 0 ; i < 10 ; i++ ){
         if(particleStarted[i]){
             SDL_BlitSurface(colorParticles, &clippingRect, level_surface, &particleRect[i]);
             }
        }
}
