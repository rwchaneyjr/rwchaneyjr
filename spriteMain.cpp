#include <cstdlib>
#include <iostream>
#include <allegro.h>
#include <time.h>

using namespace std;

/* Defines. */
#define SCR_WID 800
#define SCR_HI 600
#define PBOX_WID 300
#define PBOX_HI 300
#define BOX_WIDTH 20
#define MAX_BALL_SIZE 30
#define NUM_BALLS 20
#define NUM_BULLETS 20
#define BULLET_RADIUS 3
#define DELAY 20

#define SPACE_X 600
#define SPACE_Y 400

#define COAST 0
#define THRUST 1
#define RETRO -1
#define MAX_VEL 3
#define LEFT -2
#define RIGHT 2

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


/* Game variables. */
BITMAP *pandoraBox = NULL;

/* Classes used in game. */
class boxOBalls
{
   int height, width;
   int nBalls;
   int ulx, uly;
   
   public : void init(int w, int h)
   {
      width = w;
      height = h;
      
      /* Calculate starting point for upper left corner of box. */
      ulx = 0;
      uly = 0;
      
      /* Draw the frame. */
      drawFrame();   
   }
   
   void drawFrame(void)
   {
      /* Draw verticle and horizontal recangles to bound box. */
      /* Top and bottom. */
     rectfill(pandoraBox, ulx, uly, ulx + width, uly + BOX_WIDTH, blue);
     rectfill(pandoraBox, ulx, uly + (height - BOX_WIDTH), ulx + width, uly + height, blue);
     /* Sides. */
     rectfill(pandoraBox, ulx, uly, ulx + BOX_WIDTH, uly + height, blue);
     rectfill(pandoraBox, ulx + (width - BOX_WIDTH), uly, ulx + width, uly + height, blue);
   }
   
   void clearBox(void)
   {
      clear_to_color(pandoraBox, backColor);
      drawFrame();
   }
   
};


class ball {
   int bw, bh;
   int x, y, px, py;
   int radius, spriteSize;
   int xvel, yvel;
   BITMAP *bigBall /*, *eraseBall*/;
   
   public : void init(int w, int h)
   {
      /* Set bound int box size. */
      bw = w;
      bh = h;
      
      /* Set initial size. */
      radius = rand()%MAX_BALL_SIZE;
      spriteSize = 2*radius + 4;
      
      /* Make the ball and erase bitmaps. */
      bigBall = create_bitmap(spriteSize, spriteSize);
      //eraseBall = create_bitmap(spriteSize, spriteSize);
      
      /* Draw the ball. */
      clear_to_color(bigBall, pink);
      circlefill(bigBall, spriteSize/2, spriteSize/2, radius, red);
      
      /* Fill erase bitmap with background color. */
      //clear_to_color(eraseBall, pink);
      //circlefill(eraseBall, spriteSize/2, spriteSize/2, radius+1, backColor);
      
      /* Set location of ball, based on upper left corner of sprite. */
      x = rand()%w;
      if (x <= BOX_WIDTH) x = BOX_WIDTH+1;
      if ((x+spriteSize) >= (w - BOX_WIDTH)) x = w - spriteSize - BOX_WIDTH;
      
      y = rand()%h;
      if (y <= BOX_WIDTH) y = BOX_WIDTH+1;
      if ((y+spriteSize) > (h - BOX_WIDTH)) y = h - spriteSize - BOX_WIDTH;
      
      /* Set previous x and y positions. */
      px = x;
      py = y;
      
      /* Set velocity. */
      xvel = rand()%10;
      yvel = rand()%10;
      
   }
   
   public: void offBall(void)
   {
      destroy_bitmap(bigBall);
      //destroy_bitmap(eraseBall);
   }
   
   public : void drawBall(void)
   {
      /* We leave this code to show difference in sprites and bitmaps. */
      /*
      blit(eraseBall,pandoraBox,0,0,px,py, spriteSize, spriteSize);
      blit(bigBall,pandoraBox,0,0,x,y, spriteSize, spriteSize);
      */
      
      //draw_sprite(pandoraBox, eraseBall, px, py);
      draw_sprite(pandoraBox, bigBall, x, y);
      
      /* Update previous positions. */
      px = x;
      py = y;
   }
   
   public : void moveMe(void)
   {
      int xL, xR, yT, yB;
      
      x = x + xvel;
      y = y + yvel;
      
      xL = x;
      xR = x + spriteSize;
      yT = y;
      yB = y + spriteSize;
      if (xL <= BOX_WIDTH) {
         x = BOX_WIDTH+1;    
         xvel = -1 * xvel;
      }
      if (xR >= (bw - BOX_WIDTH)) {
         x = bw - BOX_WIDTH - spriteSize;    
         xvel = -1 * xvel;
      }
      if (yT <= BOX_WIDTH) {
         y = BOX_WIDTH+1;
         yvel = -1 * yvel;
      }
      if (yB >= (bh - BOX_WIDTH)){
         y = bh - BOX_WIDTH - spriteSize;    
         yvel = -1 * yvel;
      }
   }       
};


