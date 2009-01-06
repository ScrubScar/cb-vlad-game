
class Behemoth : public NCP
{
      public:
             Behemoth(int start_x, int start_y);
             ~Behemoth();

             void ncpInit();
             int pulse(SDL_Rect PlayerRect, status_change &status_code);
             void move( status_change &status_code);
             void start_fireball();
             bool fireball_hit_player(SDL_Rect object);
             void check_players_distance_from_npc(status_change &status_code);
             bool fireball_is_not_shooting();
             bool player_is_in_range();
             void move_fireball();
             void begin_pacing();


             // updates ncpChange surface to which direction ncp is facing
             void update_image_direction();

             // returns ncpChange surface
             SDL_Surface * get_Surface();

      private:
              SDL_Surface *ncpStandingRight[3];
              SDL_Surface *ncpStandingLeft[3];
              SDL_Surface * ncpChange;
              items dropItem;
              bool isAttacking;
              enum STATE_CODE{ DAMAGE = 1, HEAL = 2, WARP = 3 , NONE = 10};

              // fireball declairations
              SDL_Surface *fireball;
              SDL_Rect fireballRect;
              bool fireballIsShooting;
              bool fireballIsAlive;
              bool impactDirection;
              bool playerIsInRange;
              bool playerIsOutOfRange;
              int fireballRange;
              int fireballTotal;

              // this holds the direction the ncp was facing when it shot the fireball
              // so if the ncp changes direction while the fireball is moving , the fireball
              // won't change direction with it
              int originalDirectionFacing;

              // this holds the players y coord when the fireball was shot so when the player
              // moves the fireball doesnt keep following the player ( it's not a homming missle :P)
              int hold_player_y;
             };

Behemoth::Behemoth(int start_x, int start_y)
{
    // declaire the ncps position passed during creation
    ncpRect.x = start_x;
    ncpRect.y = start_y;
    ncpRect.w = 100;
    ncpRect.h = 58;

    // initialize all the fireball positions and states
    fireballRect.x = start_x;
    fireballRect.y = start_y;
    fireballRect.w = 20;
    fireballRect.h = 20;
    fireballIsShooting = false;
    fireballRange = 35;
    fireballTotal = 0;
}

Behemoth::~Behemoth()
{
    ;
}

void Behemoth::ncpInit()
{
     // initialize image surfaces
     ncpStandingRight[0] = imageLoader.load_image("sprites/BehemothRight.gif");
     ncpStandingLeft[0] = imageLoader.load_image("sprites/BehemothLeft.gif");
     fireball = imageLoader.load_image("sprites/fireBallLeft.gif");
}

SDL_Surface *Behemoth::get_Surface()
{
    return ncpChange;
}

int Behemoth::pulse(SDL_Rect playerRect, status_change &status_code)
{
    loc_playerRect = playerRect;
    update_image_direction();

     if(ncpHitpoints <= 0){
         ncpIsAlive = false;
         }

     if(ncpIsAlive == false){
         if( dropItem.show_item(ncpRect, playerRect, screen, status_code) ){
             itemGone = true;
             }
         }

     if(ncpIsAlive == true){
          move(status_code);
         }
    return 0;
}

void Behemoth::move( status_change &status_code)
{

     check_players_distance_from_npc(status_code);

     if(playerIsOutOfRange){
        begin_pacing();
        }
     if(playerIsInRange && fireballIsAlive == false){
         start_fireball();
         }

     if(fireballIsShooting && fireballIsAlive){
         SDL_BlitSurface(fireball, NULL, screen, &fireballRect);
         if( fireball_hit_player(fireballRect) ){
             status_code.code_number = DAMAGE;
             status_code.impact_direction = NONE;
             status_code.modify_number = 10;

             fireballIsShooting = false;
             isAttacking = false;
             return;
             }

         if(collision_with_map.object_map_collision(fireballRect) == true){
             fireballIsShooting = false;
             isAttacking = false;
             }
         }
      if(fireballIsAlive){
          move_fireball();
          }
}

