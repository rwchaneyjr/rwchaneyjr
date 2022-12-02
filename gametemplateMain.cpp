#include <cstdlib>
#include <iostream>
#include <allegro.h>
#include <time.h>

using namespace std;

/* Defines. */
#define SCR_WID 800
#define SCR_HI 600

#define DELAY 20


/* Define some colors. */
/* Note these colors are for 8 bit color depth.  They don't help too much with
sprites. */
#define MAGENTA  13
#define GREEN  10
#define L_GREEN  makecol(0, 215, 55)
#define BLUE 9
#define YELLOW  14
#define RED  12
#define WHITE  15
#define BLACK  0
#define ORANGE 6
#define CYAN 11

/* Global variables. */
/* Colors. */
int blue, pink, red;

/* Screen. */
int x_wid, y_hi;
int backColor;

/* Keyboard. */
char kUp, kDown, kRight, kLeft, kSpace;

/* Mouse. */
/* Clicks. */
char mouseLeftClick, mouseRightClick;
/* Movement. */
int mx, my, pmx, pmy;
char mouseMove;



/* Routines called. */
void startAllegro(int width, int height);
void startGame(int width, int height);
void endGame(void);

/* Input processing. */
void setKeyActionFlags(void);
void setMouseClickActionFlags(void);
void setMouseMovementActionFlags(void);


int main(int argc, char *argv[])
{
    int j;
    int ulx, uly;
    char search, found;
    
    printf("Hello TV Land! \n");
    
    /* Init Allegro System. */
    startAllegro(SCR_WID, SCR_HI);
    
    /* Initialize Game variables. */
    startGame(SCR_WID, SCR_HI);
    
    do {
        /* Get inputs. */
        setKeyActionFlags();
        setMouseClickActionFlags();
        setMouseMovementActionFlags();
        
        /* Calculate new frame. */
        
        
        /* Process effect of inputs. */
        if (kUp) {
           printf("kUp \n");
        }
        else if (kDown) {
           printf("kDown \n");
        }
        else if (kLeft) {
           
        }
        else if (kRight) {
           
        }
        else {
           
        }
        
        /* Ship Weapons. */
        if (kSpace) {
           
        }
        
        /* Process non-input effects. */
        
        /* Draw. */
        
        
        /* Set rest for about 50 frame refresh. */
        rest(DELAY);
        
    }while(!key[KEY_ESC]);
    
    endGame();
    
    printf("Bye bye \n");
    
    return EXIT_SUCCESS;
}
END_OF_MAIN()


void startAllegro(int width, int height)
{
     /* Initialize Allegro. */
     allegro_init();    
    
     /* The color depth is set to 16 so sprite transparency works. */
     set_color_depth(16);
     /* Set the resolution to 640 by 480 with SAFE autodetection. */
     set_gfx_mode(GFX_SAFE, width, height, 0, 0);
     
     /* Installing the keyboard handler. */
     install_keyboard(); 
     
     /* Install Mouse. */
     install_mouse();
     
     /* Define some 16 bit colors. */
     blue = makecol(0, 0, 255);
     pink = makecol(255, 0, 255);
     red = makecol(255, 0, 0);
}


void startGame(int width, int height)
{
     int j;
     int ulx, uly;
     
     /* Initialize random number generator. */
     srand((unsigned)time(NULL));
     
     /* Init screen variables. */
     x_wid = width;
     y_hi = height;
     backColor = getpixel(screen, x_wid/2, y_hi/2);
     
     /* Init mouse variables. */
     /* Moves. */
     mx = mouse_x;
     my = mouse_y;
     pmx = mx;
     pmy = my;
     
     /* Init screen objects. */
     
     
}


void endGame(void)
{
   int j;
   
   /* Release resources. */
   
   
   /* Shut down allegro. */
   allegro_exit();
}


void setKeyActionFlags(void)
{
     static int spaceBarDelay = 0;
     
     if (key[KEY_UP]) {
        kUp = TRUE;
     }
     else {
        kUp = FALSE;
     }
     
     if (key[KEY_DOWN]) {
        kDown = TRUE;
     }
     else {
        kDown = FALSE;
     }
     
     if (key[KEY_RIGHT]) {
        kRight = TRUE;
     }
     else {
        kRight = FALSE;
     }
     
     if (key[KEY_LEFT]) {
        kLeft = TRUE;
     }
     else {
        kLeft = FALSE;
     }
     
     if (key[KEY_SPACE]) {
        if (spaceBarDelay%DELAY == 0) {
           kSpace = TRUE;
           spaceBarDelay++;
        }
        else {
           kSpace = FALSE;
           spaceBarDelay++;
        }
     }
     else {
        kSpace = FALSE;
        spaceBarDelay++;
     }
}


void setMouseClickActionFlags(void)
{
     if (mouse_b & 1) {
        mouseLeftClick = TRUE;
        //printf("Left mouse button! \n");
     }
     else {
        mouseLeftClick = FALSE;
     }
          
     if (mouse_b & 2) {
        mouseRightClick = TRUE;
        //printf("Right mouse button! \n");
     }
     else {
        mouseRightClick = FALSE;
     }
}


void setMouseMovementActionFlags(void)
{
     int m_x_diff, m_y_diff;
     
     pmx  = mx;
     pmy = my;
     mx = mouse_x;
     my = mouse_y;
     
     m_x_diff = mx - pmx;
     m_y_diff = my - pmy;
     
     if ((m_x_diff != 0) || (m_y_diff != 0)) {
        mouseMove = TRUE;
        //printf("mouse moved \n");
     }
     else {
        mouseMove = FALSE;
     }
}
     
