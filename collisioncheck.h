
class collision
{
      public:
             collision();
             ~collision();

             bool object_map_collision(SDL_Rect &object, int object_collision_direction);
             //void check_map_page(int page_number, int page_level) ;
             void check_map_page();
             void load_page_counter(int the_page_counter);

             bool object_to_object_collision(SDL_Rect &objectOne, SDL_Rect &objectTwo,
                                             int object_one_collision_direction ,
                                             int object_two_collision_direction);

      private:
              int tile_row, tile_column;
              int tile_x, tile_y;
              //int map_check_array[24][32];
              int local_array[24][32];
              int map_page;
              int player_position_x;
              int player_position_y;
              int page_number;
              int page_level;
              int theTiles;
              int def_x;
              int def_y;
              int page_counter;

              enum COLLISION_DIRECTION{ LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };
              enum MAP_PART{ PART_ONE = 0, PART_TWO = 800, PART_THREE = 1600, PART_FOUR = 2400 };

              SDL_Rect object_local;
       };

collision::collision()
{
   tile_row = 0;
   tile_column = 0;
   tile_x = 0;
   tile_y = 0;
   map_page = 0;
   object_local.x = 0;
   object_local.y = 0;
   object_local.w = 0;
   object_local.h = 0;

   page_number = 0;
   page_level = 0;
   page_counter = 0;
   def_x = 0;
   def_y = 0;
   theTiles = 0;

   player_position_x = 0;
   player_position_y = 0;

   }

collision::~collision()
{
   ;
   }

bool collision::object_map_collision(SDL_Rect &object, int object_collision_direction = 0)
{
     object_local = object;
     //check_map_page();
     page_counter  = 0;
     if(object.y > 1200 || object.x < 0 || object.x + object.w > 3200)
     {
          return true;
                 }
    while(page_counter < 8)
    {
                load_page_counter(page_counter);
                 tile_row = 0;
                 tile_column = 0;
                 tile_x = map_page;
                 tile_y = page_level;
                 while(tile_row < 24)
                 {
                     while( tile_column < 32 )
                     {
                            if(local_array[tile_row][tile_column] == 0)
                            {
                                 tile_x = tile_x + 25;
                                 }

                           if(local_array[tile_row][tile_column] != 0)
                            {
                                if( (object.x >= tile_x)  && (object.x < tile_x + 25) &&
                                    (object.y + object.h > tile_y) &&
                                    (object.y < tile_y + 25))
                                    {
                                       if(object.y > tile_y )
                                       {
                                           object_collision_direction = 1;
                                           }
                                       if(object.y < tile_y)
                                       {
                                           object_collision_direction = 2;
                                           }
                                       tile_y = 0, tile_x = 0;
                                       tile_column = 0, tile_row =0;
                                       return true;
                                    }

                                if( (object.x <= tile_x) && (object.x + object.w > tile_x) &&
                                    (object.y + object.h > tile_y) &&
                                    (object.y < tile_y + 25) )
                                    {
                                        if(object.y > tile_y )
                                           {
                                              object_collision_direction = 1;
                                              }
                                        if(object.y < tile_y)
                                           {
                                               object_collision_direction = 2;
                                              }


                                        return true;
                                    }
                                else
                                   tile_x = tile_x + 25;
                                }
                           tile_column = tile_column + 1;
                           }

                     tile_y = tile_y + 25;
                     tile_x = map_page;
                     tile_column = 0;
                     tile_row = tile_row + 1;
                     }
      page_counter++;
      }
      return false;
}


bool collision::object_to_object_collision(SDL_Rect &objectOne, SDL_Rect &objectTwo,
                                           int object_one_collision_direction = 0 ,
                                           int object_two_collision_direction = 0)
{
     if( (objectOne.x >= objectTwo.x) && (objectOne.x < objectTwo.x + objectTwo.w) &&
         (objectOne.y + objectOne.h > objectTwo.y) &&
         (objectOne.y < objectTwo.y + objectTwo.h))
         {
                  if(objectOne.y > objectTwo.y)
                  {
                       object_one_collision_direction = 2;
                       object_two_collision_direction = 1;
                       }

                  return true;
                  }

      else if( (objectOne.x <= objectTwo.x) && (objectOne.x + objectOne.w > objectTwo.x) &&
               (objectOne.y + objectOne.h > objectTwo.y) && (objectOne.y < objectTwo.y + objectTwo.h) )
               {
                      if(objectOne.y < objectTwo.y)
                      {
                          object_one_collision_direction = 1;
                          object_two_collision_direction = 2;
                          }
                      return true;
                      }

      else
          return false;
    }

void collision::check_map_page()
{
   ;
    }

void collision::load_page_counter(int the_page_counter)
{
     switch( the_page_counter)
     {


             case 0:      map_page = PART_ONE;
                          page_level = 0;
                          for(int a = 0; a < 24; a ++)
                          { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_one[a][b];} }
                            break;

             case 1:     map_page = PART_TWO;
                        page_level = 0;
                        for(int a = 0; a < 24; a ++)
                         { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_two[a][b];} }
                           break;

             case 2:
                   map_page = PART_THREE;
                  page_level = 0;
                  for(int a = 0; a < 24; a ++)
                  { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_three[a][b];} }
                  break;

             case 3:map_page = PART_FOUR;
                  page_level = 0;
                  for(int a = 0; a < 24; a ++)
                  { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_four[a][b];} }
                    break;

             case 4: map_page = PART_ONE;
                         page_level = 600;
                         for(int a = 0; a < 24; a ++)
                         { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_five[a][b];} }
                          break;

             case 5:map_page = PART_TWO;
                   page_level = 600;
                   for(int a = 0; a < 24; a ++)
                      { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_six[a][b];} }
                    break;
             case 6: map_page = PART_THREE;
                   page_level = 600;
                   for(int a = 0; a < 24; a ++)
                      { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_seven[a][b];} }
                   break;

             case 7:map_page = PART_FOUR;
                    page_level = 600;
                    for(int a = 0; a < 24; a ++)
                      { for(int b = 0; b < 32; b++) { local_array[a][b] = map_one_section_eight[a][b];} }
                       break;
             }

     }
