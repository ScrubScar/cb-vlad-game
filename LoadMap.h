class map_load
{
      public:
             map_load();
             ~map_load();

             void init(SDL_Surface *main_levelSurface);
             void load_map();
             void load_page(int page_number, int page_level);

      private:
              int map_check_array[24][32];
              SDL_Surface *levelSurface;
              SDL_Surface *tiles[3];

              imageLoad image_loader;



};

map_load::map_load()
{
     ;
}

map_load::~map_load()
{
   ;
}

void map_load::init( SDL_Surface * main_levelSurface)
{
     levelSurface = main_levelSurface;
     tiles[0] = image_loader.load_image("sprites/stonetileledge1.gif");
     tiles[1] = image_loader.load_image("sprites/stoneTilesprite1.gif");
     tiles[2] = image_loader.load_image("sprites/stoneTilesprite2.gif");
}

void map_load::load_map()
{
   int j= 0, k = 0, def_x = 0, def_y = 0;

   for(int y = 0; y < 2; y++){
        j = 0;
        k = 0;
        def_x = 0;
        def_y = 600 * y;

        for(int z = 0; z < 4; z++){
            load_page( z, y );
            j = 0;
            k = 0;
            def_x = 0;

             for(int b = 0; b < 24; b++){

                 for(int a = 0; a < 32; a++){
                     if(map_check_array[j][k] == 0) { def_x = def_x + 25;  k = k + 1;}

                         else if( map_check_array[j][k] == 1){
                                      image_loader.apply_surface(def_x, def_y, tiles[0],levelSurface);
                                      def_x = def_x + 25;
                                      k = k + 1;
                                      }
                         else if( map_check_array[j][k] == 2){
                                      image_loader.apply_surface(def_x, def_y, tiles[1], levelSurface);
                                      def_x = def_x + 25;
                                      k = k + 1;
                                      }

                         else if( map_check_array[j][k] == 3){
                                      image_loader.apply_surface(def_x, def_y, tiles[2], levelSurface);
                                      def_x = def_x + 25;
                                      k = k + 1;
                                      }
                         }
                  j = j + 1;
                  def_y = def_y + 25;
                  def_x = 800 * z;
                  k = 0;
                  }
              def_y = 600 * y;
             }
        }
}

void map_load::load_page(int page_number, int page_level)
{
    switch(page_number){
         case 0:  if(page_level == 0){
                    for(int a = 0; a < 24; a ++){
                        for(int b = 0; b < 32; b++) {
                            map_check_array[a][b] = map_one_section_one[a][b];
                            }
                        }
                    }

                   if(page_level == 1){
                       for(int a = 0; a < 24; a ++){
                           for(int b = 0; b < 32; b++) {
                               map_check_array[a][b] = map_one_section_five[a][b];
                               }
                           }
                        }
                    break;

         case 1:  if(page_level == 0){
                    for(int a = 0; a < 24; a ++){
                        for(int b = 0; b < 32; b++) {
                            map_check_array[a][b] = map_one_section_two[a][b];
                                }
                            }
                        }

                   if(page_level == 1){
                       for(int a = 0; a < 24; a ++){
                           for(int b = 0; b < 32; b++) {
                               map_check_array[a][b] = map_one_section_six[a][b];
                               }
                           }
                        }
                    break;

         case 2:  if(page_level == 0) {
                    for(int a = 0; a < 24; a ++){
                        for(int b = 0; b < 32; b++) {
                            map_check_array[a][b] = map_one_section_three[a][b];
                                }
                            }
                        }

                   if(page_level == 1){
                       for(int a = 0; a < 24; a ++){
                           for(int b = 0; b < 32; b++) {
                               map_check_array[a][b] = map_one_section_seven[a][b];
                               }
                           }
                       }
                    break;


         case 3:  if(page_level == 0)
                  {
                    for(int a = 0; a < 24; a ++){
                        for(int b = 0; b < 32; b++) {
                            map_check_array[a][b] = map_one_section_four[a][b];
                                } }
                        }

                   if(page_level == 1)
                   {
                       for(int a = 0; a < 24; a ++){
                           for(int b = 0; b < 32; b++) {
                               map_check_array[a][b] = map_one_section_eight[a][b];
                               }}
                        }
                    break;
         }
}

