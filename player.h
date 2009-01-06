

class player
{
      public:
             player();
             player(int start_x, int start_y, int the_player_number);
             ~player();

             SDL_Surface * get_surface();
             SDL_Rect &get_player_rect();

             void setScreenSurface(SDL_Surface *screenSurface);
             void playerInit();
             void move(SDL_Event event, NCP *generic_ncp[2]);
             void set_player_x( int x );
             void set_player_y( int y );
             void set_player_score( unsigned long int updatedScore );
             void set_player_hitpoints( int updatedHitpoints );
             void push_back();
             void gravity();
             void jump();
             void player_state_change(status_change &status_code);

             //void pulse(SDL_Event event, SDL_Joystick &stick);
             //void move( SDL_Event event, SDL_Joystick &stick );

             int pulse(SDL_Event event, NCP *generic_ncp[2]);
             int get_player_x() const;
             int get_player_y() const;
             int get_player_w() const;
             int get_player_h() const;
             int get_player_hitpoints() const;
             int impact_direction;
             int damage_done;
             int get_score() const;


             Uint8 button;
             Sint16 axis;

      private:
              SDL_Surface *playerStandingRight[3];
              SDL_Surface *playerStandingLeft[3];
              SDL_Surface *playerRunningRight[5];
              SDL_Surface *playerRunningLeft[5];
              SDL_Surface *playerChange;
              SDL_Surface *screen;
              SDL_Rect playerRect;
              SDL_Rect ncpRect;
              SDL_Rect tempRect;

              imageLoad imageLoader;
              collision collision_with_map;
              missle theMissle[15];

              int missleNumber;
              int playerDirectionFacing;
              int playerCollisionDirection;
              int jumpHeight;
              int peakOfJump;
              int playerIsJumping;
              int playerNumber;
              int standingTicks;
              int runningRightTicks;
              int runningLeftTicks;
              int holdFrameTicks;
              int holdX;
              int holdPlayerX;
              int holdStandingTicks;
              int playerScore;
              int playerHitpoints;
              int animationTicks;
              int maxHitpoints;
              bool jumpingOrFalling;

              Uint32 holdTicks;
              Uint32 startTicks;

              bool playerDamaged;
              bool playerIsFalling;
              bool shoot_button_is_down;
              bool jump_button_is_down;
              bool gravityOn;

              enum SPEED{ SLOW_WALK = 2, NORMAL_WALK = 8, FAST_RUN =10 };
              enum FACING_DIRECTION{ LEFT = 0, RIGHT = 1 };
              enum STATE_CODE{ DAMAGE = 1, HEAL = 2, WARP = 3 };
              short int WALK_SPEED;

              Uint8 *keystates;
              };

 player::player()
 {
    keystates = SDL_GetKeyState(NULL);
    playerRect.x = 0;
    playerRect.y = 0;
    playerRect.w = 25;
    playerRect.h = 40;

    WALK_SPEED = NORMAL_WALK;
    standingTicks = 0;
    runningRightTicks = 0;
    runningLeftTicks = 0;
    holdFrameTicks = 0;
    holdStandingTicks = 0;
    gravityOn = true;
    missleNumber = 0;
    animationTicks= 0;

    peakOfJump = 0;
    playerIsJumping = false;
    playerIsFalling = false;
    shoot_button_is_down = false;
    jump_button_is_down = false;

    playerDirectionFacing = RIGHT;
    playerHitpoints = 100;
    playerScore = 0;
    jumpHeight = 210;
    }

player::player(int start_x, int start_y, int the_player_number)
{
    keystates = SDL_GetKeyState(NULL);
    playerRect.x = start_x;
    playerRect.y = start_y;
    playerRect.w = 25;
    playerRect.h = 40;
    playerNumber = the_player_number;
    standingTicks = 0;
    holdFrameTicks = 0;
    runningRightTicks = 0;
    runningLeftTicks = 0;
    holdStandingTicks = 0;
    gravityOn = true;
    playerDamaged = false;
    missleNumber = 0;
    animationTicks = 0;

    WALK_SPEED = NORMAL_WALK;

    if(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true ||
       playerRect.w > 200 || playerRect.h > 200)
    {
       playerRect.x = 0;
       playerRect.y = 0;
       playerRect.w = 25;
       playerRect.h = 40;
       }

    peakOfJump = 0;
    playerIsJumping = false;
    playerIsFalling = false;
    shoot_button_is_down = false;
    jumpingOrFalling = false;
    jump_button_is_down = false;
    holdPlayerX = 0;


    // directionFacing : 2 = right , 1 = left
    playerDirectionFacing = RIGHT;
    playerHitpoints = 100;
    playerScore = 0;
    jumpHeight = 210;
  }
player::~player()
{
    playerRect.x = 0;
    playerRect.y = 0;
    playerRect.w = 50;
    playerRect.h = 35;
    }