class bullet {
   int x, y, px, py;
   int heading;
   int radius, spriteSize;
   int vel;
   public : char isAlive;
   BITMAP *bigBullet, *eraseBullet;
   
   public : void init(int r, int color)
   {
      /* Set initial size. */
      radius = r;
      spriteSize = 2*radius + 4;
      
      /* Make the ball and erase bitmaps. */
      bigBullet = create_bitmap(spriteSize, spriteSize);
      eraseBullet = create_bitmap(spriteSize, spriteSize);
      
      /* Draw the ball. */
      clear_to_color(bigBullet, pink);
      circle(bigBullet, spriteSize/2, spriteSize/2, radius, color);
      
      /* Fill erase bitmap with background color. */
      clear_to_color(eraseBullet, pink);
      circlefill(eraseBullet, spriteSize/2, spriteSize/2, radius+1, backColor);
      
      /* Set live flag, this flag is TRUE when bullet is shot. */
      isAlive = FALSE;
      
      /* Set bullet velocity. */
      vel = (int)(4 * MAX_VEL);
   }
   
   public : void shutdown(void)
   {
      destroy_bitmap(bigBullet);
      destroy_bitmap(eraseBullet);
   }
   
   public : char isShot(void)
   {
      return isAlive;
   }
   
   public : void shoot(int init_x, int init_y, int init_head)
   {
      unsigned char perp;
      int pAngFix;
      
      //x = init_x;
      //y = init_y;
      
      /* Find a perpidicular angle to the heading. */
      perp = init_head;
      pAngFix = itofix((int)perp);
      
      /* Estimate where the center of the sprite is .*/
      /* 29 is the approximate with of the sprite. */
      x = init_x + (int)(fixtof(fixcos(pAngFix))*29);
      y = init_y + (int)(fixtof(fixsin(pAngFix))*29);
     
      px = x;
      py = y;
      heading = init_head;
      
      isAlive = TRUE;
      
      printf("shoot: x, y, heading = %d %d %d \n", x, y, heading);
   }
   
   public : void drawBullet(void)
   {
      int angFix;
      
      if (isAlive) {
         /* Here, we subtract 64 (90 degrees) so that the degrees from math 
         fixed point math and screen coordinates line up. */
         angFix = itofix((int)(heading-64));
         x = x + (int)(fixtof(fixcos(angFix))*vel);
         y = y + (int)(fixtof(fixsin(angFix))*vel);
         
         if (((x <=0)|| (x >= SCR_WID)) || ((y <= 0) || (y >= (SCR_HI - 20)))) {
            isAlive = FALSE;
            draw_sprite(screen, eraseBullet, px, py);
         }
         else { 
            draw_sprite(screen, eraseBullet, px, py);
            draw_sprite(screen, bigBullet, x, y);
          
            /* Update previous positions. */
            px = x;
            py = y;
         }
      }
   }   
};


class spaceMe {
   public  : int x, y ; 
   int px, py;
   int wid, hi;
   int vel;
   public : unsigned char heading;
   unsigned char phead;
  
   public : char drawShip;
   
   BITMAP *spaceship, *eraseShip;
   
   public : void init(char *filename, int xpos, int ypos)
   {
      /* Get the spaceship bitmap. */
      spaceship = NULL;
      spaceship = load_bitmap(filename, NULL);
      
      wid = spaceship->w;
      hi = spaceship->h;
      
      /* Make a bit map the same size and fill it with background. */
      eraseShip = create_bitmap(wid, hi);
      clear_to_color(eraseShip, backColor);
      
      /* Give the ship a postion. */
      x = xpos;
      y = ypos;
      px = x;
      py = y;
      
      /* Give initial velocity and heading. */
      vel = 0;
      heading = 0;
      phead = heading;
   }
   
