
class NCP
{
      public:
             NCP();
             NCP(int start_location_x, int start_location_y);
             virtual ~NCP();

             virtual SDL_Surface * get_Surface();
             SDL_Rect &get_ncp_rect();

             void setScreenSurface(SDL_Surface *screenSurface);
             virtual void ncpInit();
             virtual int pulse(SDL_Rect PlayerRect, status_change &status_code);
             virtual void move(status_change &status_code);
             void set_ncp_x( int x );
             void set_ncp_y( int y );
             void set_ncp_hitpoints( int updatedHitpoints );
             void gravity();
             void showDroppedItem(SDL_Rect playerRect);
             virtual void begin_pacing();
             bool isDeathItemPickedUp();

             int get_ncp_x() const;
             int get_ncp_y() const;
             int get_ncp_w() const;
             int get_ncp_h() const;
             int get_ncp_hitpoints() const;

             bool isNcpAlive();

      protected:
              SDL_Surface *ncpStandingRight[3];
              SDL_Surface *ncpStandingLeft[3];
              SDL_Surface *ncpRunningRight[5];
              SDL_Surface *ncpRunningLeft[5];
              SDL_Surface * ncpChange;
              SDL_Surface * screen;

              SDL_Rect ncpRect;
              SDL_Rect loc_playerRect;

              imageLoad imageLoader;
              collision collision_with_map;

              int missleNumber;
              int ncpDirectionFacing;
              int ncpHitpoints;
              int ncpCollisionDirection;
              int holdFrameTicks;
              int holdX;
              int max_left;
              int max_right;

              bool gravityOn;
              bool ncpIsFalling;
              bool ncpIsAlive;
              bool itemPickedUp;
              bool itemGone;

              enum SPEED{ SLOW_WALK = 1, NORMAL_WALK = 8, FAST_RUN =10 };
              enum FACING_DIRECTION{ LEFT = 0, RIGHT = 1 };
              short int WALK_SPEED;
              };

NCP::NCP()
{
    ncpRect.x = 500;
    ncpRect.y = 335;
    ncpRect.w = 50;
    ncpRect.h = 50;

    max_left = 0;
    max_right = 50;


    WALK_SPEED = NORMAL_WALK;
    missleNumber = 0;
    ncpDirectionFacing = 0;
    ncpHitpoints = 100;
    ncpCollisionDirection = 0;
    holdFrameTicks = 0;
    holdX = 0;
    gravityOn = true;
    ncpIsFalling = false;
    ncpIsAlive = true;
    itemGone = false;
}

NCP::NCP(int start_location_x, int start_location_y)
{
    ncpRect.x = start_location_x;
    ncpRect.y = start_location_y;
    ncpRect.w = 50;
    ncpRect.h = 50;

    max_left = 0;
    max_right = 50;

    WALK_SPEED = NORMAL_WALK;
    missleNumber = 0;
    ncpDirectionFacing = 0;
    ncpHitpoints = 100;
    ncpCollisionDirection = 0;
    holdFrameTicks = 0;
    holdX = 0;
    gravityOn = true;
    ncpIsFalling = false;
    ncpIsAlive = true;
    itemPickedUp = false;
}

NCP::~NCP()
{
           ;
}

SDL_Surface * NCP::get_Surface()
{
    return ncpChange;
}

SDL_Rect &NCP::get_ncp_rect()
{
         return ncpRect;
}

void NCP::setScreenSurface(SDL_Surface *screenSurface)
{
     screen = screenSurface;
}

void NCP::ncpInit()
{
     ncpStandingRight[0] = imageLoader.load_image("sprites/KnucklesRight.gif");
     ncpStandingLeft[0] = imageLoader.load_image("sprites/KnucklesLeft.gif");
}

int NCP::pulse(SDL_Rect playerRect, status_change &status_code)
{
    loc_playerRect = playerRect;

     if(ncpHitpoints <= 0){
         ncpIsAlive = false;
         }

     if(ncpIsAlive){
          move(status_code);
         }
    return 0;
}

void NCP::move(status_change &status_code)
{
     begin_pacing();
}

void NCP::set_ncp_x(int x)
{
     ncpRect.x = x;
}

void NCP::set_ncp_y(int y)
{
     ncpRect.y = y;
}

void NCP::set_ncp_hitpoints(int updatedHitPoints)
{
     ncpHitpoints = updatedHitPoints;
}

void NCP::begin_pacing()
{
;
}


void NCP::gravity()
{
     ;
     }

int NCP::get_ncp_x() const
{
    return ncpRect.x;
}

int NCP::get_ncp_y() const
{
    return ncpRect.y;
}

int NCP::get_ncp_w() const
{
    return ncpRect.w;
}

int NCP::get_ncp_h() const
{
    return ncpRect.h;
}

int NCP::get_ncp_hitpoints() const
{
    return ncpHitpoints;
}

bool NCP::isNcpAlive()
{
     return ncpIsAlive;
}


bool NCP::isDeathItemPickedUp()
{
     return itemGone;
     }
