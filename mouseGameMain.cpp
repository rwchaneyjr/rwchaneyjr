#include <cstdlib>
#include <iostream>
#include <allegro.h>

using namespace std;

int main(int argc, char *argv[])
{
    printf("Hello TV LAND \n");
    
    /* Initialize Allegro. */
    allegro_init();     
    
    /* Set the resolution to 640 by 480 with SAFE autodetection. */
    set_gfx_mode(GFX_SAFE, 640, 480, 0, 0);

    /* Installing the keyboard handler. */
    install_keyboard(); 
    
    install_mouse();
    
    
    while(!key[KEY_ESC]) {
    
       if(mouse_b & 1) {
          printf("Left mouse:  %d       %d. \n", mouse_x, mouse_y);
       }
       
       if(mouse_b & 2) {
          printf("Right :  %d       %d. \n", mouse_x, mouse_y);
       }
                         
       rest(200);
    }
    
    /* Shut down allegro, destroy window, etc.... */
    allegro_exit();
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
END_OF_MAIN()