   public : void drawMe(void)
   {
      rotate_sprite(screen, eraseShip, px, py, itofix((int)phead));
      rotate_sprite(screen, spaceship, x, y, itofix((int)heading));
      
      /* Update previous positions. */
      px = x;
      py = y;
      
      /* Update previous headings. */
      phead = heading;
      
      if (vel == 0) {
         drawShip = FALSE;
      }
   }
   
   
   public : void move(char mode)
   {
          int angFix;
          
          switch (mode) 
          {
             case COAST :
                break;
             case THRUST :
                vel = vel + THRUST ;
                if (vel > MAX_VEL) {
                   vel = MAX_VEL;
                }
                break;
          
             case RETRO :
                vel = vel+RETRO;
                if (vel < 0) {
                   vel = 0;
                }
                break;
             case LEFT :
                heading = heading - 1;
                
                break;
             case RIGHT :
                heading = heading + 1;
                
                break;
          }
          
          /* Using fixed trig, calculate the x and y displacements based on 
             the ships velocity. */
          /* Here, we subtract 64 (90 degrees) so that the degrees from math 
             fixed point math and screen coordinates line up. */
          angFix = itofix((int)(heading-64));
          x = x + (int)(fixtof(fixcos(angFix))*vel);
          y = y + (int)(fixtof(fixsin(angFix))*vel);
          printf("%f   ",angFix);
          /* Don't draw outside of screen. */
          if (((x <=0)|| (x >= (SCR_WID - 60))) || ((y <= 0) || (y >= (SCR_HI-80)))) {
             x = px;
             y = py;
          }
          
          if (vel > 0) {
             drawShip = TRUE;
          }
          
          if (heading != phead) {
             drawShip = TRUE;
          }       
   }
             
                
      
      
   public : void shutdown(void)
   {
      destroy_bitmap(spaceship);
      destroy_bitmap(eraseShip);
   }
};
      
      

/* Game variables. */
boxOBalls pandora;
ball balls[NUM_BALLS];
spaceMe ufo;
bullet bullets[NUM_BULLETS];

/* Routines called. */
void startAllegro(int width, int height);
void startGame(int width, int height, int p_wid, int p_hi);
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
    startGame(SCR_WID, SCR_HI, PBOX_WID, PBOX_HI);
    
    ulx = SCR_WID/2 - PBOX_WID/2;
    uly = SCR_HI/2 - PBOX_HI/2;
    
    do {
        /* Get inputs. */
        setKeyActionFlags();
        setMouseClickActionFlags();
        setMouseMovementActionFlags();
        
        /* Calculate new frame. */
        
        
        /* Process effect of inputs. */
        /* Ship movement. */
        if (kUp) {
           printf("kUp \n");
           ufo.move(THRUST);
        }
        else if (kDown) {
           printf("kDown \n");
           ufo.move(RETRO);
        }
        else if (kLeft) {
           ufo.move(LEFT);
        }
        else if (kRight) {
           ufo.move(RIGHT);
        }
        else {
           ufo.move(COAST);
        }
        
        /* Ship Weapons. */
        if (kSpace) {
           /* Find a free bullet. */
           j = 0;
           found = FALSE;
           search = TRUE;
           while(search) {
              if (bullets[j].isAlive) {
                 j = j+1;
              }
              else {
                 found = TRUE;
                 search = FALSE;
              }
              if (j == NUM_BULLETS) {
                 search = FALSE;
              }
           } /* End while. */
           if (found) {
              bullets[j].shoot(ufo.x, ufo.y, ufo.heading);
              ufo.drawShip = TRUE;
           }
        }
        
        pandora.clearBox();
        
        /* Process non-input effects. */
        /* Bouncing balls. */
        for(j=0;j<NUM_BALLS;j++) {
           balls[j].moveMe();
           balls[j].drawBall();
        }
        
        /* Draw. */
        blit(pandoraBox, screen, 0, 0, ulx, uly, PBOX_WID, PBOX_HI);
        rest(1);
        
        /* Bullets. */
        for(j=0;j<NUM_BULLETS;j++) {
           bullets[j].drawBullet();
        }
        
        if (ufo.drawShip) {
           ufo.drawMe();
        }
        
        /* Set rest for about 50 frame refresh. */
        rest(20);
        
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


void startGame(int width, int height, int p_wid, int p_hi)
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
     pandoraBox = create_bitmap(p_wid, p_hi);
     
     /* Box to contain bouncing balls. */
     pandora.init(p_wid, p_hi);
     
     /* Bouncing balls. */
     for(j=0;j<NUM_BALLS;j++) {
        balls[j].init(p_wid, p_hi);
        balls[j].drawBall();
     }
     
     /* Put pandora on the screen. */
     ulx = width/2 - p_wid/2;
     uly = height/2 - p_hi/2;
     blit(pandoraBox,screen,0,0,ulx,uly,p_wid, p_hi);
     
     /* Set up the spaceship. */
     ufo.init("spaceship.bmp", SPACE_X, SPACE_Y);
     ufo.drawShip = TRUE;
     
     /* Bullet initialization. */
     for(j=0;j<NUM_BULLETS;j++) {
        bullets[j].init(BULLET_RADIUS, makecol(0, 255, 0));
     }
}


void endGame(void)
{
   int j;
   
   /* Release resources. */
   destroy_bitmap(pandoraBox);
   
   /* Get rid of the balls. */
   for(j=0;j<NUM_BALLS;j++) {
      balls[j].offBall();
   }
   
   /* Get rid of the ship. */
   ufo.shutdown();
   
   /* Loose the bullets. */
   for(j=0;j<NUM_BULLETS;j++) {
      bullets[j].shutdown();
   }
   
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
     
