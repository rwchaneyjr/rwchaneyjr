#include <cstdlib>
#include <iostream>
#include <allegro.h>

volatile int ticks = 0;
void ticker()
{
	ticks++;
}
END_OF_FUNCTION(ticker)
 
const int updates_per_second = 60;

 
int main(void )
{
    int time = 0;
    int restDelay;
    int old_ticks;

    
	allegro_init();
	install_timer();
	
	/* Installing the keyboard handler. */
    install_keyboard(); 
 
	/* Initialize the timer */
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));
 
    /* Calculate a rest that is 1/10 of a tick. */
	restDelay = (1000/updates_per_second)/10;
 
	while(!key[KEY_ESC])
	{
        /* Update the screen once per second. */
	    if ((time%updates_per_second) == 0) {
           printf(" %d\n", time/updates_per_second);
        }
		time++;
		
        /* Wait for a tick from the timer. */
		while(ticks == 0)
		{
            /* Rest 1/10th of the ticker time. */
			rest(restDelay);
		}
		
		/* When we leave this loop, ticks = 1. */
		
		//old_ticks = ticks;
		
		printf("*");
		
		
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
			    printf(".");
				break; 
            }
		}
		
		/* DrawEverything(); */
	
	}
	return 0;
}
END_OF_MAIN()