void Behemoth::start_fireball()
{

    if(ncpRect.x < loc_playerRect.x){
        ncpDirectionFacing = RIGHT;
        }

    else if(ncpRect.x > loc_playerRect.x){
       ncpDirectionFacing = LEFT;
       }

    fireballRect.x = ncpRect.x + 20;
    fireballRect.y = ncpRect.y + 20;

    if(ncpRect.x > loc_playerRect.x) {
         if(ncpRect.x - loc_playerRect.x <= 200 ) {
             hold_player_y = loc_playerRect.y;
             originalDirectionFacing = ncpDirectionFacing;
             isAttacking = true;
             fireballIsShooting = true;
             fireballIsAlive = true;
          }
     }

     else if(ncpRect.x < loc_playerRect.x) {
         if( loc_playerRect.x - ncpRect.x <= 250)
         {
             hold_player_y = loc_playerRect.y;
             originalDirectionFacing = ncpDirectionFacing;
             isAttacking = true;
             fireballIsShooting = true;
             fireballIsAlive = true;
             }
         }
}

void Behemoth::update_image_direction()
{
     if(ncpDirectionFacing == RIGHT){
        ncpChange = ncpStandingRight[0];
        }

     else if(ncpDirectionFacing == LEFT){
        ncpChange = ncpStandingLeft[0];
        }
}

bool Behemoth::fireball_hit_player(SDL_Rect object)
{
    if(object.x < loc_playerRect.x + loc_playerRect.w &&
       object.x > loc_playerRect.x &&
       object.y + object.h > loc_playerRect.y &&
       object.y < loc_playerRect.y + loc_playerRect.h){
                return true;
                }
    else
        return false;
}

void Behemoth::check_players_distance_from_npc(status_change &status_code)
{
     if(collision_with_map.object_to_object_collision(loc_playerRect, ncpRect) == true) {
             status_code.code_number = DAMAGE;
             if(loc_playerRect.x < ncpRect.x ) {
                 status_code.impact_direction = RIGHT;
                 }

             else if(loc_playerRect.x + loc_playerRect.x  > ncpRect.x ){
                 status_code.impact_direction = LEFT;
                 }

             status_code.modify_number = 10;
             }


     if( ncpRect.x < loc_playerRect.x ){
         if( loc_playerRect.x - ncpRect.x >= 220 ){
                   playerIsOutOfRange = true;
                   playerIsInRange = false;
                    }

         else
             playerIsOutOfRange = false;
             playerIsInRange = true;
         }
     else if( ncpRect.x > loc_playerRect.x ){
         if( ncpRect.x - loc_playerRect.x >= 260) {
               playerIsOutOfRange = true;
               playerIsInRange = false;
             }

         else
             playerIsOutOfRange = false;
             playerIsInRange = true;
         }
}


void Behemoth::move_fireball()
{
     if(ncpRect.y < hold_player_y){
              fireballRect.y = fireballRect.y + 3;
              }

          else if(ncpRect.y > hold_player_y){
              fireballRect.y = fireballRect.y - 3;
              }

          if( originalDirectionFacing == LEFT){
              fireballTotal++;
              fireballRect.x = fireballRect.x - 15;
              impactDirection = RIGHT;
              if( fireballTotal == fireballRange ){
                  fireballTotal = 0;
                  fireballIsShooting = false;
                  fireballIsAlive = false;
                  }
              }
          if( originalDirectionFacing == RIGHT){
              fireballTotal++;
              fireballRect.x = fireballRect.x + 15;
              impactDirection = LEFT;
              if( fireballTotal == fireballRange ){
                  fireballTotal = 0;
                  fireballIsShooting = false;
                  fireballIsAlive = false;
                  }
              }
}

void Behemoth::begin_pacing()
{
     if(max_left < 50){
         ncpChange =  ncpStandingLeft[0];
         ncpDirectionFacing = LEFT;
         max_left++;
         ncpRect.x = ncpRect.x - SLOW_WALK;
         if(max_left >= 50){
             max_right = 0;
             max_left = 50;
             }
         }

     if(max_right < 50){
         ncpChange = ncpStandingRight[0];
         max_right++;
         ncpRect.x = ncpRect.x + SLOW_WALK;
         if(max_right >= 50){
             max_left = 0;
             max_right = 50;
             }
         }
}
