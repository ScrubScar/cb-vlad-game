
class missle
{
      public:
             missle();
             ~missle();
             SDL_Surface * get_missle_surface();
             void set_missle_x(int x);
             void set_missle_y(int y);

             int get_missle_x();
             int get_missle_y();
             SDL_Rect get_missle_rect();
             void start_missle( bool missleActivate, int directionFacing);
             void missleInit();
             bool is_missle_alive();
             int missleMove(NCP *generic_ncp[2]);
             void set_base_x(int x);
             int get_base_x();




      private:
              SDL_Surface *missleImage;
              SDL_Rect ncpRect;
              imageLoad imageLoader;
              bool missleExists;
              SDL_Rect missleRect;
              int missleCollisionDirection;
              collision collision_with_map;
              int baseX;
              int missleDirection;
              enum FACING_DIRECTION{ LEFT = 0, RIGHT = 1 };


              };

missle::missle()
{
    missleImage = NULL;
    missleExists = false;
    missleRect.x = 0;
    missleRect.y = 0;
    missleRect.w = 10;
    missleRect.h = 10;
    baseX = 0;
                }


missle::~missle()
{
                 ;
                 }

void missle::missleInit()
{
     missleImage = imageLoader.load_image("sprites/missle.gif");
     missleRect.x = 0;
     missleRect.x = 0;
     missleRect.x = 0;
     missleExists = false;
     baseX = 0;
     }


int missle::missleMove(NCP *generic_ncp[2])
{
    for(int i = 0; i < 2; i++)
    {
      if( (missleRect.x > generic_ncp[i]->get_ncp_x()) && (missleRect.x < generic_ncp[i]->get_ncp_x() + generic_ncp[i]->get_ncp_w())
         && (missleRect.y + missleRect.h > generic_ncp[i]->get_ncp_y()) && (missleRect.y < generic_ncp[i]->get_ncp_y() + generic_ncp[i]->get_ncp_h())
         && missleExists == true && generic_ncp[i]->isNcpAlive() == true )
         {
             missleExists = false;
             generic_ncp[i]->set_ncp_hitpoints(generic_ncp[i]->get_ncp_hitpoints() - 10);
             if(generic_ncp[i]->get_ncp_hitpoints() <= 0)
             {
                 return 10;
                 }
             }
         }


     if(missleDirection == RIGHT && missleRect.x - baseX > 225)
     {
        missleExists = false;
        return 0;
        }

     if(missleDirection == LEFT && baseX - missleRect.x > 250)
     {
        missleExists = false;
        return 0;
        }

     if(collision_with_map.object_map_collision(missleRect, missleCollisionDirection) == true  )
     {
         missleExists = false;
         return 0;
         }

     else if(missleDirection == RIGHT){
          missleRect.x = missleRect.x + 25;
          return 0;
          }
     else if(missleDirection == LEFT){
          missleRect.x = missleRect.x - 25;
          return 0;
          }
     }

void missle::start_missle(bool missleActivate, int directionFacing)
{
     missleExists = true;
     missleDirection = directionFacing;
     }

int missle::get_missle_x()
{
    return missleRect.x;
}

int missle::get_missle_y()
{
    return missleRect.y;
}

SDL_Rect missle::get_missle_rect()
{
         return missleRect;
         }

bool missle::is_missle_alive()
{
     return missleExists;
     }

void missle::set_base_x(int x)
{
     baseX = x;
     }

void missle::set_missle_x(int x)
{
     missleRect.x = x;
}

void missle::set_missle_y(int y)
{
     missleRect.y = y;
     }

int missle::get_base_x()
{
    return baseX;
}

SDL_Surface * missle::get_missle_surface()
{
            return missleImage;
            }

