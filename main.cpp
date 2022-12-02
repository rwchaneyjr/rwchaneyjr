#include <stdio.h>
#include <allegro.h>
#include "mappyal.h"
#include "PROTO.h"
#define WIDTH 320
#define HEIGHT 320
#define MODE GFX_AUTODETECT_WINDOWED
#define RIGHT_LIMIT (mapwidth*mapblockwidth) - WIDTH
#define WHITE makecol(255, 255, 255)
#define BLACK makecol(0, 0, 0)
#define MAIN
#include "GLOBALS.h"



volatile int ticks = 0;
void ticker()
{
	ticks++;
}
END_OF_FUNCTION(ticker)
 
const int updates_per_second = 60;
	



int collided(int x, int y)
{
    BLKSTR *blockdata;
	blockdata = MapGetBlockInPixels(x, y);
	return blockdata->tl;
}






int main(void) 
{   
    LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
    int time = 0;
    int restDelay;
    int old_ticks;
    int j;
    char dt = false;
    int xoff,yoff;
    int oldx,oldy;
    
    x = 0; y =200;xb = 150; j =0;
    tf = true;
    tf1=true;
    tf2 = true;
    tf3 = true;
    tf4 = true;
    a1 = false;
    a2 = false;
    a3 = false;
    a4 = false;
    b1 = false;
    b2 = false;
    b3 = false;
    b4 = false;
    end = false;
    xc = 0;
    yd = 70;
    yc = 320;
    yb = 380;
    ya = 120;
     sx = x;
     xoffset = 0;
     y1 = 120;
     y2 = 120;
     y3 =320;
     y4 =320;
     level0 = true;
     level1=false;
     level2 = false;
     d = false;
     Score = 150;
	//initialize the program
    allegro_init();
    
	set_color_depth(16);
	set_gfx_mode(MODE, 640, 480, 0, 0);
	MapLoad("map10.FMP");
	 
	install_keyboard(); 
    install_timer();
      if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "") != 0) 
   {
        allegro_message("Error initializing sound system");
       return 1;
    }
		
  /* Load the midi file. */
	music = load_midi("kawliga.mid");
	if (!music) {
		allegro_message("Error loading Midi file");
		return 1;
	}
	/* Play the midi music, make sure that on the Windows Master Volume, the
	   SW Synth volume is turned up. */
	if (play_midi(music, 1) != 0) {
		allegro_message("Error playing Midi\n%s", allegro_error);
		return 1;
	}
	textout_ex(screen, font, "AnimSprite Program (ESC to quit)",
        0, 0, WHITE,0);

	
    
    
	install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));
 
    /* Calculate a rest that is 1/10 of a tick. */
	restDelay = (1000/updates_per_second)/10;
    
    
 
     
     	scene = load_bitmap("dragon.bmp",NULL);
    for (n=0; n<6; n++)
    {
       
        dragonimg[n] = grabframe(scene,128,64,0,0,3,n);
    }
     scene = load_bitmap("explosion.bmp",NULL);
    for(n = 0; n < 6; n++)
    {
          explosionimg[n] = grabframe(scene,32,32,0,0,6,n);
    }
    scene = load_bitmap("skeeter.bmp",NULL);
    for(n = 0; n < 6; n++)
    skeeterimg[n] = grabframe(scene,50,40,0,0,6,n);
    scene = load_bitmap("bee.bmp",NULL);
    for (n = 0; n < 6; n++)
    beeimg[n] = grabframe(scene,50,40,0,0,6,n);
  
	while((!end))
	{ 
    
         scene = create_bitmap(640, 480);               
        
                        
      
        /* Update the screen once per second. */
	    if ((time%updates_per_second) == 0) {
          // printf(" %d\n", time/updates_per_second);
        }
		time++;
		
        /* Wait for a tick from the timer. */
		while(ticks == 0)
		{
            /* Rest 1/10th of the ticker time. */
			rest(restDelay);
		}
		
		/* When we leave this loop, ticks = 1. */
		
		old_ticks = ticks;
		
		//printf("*");
		
		
        /* This loop gives us one tick interval to do our work. */
		while(ticks > 0)
		{
            /* Here ticks and old_ticks are equal to 1 or 2. */
			old_ticks = ticks;
    
  
    
   
    
			/* DoLogic(); */
            /* In the logic section, there is a good chance that ticks 
               will be incremented. */
            /* This rest will simulate our logic.  It will use one half the
               time that we allocate for a frame.  */
            rest(restDelay*5);
            
			ticks--;
			
			/* If old ticks > ticks, ticks was incremented twice during the logic 
			   section. */
			/* If old_ticks = ticks, ticks got incremented once during the logic
			   section. */
            /* If old_ticks < ticks, ticks got incremented twice during the logic
               section. */
			if(old_ticks <= ticks) {
                /* Logic is taking too long: abort and draw a frame. */
			    //printf(".");
				break; 
            }
		}
		
	
		
		
 
	
    
    
         
      
   
   
   
    move();
    	
      if (collided(x+120,y+38)) {
       x = tempX;
       y = tempY;
       }            
       if (xoffset < 0) xoffset = 0;
        if (xoffset > RIGHT_LIMIT) xoffset = RIGHT_LIMIT; 
        MapChangeLayer(0);
        MapDrawBG(scene, xoffset, 0, 0, 0, 640, 480); 
        MapChangeLayer(1);
		MapDrawBGT(scene, xoffset, 0, 0, 0, 640, 480);
       
       

      //rectangle for dragon
      // rect(scene,x+20,y+22,x+120,y+54,makecol(255,255,255));
  	if(x <=2189)
      level0 = true;
      if(level0)
      {  
  	   drawDragonScroll(scene);
        
        fire();
       staticfall();
       cur1 = anibeeskeeter();
        if ( collided1()){
             Score = Score -5;
      
       circle(); 
      
   
       }
      
      }
      if((x > 2189) && (x <4378))
      {
      level1 = true;
      level0 = false;
      }
      if(level1)
      { 
         drawDragonScroll(scene);          
  	   level1A();
  	   fire();
      dynamicbugfall();
  
  	  	
     if(collide2()){
      Score = Score -5;
      circle();
     
      }
      } 
       if(x > 4378)
       {
       level2 = true;
        level1 = false; 
        }
        if(level2)
        { 
       drawDragonScroll(scene);
       anibeeskeeter();
       fire();
       staticfall();
       if(collided1()){
                       
       Score = Score -5;
       circle();
       
       }
       level1A();
       
       fire();
       if(collide2()){
       circle();
      
       Score = Score-5;
       }
      dynamicbugfall();
}

		textprintf_ex(/*screen*/scene,font,0,20,WHITE,0,
            "Score: %3d",Score);
	    vsync();
        acquire_screen();
        blit(scene, screen, 0, 0, 0, 0, 640, 480);
       	release_screen();
		
   if((Score >= 0 )&&(x > 6560))
   {     
           allegro_message(" YOU WON ! ");
          for(n = 0; n < 2; n++)
    {
          destroy_sample(sample[n]);
          }
          destroy_midi(music);    
   
    for(n=0;n<6;n++){
    destroy_bitmap(skeeterimg[n]);
    destroy_bitmap(dragonimg[n]);
    destroy_bitmap(beeimg[n]);
    }
    MapFreeMem ();
    destroy_bitmap(scene);
    destroy_bitmap(temp);
    allegro_exit();
     
          end = true; }
     if ((Score < 0))
            {
                
            allegro_message("YOU LOST ");
           for(n = 0; n < 2; n++)
    {
          destroy_sample(sample[n]);
          }
          destroy_midi(music);    
   
    for(n=0;n<6;n++){
    destroy_bitmap(skeeterimg[n]);
    destroy_bitmap(dragonimg[n]);
    destroy_bitmap(beeimg[n]);
   end = true; }
    MapFreeMem ();
    destroy_bitmap(scene);
    destroy_bitmap(temp);
    allegro_exit();
     }        
        
	
}


            


    
	
		
    
}
END_OF_MAIN()

