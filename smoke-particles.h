class smoke : public particles
{
      public:
             smoke();
             ~smoke();

             void init_particles(int x, int y);
             void move_particles(int x, int y);

      private:
             int holdYticks;

};

smoke::smoke()
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
    holdYticks =0;
    colorParticles = NULL;
    blackWhiteParticles = NULL;
    level_surface = NULL;
}

smoke::~smoke()
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
    holdYticks =0;
    colorParticles = NULL;
    blackWhiteParticles = NULL;
    level_surface = NULL;
}

void smoke::init_particles(int x, int y)
{
    current_surface = blackWhiteParticles;

    clippingRect.x = 0;
    clippingRect.y = 100;
    clippingRect.w = 5;
    clippingRect.h = 5;

    for(int i = 0; i < 10; i++){
        particleRect[i].x = x;
        particleRect[i].y = y;
        particleRect[i].w = 5;
        particleRect[i].h = 5;

        particleStarted[i] = false;
        moveHeight[i] = 10;
    }

}

void smoke::move_particles(int x, int y)
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
                              if(holdRand < 0){
                                  holdRand = 1;
                                  }
                              particleRect[i].y = particleRect[i].y - holdRand;
                              }

                         holdYticks++;
                         moveHeight[i]++;
                         if(holdYticks%2 == 0){
                             clippingRect.y++;
                         }

                         if(clippingRect.y > 120){
                             clippingRect.y = 0;
                             }
                }
         }
}
