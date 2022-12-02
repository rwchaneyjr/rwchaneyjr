#include <allegro.h>
#include <stdio.h>

#define PINK makecol(255, 0, 255)
#define GREEN makecol(0, 255, 0)
#define BLUE makecol(0, 0, 255)
#define YELLOW makecol(255, 255, 0)
#define RED makecol(255, 0, 0)
#define WHITE makecol(255, 255, 255)

/* Routines called */
void lineCallback(BITMAP *bmp, int x, int y, int color);

BITMAP *buffer = NULL;
int main()
{
    int color;
    int x1, y1, x2, y2;
    int points[8], polyPoints[10];
    
    // Initialize Allegro.        
    allegro_init();      

    // Set the resolution to 640 by 480 with SAFE autodetection.
    set_gfx_mode(GFX_SAFE, 640, 480, 0, 0);

    // Installing the keyboard handler.
    install_keyboard();
    
    /* Make a buffer the size of the screen. */
	buffer=create_bitmap(640,480);
	
    do{	
	    if(key[KEY_F1]){
           /* The textprintf function is deprecated. */
           textprintf(buffer,font,5,20,makecol(0,191,255),"Hello Gorgeous");
           blit(buffer,screen,0,0,0,0,640,480);
        }
		else if (key[KEY_F2]){
           textout_ex(screen, font, "K O O W E L L       D U D E", 320, 240, 10, -1);
        }
        else if (key[KEY_F3]){
             allegro_message("I am a Flumbo Head!");
        }
        else if (key[KEY_F4]){
             color = makecol(255, 255, 0);
             hline(screen, 100,300,500,color);
        }
        else if (key[KEY_F5]){
             vline(screen, 300, 100, 400, PINK);
        }
        else if (key[KEY_F6]){
             line(screen, 100, 100, 300, 300, GREEN);
        }
        else if (key[KEY_F7]){
             rect(screen, 500,20,600,120, BLUE);
             rectfill(screen, 520,40,580,100, GREEN);
        }
        else if (key[KEY_F8]){
             /*
             printf("Enter the starting points, x0 and y0. \n");
             scanf("%d %d", &x1, &y1);
             printf("Enter the ending points, x0 and y0. \n");
             scanf("%d %d", &x2, &y2);
             */
             x1 = 200;
             y1 = 200;
             x2 = 400;
             y2 = 100;
             
             do_line(screen, x1,y1,x2,y2, YELLOW, lineCallback);
             
             circlefill(screen, 100, 350, 25, BLUE);
        }
        else if (key[KEY_F9]) {
             ellipse(screen,500,400,30,10,YELLOW);
             ellipsefill(screen,500,400,10,30,GREEN);
             
             points[0] = 50;
             points[1] = 450;
             
             points[2] = 100;
             points[3] = 300;
             
             points[4] = 150;
             points[5] = 400;
             
             points[6] = 200;
             points[7] = 450;
             
             spline(screen, points, YELLOW);
             
             triangle(screen,500,150,550,200,600,150, YELLOW);
             
             polyPoints[0] = 150;
             polyPoints[1] = 350;
             
             polyPoints[2] = 150;
             polyPoints[3] = 200;
             
             polyPoints[4] = 550;
             polyPoints[5] = 100;
             
             polyPoints[6] = 270;
             polyPoints[7] = 350;
             
             polyPoints[8] = 370;
             polyPoints[9] = 150;
             
             polygon(screen, 5, polyPoints, RED);
             
             rest(1000);
             
             floodfill(screen, 400,95, WHITE);
        }
        
		
	} while(!key[KEY_ESC]);
	return 0;
}
END_OF_MAIN();


void lineCallback(BITMAP *bmp, int x, int y, int color)
{
     int backColor, currCol;
     
     backColor = getpixel(bmp, 2, 2);
     currCol = getpixel(bmp, x, y);
     
     printf("bC %d, p %d \n", backColor, currCol);
     
     /* Get pixel returns the color of what is at x, y.  If it is positive,
        a circle will be drawn around it. */
     if(currCol == backColor){
        putpixel(bmp, x, y, color);
        /* The rest gives time for the color to get to the screen. */
        rest(1);
     }
     else {
          circle(bmp,x,y,60,GREEN);
     }
}


