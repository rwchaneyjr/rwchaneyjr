#include <allegro.h>

int main() 
{ 
 // Initialize Allegro.        
 allegro_init();      

 // Set the resolution to 640 by 480 with SAFE autodetection.
 set_gfx_mode(GFX_SAFE, 640, 480, 0, 0);

 // Installing the keyboard handler.
 install_keyboard();

 // Printing text to the screen.
 textout(screen, font, "Hello TV LAND!", 1, 5, 10);
 textout(screen, font, "Bye-bye !", 1, 20, 20);
 textout(screen, font, "Press ESCape to quit.", 1, 40, 30);

 // Looping until the ESCape key is pressed.
 while(! key[KEY_ESC])
   poll_keyboard(); // This shouldn't be necessary in Windows. 

 // Exit program.
 allegro_exit();
 return 0;     
}     

// Some Allegro magic to deal with WinMain().
END_OF_MAIN()
