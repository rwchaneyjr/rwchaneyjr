#include <allegro.h>
#include <iostream>
#include <stdio.h>

int main(void) 
{ 
 // Initialize Allegro.        
 allegro_init();      

 // Set the resolution to 640 by 480 with SAFE autodetection.
 set_gfx_mode(GFX_SAFE, 640, 480, 0, 0);

 // Installing the keyboard handler.
 install_keyboard();

 // Printing text to the screen.
 textout_ex(screen, font, "Hello TV LAND!", 1, 1, 10, -1);
 textout_ex(screen, font, "Press ESCape to quit.", 1, 12, 11, -1);
 textout_ex(screen, font, "N U D E       D U D E", 320, 240, 10, -1);
 

 // Looping until the ESCape key is pressed.
 while(! key[KEY_ESC]);
   poll_keyboard(); // This shouldn't be necessary in Windows. 
   
 

 // Exit program.
 allegro_exit();
 
 return 0;     
}     

// Some Allegro magic to deal with WinMain().
END_OF_MAIN()
