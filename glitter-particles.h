class glitter : public particles
{
     public:
            glitter();
            ~glitter();

            void init_particles(int x, int y);
            void move_particles(int x, int y);
            void show_particles(int x, int y);


     private:


};

glitter::glitter()
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
}

glitter::~glitter()
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
}

void glitter::init_particles(int x, int y)
{
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
}

void glitter::move_particles(int x, int y)
{
        srand((unsigned)time(0));
        for(int i = 0; i < 10; i++){
                particleRect[i].x = x + i * 2;
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

void glitter::show_particles(int x, int y)
{
        start_particles();
   move_particle(x, y);
   blit_particles();
}