void player::playerInit()
{
     missleNumber = 0;
     startTicks = 0;
     holdTicks = 0;
     playerStandingRight[0] = imageLoader.load_image("sprites/sonicStandingRight1.gif");
     playerStandingRight[1] = imageLoader.load_image("sprites/sonicStandingRight2.gif");
     playerStandingRight[2] = imageLoader.load_image("sprites/sonicStandingRight3.gif");

     playerStandingLeft[0] = imageLoader.load_image("sprites/sonicStandingLeft1.gif");
     playerStandingLeft[1] = imageLoader.load_image("sprites/sonicStandingLeft2.gif");
     playerStandingLeft[2] = imageLoader.load_image("sprites/sonicStandingleft3.gif");

     playerRunningRight[0] = imageLoader.load_image("sprites/runningRight1.gif");
     playerRunningRight[1] = imageLoader.load_image("sprites/runningRight2.gif");
     playerRunningRight[2] = imageLoader.load_image("sprites/runningRight3.gif");
     playerRunningRight[3] = imageLoader.load_image("sprites/runningRight4.gif");
     playerRunningRight[4] = imageLoader.load_image("sprites/runningRight5.gif");

     playerRunningLeft[0] = imageLoader.load_image("sprites/runningLeft1.gif");
     playerRunningLeft[1] = imageLoader.load_image("sprites/runningLeft2.gif");
     playerRunningLeft[2] = imageLoader.load_image("sprites/runningLeft3.gif");
     playerRunningLeft[3] = imageLoader.load_image("sprites/runningLeft4.gif");
     playerRunningLeft[4] = imageLoader.load_image("sprites/runningLeft5.gif");

     maxHitpoints = 100;

     for(int i = 0; i < 15; i ++)
     {
             theMissle[i].missleInit();
             }

     }

SDL_Surface * player::get_surface()
{
    return playerChange;
    }


SDL_Rect &player::get_player_rect()
{
         return playerRect;
         }

//void player::pulse(SDL_Event event, SDL_Joystick &stick)
//{
//     gravity();
//     move(event, stick);
//     }

 void player::setScreenSurface(SDL_Surface *screenSurface)
 {
      screen = screenSurface;
      }

int player::pulse(SDL_Event event, NCP *generic_ncp[2])
{
     holdTicks = SDL_GetTicks() - startTicks;
     if(playerDamaged == false) {
         move(event, generic_ncp);
         }

     if(gravityOn == true)
     {
         gravity();
         }

     if(playerDamaged == true){
         push_back();
         }
     startTicks = SDL_GetTicks();
     imageLoader.apply_surface(playerRect.x, playerRect.y, playerChange, screen);

     return 0;
}

void player::set_player_x( int x )
{
     playerRect.x = x;
     }

void player::set_player_y( int y )
{
     playerRect.y = y;
     }

void player::move(SDL_Event event, NCP *generic_ncp[2])
{
     for(int i = 0; i < 15; i++)
     {
             if(theMissle[i].is_missle_alive() == true)
             {
                 damage_done = theMissle[i].missleMove(generic_ncp);
                 playerScore = playerScore + damage_done;
                 tempRect = theMissle[i].get_missle_rect();
                 SDL_BlitSurface(theMissle[i].get_missle_surface(), NULL, screen, &tempRect);
                 }
             }

     if(holdX == playerRect.x)
     {
         runningRightTicks = 0;
         runningLeftTicks = 0;
         if(holdStandingTicks % 50 == 0)
         {
             standingTicks++;
             }
         holdStandingTicks++;

         if(standingTicks > 2)
         {
            standingTicks = 0;
            }
         if(playerDirectionFacing == RIGHT  )
         {
             playerChange = playerStandingRight[standingTicks];
             }
         else if(playerDirectionFacing == LEFT)
         {
             playerChange = playerStandingLeft[standingTicks];
             }

         }
     holdFrameTicks = SDL_GetTicks();
     holdX = playerRect.x;

     if(playerIsJumping && gravityOn)
     {
         jump();
         }

     // lets us know if jump button is being held down
     if(event.type == SDL_KEYUP)
     {
             if(event.key.keysym.sym == SDLK_RSHIFT){
                 WALK_SPEED = NORMAL_WALK;
                  }

             if(event.key.keysym.sym == SDLK_i) {
                 shoot_button_is_down = false;
                 }

             }


     if(keystates[SDLK_d])    // move right
     {
          if(runningRightTicks > 4){
             runningRightTicks = 0;
             }

         playerChange = playerRunningRight[runningRightTicks];
         if(animationTicks >= 2){
             runningRightTicks++;
             animationTicks = 0;
             }
          animationTicks++;
         standingTicks = 0;
         playerRect.x = playerRect.x + WALK_SPEED;
          while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true)
          {
              playerRect.x = playerRect.x - WALK_SPEED ;
              }
              playerDirectionFacing = RIGHT;
          }

     if(keystates[SDLK_a])   // move left
     {
         if(runningLeftTicks > 4){
             runningLeftTicks = 0;
             }
         playerChange = playerRunningLeft[runningLeftTicks];
         if(animationTicks >= 2){
             runningLeftTicks++;
             animationTicks = 0;
             }
          animationTicks++;
         playerRect.x = playerRect.x - WALK_SPEED;
          while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true)
          {
              playerRect.x = playerRect.x + WALK_SPEED;
              }
              playerDirectionFacing = LEFT;
          }

     if(keystates[SDLK_w] && gravityOn == false)
     {
         playerRect.y = playerRect.y - WALK_SPEED;
          while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true)
          {
              playerRect.y = playerRect.y + WALK_SPEED ;
              }
          }

     if(keystates[SDLK_s] && gravityOn == false)
     {
         playerRect.y = playerRect.y + WALK_SPEED ;
          while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true)
          {
              playerRect.y = playerRect.y - WALK_SPEED;
              }
          }


     if(keystates[SDLK_F1])
     {
        playerRect.x = 0;
        playerRect.y = 0;
        }

     if(keystates[SDLK_F2])
     {
           gravityOn = true;
        }

     if(keystates[SDLK_F3])
     {
         gravityOn = false;
         }

     if(keystates[SDLK_RSHIFT])
     {
         WALK_SPEED = FAST_RUN;
         }

     if(keystates[SDLK_SPACE])  // jump
     {
          if(jumpingOrFalling == false && playerIsFalling == false)
            {
                jumpHeight = 250;
                playerIsJumping = true;
                jumpingOrFalling = true;
                }

            }

     if(keystates[SDLK_i])
     {
          if(shoot_button_is_down== false)
          {
              if(missleNumber > 14){
                          missleNumber = 0;
                          }
              if(theMissle[missleNumber].is_missle_alive() == false) {
                          theMissle[missleNumber].set_missle_x(playerRect.x);
                          theMissle[missleNumber].set_base_x(playerRect.x);
                          theMissle[missleNumber].set_missle_y(playerRect.y);
                          theMissle[missleNumber].start_missle(true, playerDirectionFacing);
                          }
                          missleNumber++;
                 shoot_button_is_down = true;
              }
         }

}


