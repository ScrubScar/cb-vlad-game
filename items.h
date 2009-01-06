
class items
{
      public:
             items();
             ~items();

             void item_init(SDL_Rect ncpRect, SDL_Surface *main_level_surface);
             void item_init(int x, int y, SDL_Surface *main_level_surface);

             void item_gravity();

             bool show_item(SDL_Rect playerRect, SDL_Rect ncpRect, SDL_Surface *main_level_surface, status_change &status_code);
             bool show_item(SDL_Rect playerRect, status_change &status_code);
             bool player_has_attained_item(SDL_Rect playerRect);
             bool player_has_not_attained_item();


      protected:
                SDL_Surface *item_surface;
                SDL_Surface *level_surface;
                collision check_collision;
                imageLoad image_loader;
                SDL_Rect itemRect;
                bool itemJumping;
                bool itemHasInit;
                bool itemHasLanded;
                bool itemNotAttained;
                int itemJumpHeight;
                int direction;
                enum STATE_CODE{ DAMAGE = 1, HEAL = 2, WARP = 3, NONE = 0 };
                particles_glitter testParticle;

};

items::items()
{
    item_surface = NULL;
    level_surface = NULL;
    itemRect.x = 0;
    itemRect.y = 0;
    itemRect.w = 10;
    itemRect.h = 10;
    itemJumping = 0;
    itemJumpHeight = 0;
    itemHasInit = false;
    direction = 0;
    itemHasLanded = false;
}

items::~items()
{
    item_surface = NULL;
    level_surface = NULL;
    itemRect.x = 0;
    itemRect.y = 0;
    itemRect.w = 0;
    itemRect.h = 0;
}

void items::item_init(SDL_Rect ncpRect, SDL_Surface *main_level_surface)
{
     item_surface = image_loader.load_image("sprites/healthItem.gif");
     level_surface = main_level_surface;
     itemJumping = true;
     itemJumpHeight = 0;
     itemRect.x = ncpRect.x;
     itemRect.y = ncpRect.y;
     itemRect.w = 20;
     itemRect.h = 20;
     itemHasInit = true;
     itemNotAttained = true;
     testParticle.main_init(itemRect.x, itemRect.y, level_surface);
}

void items::item_init(int x, int y, SDL_Surface *main_level_surface)
{
     item_surface = image_loader.load_image("sprites/healthItem.gif");
     level_surface = main_level_surface;
     itemRect.x = x;
     itemRect.y = y;
     itemRect.w = 20;
     itemRect.h = 20;
     itemNotAttained = true;
     testParticle.main_init(itemRect.x, itemRect.y, level_surface);
}

bool items::show_item(SDL_Rect ncpRect, SDL_Rect playerRect, SDL_Surface *main_level_surface, status_change &status_code)
{
     if(itemHasInit == false){
          item_init(ncpRect, main_level_surface);
          }

     SDL_BlitSurface(item_surface, NULL, level_surface, &itemRect);
     testParticle.show_particles(itemRect.x, itemRect.y);

     if(player_has_attained_item(playerRect) ) {
         status_code.code_number = HEAL;
         status_code.modify_number = 10;
         return true;
         }

     item_gravity();
     return false;
}

bool items::show_item(SDL_Rect playerRect, status_change & status_code )
{
     SDL_BlitSurface(item_surface, NULL, level_surface, &itemRect);

     if(player_has_attained_item(playerRect) ) {
         status_code.code_number = HEAL;
         status_code.modify_number = 10;
         itemNotAttained = false;
         return true;
         }

     else{
          itemNotAttained = true;
          }

    return true;
 }

void items::item_gravity()
{
     if( itemJumping ) {
         if (check_collision.object_map_collision(itemRect) == false) {
                   itemRect.y = itemRect.y - 10;
                   itemJumpHeight++;
                   if(itemJumpHeight > 3) {
                        itemJumping = false;
                        }
                   }
         else if(check_collision.object_map_collision(itemRect) == true) {
              itemJumping = false;
              }

         }

     else if( itemJumping == false && itemHasLanded == false){
         if( check_collision.object_map_collision(itemRect) == false )
         {
             itemRect.y = itemRect.y + 10;
             }

         else if( check_collision.object_map_collision(itemRect) == true ){
              itemHasLanded = true;
              }
         }
     if( itemJumping == false && itemHasLanded == true){
          while( check_collision.object_map_collision(itemRect) == true ){
                 itemRect.y-- * 10;
                 }
         }
}

bool items::player_has_attained_item(SDL_Rect playerRect)
{
     return check_collision.object_to_object_collision(playerRect, itemRect);
     }

bool items::player_has_not_attained_item()
{
     return itemNotAttained;
     }
