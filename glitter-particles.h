class particles_glitter : public particles
{
     public:
            particles_glitter();
            ~particles_glitter();

            void move_particles(int x, int y);
            void init_particles(int x, int y);

     private:


};

particles_glitter::particles_glitter()
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

particles_glitter::~particles_glitter()
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

void particles_glitter::init_particles(int x, int y)
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

    current_surface = colorParticles;
}

void particles_glitter::move_particles(int x, int y)
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