void player::set_player_score( unsigned long int updatedScore )
{
     playerScore = updatedScore;
     }

void player::set_player_hitpoints( int updatedHitpoints )
{
     playerHitpoints = updatedHitpoints;
     }

void player::gravity()
{

    if( playerIsJumping == false )
    {
        playerRect.y = playerRect.y + peakOfJump * 3;
        playerIsFalling = true;

        while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true )
        {
            playerRect.y = playerRect.y - 1;
            playerIsFalling = false;
            peakOfJump = 0;
            playerCollisionDirection = 1 ;
            jumpingOrFalling = false;
            }

         if(playerIsFalling == false )
         { playerCollisionDirection = 1;}


         if( peakOfJump < 10 )
         {
              peakOfJump = peakOfJump + 1;
              }
         }
}

void player::jump()
{
    if(jumpHeight <= 0 )
    {
        playerIsJumping = false;
        jumpHeight = 0;
        }

    playerRect.y = playerRect.y - (jumpHeight/15);
    while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true)
    {
        playerRect.y = playerRect.y + 1 ;
        playerIsJumping = false;
        playerIsFalling = true;
        playerCollisionDirection = 2;
        jumpHeight = 0;
        }

        if(jumpHeight > 0 )
        {
            playerIsJumping = true;
            jumpHeight = jumpHeight - 20;
            }
     }

int player::get_player_x() const
{
    return playerRect.x;
    }

int player::get_player_y() const
{
    return playerRect.y;
    }

 int player::get_player_hitpoints() const
 {
     return playerHitpoints;
     }

int player::get_player_w() const
{
    return playerRect.w;
    }

int player::get_player_h() const
{
    return playerRect.h;
    }

int player::get_score() const
{
         return playerScore;
         }

void player::player_state_change(status_change &status_code)
{
     if( status_code.code_number == DAMAGE ) {
         playerHitpoints = playerHitpoints - status_code.modify_number;
         impact_direction = status_code.impact_direction;
         playerDamaged = true;
         }

     else if( status_code.code_number == HEAL && playerHitpoints){
          playerHitpoints = playerHitpoints + status_code.modify_number;
          if(playerHitpoints > maxHitpoints){
              playerHitpoints = maxHitpoints;
              }
          }

     else if( status_code.code_number == WARP ){
          playerRect.x = status_code.x;
          playerRect.y = status_code.y;
          }

     status_code.reset();
}

void player::push_back()
{
         if(impact_direction == LEFT){
             playerRect.x = playerRect.x + 10;
             while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true)
             {
                 playerRect.x--;
                 }
             }
         else if(impact_direction == RIGHT) {
             playerRect.x = playerRect.x - 10;
             while(collision_with_map.object_map_collision(playerRect, playerCollisionDirection) == true)
             {
                 playerRect.x++;
                 }
             }

         else if(impact_direction == 10)
         {
              playerDamaged = false;
              }
         holdPlayerX++;
         if(holdPlayerX > 3){
             holdPlayerX = 0;
             playerDamaged = false;
             }
}
