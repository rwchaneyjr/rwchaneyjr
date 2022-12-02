#include <cstdlib>
#include <iostream>
#include <allegro.h>
#include <stdio.h>
#include <time.h>



/* Define game board size. */
#define GSIZE 10
#define BWIDTH 20

/* Tank defines. */
#define TSPEED 1
#define BULLIT_SPEED 1
#define BULLIT_LENGTH 4

/* Define some colors. */
#define PINK  makecol(255, 0, 255)
#define GREEN  makecol(0, 255, 0)
#define L_GREEN  makecol(0, 215, 55)
#define BLUE makecol(0, 0, 255)
#define YELLOW  makecol(255, 255, 0)
#define RED  makecol(255, 0, 0)
#define WHITE  makecol(255, 255, 255)
#define BLACK  makecol(0, 0, 0)

#define ORANGE 6

/* Define a Tank. */
int leftTreadNS[4] = {-10, -10, -6, 10};
int leftTreadEW[4] = {-10, -10, 10, -6};
int bodyNSEW[4] = {-6, -6, 6, 6};
int rightTreadNS[4] = {6, -10, 10, 10};
int rightTreadEW[4] = {-10, 6, 10, 10};
int turretNSEW[3] = {0, 0, 4};
int gunN[4] = {-2, -12, 2, 2};
int gunE[4] = {2, 2, 12, -2};
int gunW[4] = {-12, -2, -2, 2};
int gunS[4] = {-2, 2, 2, 12};

struct TANK {
       int x, y;
       int px, py;
       int color;
       char draw;
       char head;
       char phead;
};


/* Subroutine Prototypes. */
void loadPlayingBoard(char *filename);
void drawPlayingBoard(int borderColor, int color);
void showBoard(void);
void drawTank(int x, int y, int head, int color);
TANK initTank(int x, int, char head, int color);
char checkForObstacle(int tx, int ty, char head);
void eraseTank(int x, int y);
void shootEm(int x, int y, char head, int tx, int ty);
void loadRandom(BITMAP *map, int nrows, int ncols, int color, int percentFill);
void explodeMe(int x, int y);
void puff(int x, int y);
void eatN(int x, int y);
void explodeTank(int x, int y, int color);


/* Global variables. */
char board[GSIZE][GSIZE];
int backColor, bulletColor;

/* Explosion effect bitmaps */
BITMAP *clearMe = NULL;
BITMAP *ex01 = NULL;
BITMAP *ex02 = NULL;
BITMAP *ex03 = NULL;
BITMAP *eat = NULL;
BITMAP *eatC = NULL;

int main(int argc, char *argv[])
{
    TANK X, O;
    
    printf("Welcome to dumb game! \n");
    
    printf("\n");
    printf("loading playing board \n");
    
    /* Initialize Allegro. */
    allegro_init();     
    
    /* Set the resolution to 640 by 480 with SAFE autodetection. */
    set_gfx_mode(GFX_SAFE, 640, 480, 0, 0);

    /* Installing the keyboard handler. */
    install_keyboard(); 
    
    /* Get the background color for later use. */
    backColor = getpixel(screen, 320, 240);
    
    /* Load initial playing board. */
    loadPlayingBoard("boardMe.txt");
    showBoard();
    
    /* Draw the board on to the screen. */
    drawPlayingBoard(BLUE, L_GREEN);
    
    /* Initialize tanks. */
    X = initTank(100, 400, 'n', RED);
    O = initTank(500, 100, 's', YELLOW);
    
    /* Create explosion effect bitmaps. */
    clearMe = create_bitmap(15,15);
    ex01 = create_bitmap(7, 7);
    ex02 = create_bitmap(10, 10);
    ex03 = create_bitmap(15, 15);
    eat = create_bitmap(15, 15);
    eatC = create_bitmap(7, 7);
    
    /* Initialize random number generator. */
	srand( (unsigned)time( NULL ) );
    
    /* Load the explosion fx bitmaps. */
    loadRandom(clearMe, 15, 15, backColor, 100);
    loadRandom(ex01, 7, 7, YELLOW, 70);
    loadRandom(ex02, 10, 10, ORANGE, 60);
    loadRandom(ex03, 15, 15, RED, 50);
    loadRandom(eat, 15, 15, L_GREEN, 50);
    loadRandom(eatC, 7, 7, backColor, 100);
    
    /* Main game loop. */
    do{	
        /* X tank keys. */
        if (key[KEY_UP]) {
           X.py = X.y;
           X.phead = X.head;
           
           X.head = 'n';
           X.y = X.y - TSPEED;
           
           if (checkForObstacle(X.x, X.y, 'n')) {
              X.draw = FALSE;
              X.y = X.py;
           }
           else {
              X.draw = TRUE;
           }
        }
        
        if (key[KEY_DOWN]) {
           X.py = X.y;
           X.phead = X.head;
           
           X.head = 's';
           X.y = X.y + TSPEED;
           
           if (checkForObstacle(X.x, X.y, 's')) {
              X.draw = FALSE;
              X.y = X.py;
           }
           else {
              X.draw = TRUE;
           }
        }
        
        if (key[KEY_RIGHT]) {
           X.px = X.x;
           X.phead = X.head;
           
           X.head = 'e';
           X.x = X.x + TSPEED;
           
           if (checkForObstacle(X.x, X.y, 'e')) {
              X.draw = FALSE;
              X.x = X.px;
           }
           else {
              X.draw = TRUE;
           }
        }
        
        if (key[KEY_LEFT]) {
           X.px = X.x;
           X.phead = X.head;
           
           X.head = 'w';
           X.x = X.x - TSPEED;
           
           if (checkForObstacle(X.x, X.y, 'w')) {
              X.draw = FALSE;
              X.x = X.px;
           }
           else {
              X.draw = TRUE;
           }
        }
        
        if (key[KEY_SPACE]) {
           printf("Tank X says 'I kill you ! ' \n");
           shootEm(X.x, X.y, X.head, O.x, O.y);
        }
        
        /* O tank keys. */
        if (key[KEY_8_PAD]) {
           O.py = O.y;
           O.phead = O.head;
           
           O.head = 'n';
           O.y = O.y - TSPEED;
           O.draw = TRUE;
        }
        
        if (key[KEY_2_PAD]) {
           O.py = O.y;
           O.phead = O.head;
           
           O.head = 's';
           O.y = O.y + TSPEED;
           O.draw = TRUE;
        }
        
        if (key[KEY_6_PAD]) {
           O.px = O.x;
           O.phead = O.head;
           
           O.head = 'e';
           O.x = O.x + TSPEED;
           O.draw = TRUE;
        }
        
        if (key[KEY_4_PAD]) {
           O.px = O.x;
           O.phead = O.head;
           
           O.head = 'w';
           O.x = O.x - TSPEED;
           O.draw = TRUE;
        }
        
        /* Update tank positions on screen. */
        if (X.draw) {
           eraseTank(X.px, X.py);
           drawTank(X.x, X.y, X.head, X.color);
           X.draw = FALSE;
        }
        
        if (O.draw) {
           eraseTank(O.px, O.py);
           drawTank(O.x, O.y, O.head, O.color);
           O.draw = FALSE;
        }
        rest(5);
    } while(!key[KEY_ESC]);
    
    
    printf("Game over! \n");
    
    return EXIT_SUCCESS;
}
END_OF_MAIN()


void shootEm(int x, int y, char head, int tx, int ty)
{
     char hit = FALSE;
     int bx, by, pbx, pby;
     int b;
     int index = 0;
     
     if (head == 'n') {
              bx = x;
              by = y-15; /* Gun length + 1 */
              
              while(!hit) {
                 b = getpixel(screen, bx, by);
                 if (b == backColor) {
                       /* Draw new bullit. */
                       putpixel(screen, bx, by, RED);
                       putpixel(screen, bx-1,by + 1, RED);
                       putpixel(screen, bx+1, by + 1, RED);
                       if (index >= BULLIT_LENGTH) {
                          putpixel(screen, bx, by + BULLIT_LENGTH, backColor);
                          putpixel(screen, bx-1,by + 1+ BULLIT_LENGTH, backColor);
                          putpixel(screen, bx+1, by + 1+ BULLIT_LENGTH, backColor);
                       }
                       by = by - BULLIT_SPEED;
                       index++;
                 }
                 else {
                      if (b == L_GREEN) {
                            explodeMe(bx, by);
                            eatN(bx, by);
                      }
                      else if (b == YELLOW) {
                           explodeMe(tx, ty);
                           rest(100);
                           explodeTank(tx, ty, YELLOW);
                      }
                      else {
                         puff(bx, by);
                      }
                      hit = TRUE;
                 }
                 rest(5);
              } /* End while !hit. */
     } /* End head = 'n' */
}


void explodeTank(int x, int y, int color)
{
     eraseTank(x, y+4);
     eraseTank(x, y-4);
     rect(screen, leftTreadNS[0]+x,leftTreadNS[1]+y,leftTreadNS[2]+x,leftTreadNS[3]+y, color);
     rect(screen, bodyNSEW[0]+x+1,bodyNSEW[1]+y-1,bodyNSEW[2]+x-1,bodyNSEW[3]+y+1, color);
     rect(screen, rightTreadEW[0]+x,rightTreadEW[1]+y,rightTreadEW[2]+x,rightTreadEW[3]+y, color);
     circle(screen, turretNSEW[0]+x, turretNSEW[1]+y+2, turretNSEW[2], color);
     rect(screen, gunW[0]+x,gunW[1]+y,gunW[2]+x,gunW[3]+y, color);
}


void explodeMe(int x, int y)
{
     blit(clearMe,screen,0,0,x-7,y+1,15,15);
     blit(ex01, screen, 0, 0, x-3, y+1, 7, 7);
     rest(100);
     blit(ex02, screen, 0, 0, x-5, y+1, 10, 10);
     if (getpixel(screen, x, y - 15 + 1) != backColor) {
        blit(eat,screen,0,0,x-7,y-15+1,15,15);
     }
     rest(150);
     blit(ex03, screen, 0, 0, x-7, y+1, 15, 15);
     rest(100);
     blit(ex02, screen, 0, 0, x-5, y+1, 10, 10);
     rest(100);
     blit(clearMe,screen,0,0,x-7,y+1,15,15);
}


void puff(int x, int y)
{
     blit(clearMe,screen,0,0,x-7,y+1,15,15);
     blit(ex01, screen, 0, 0, x-3, y+1, 7, 7);
     rest(100);
     blit(ex02, screen, 0, 0, x-5, y+1, 10, 10);
     rest(150);
     blit(ex03, screen, 0, 0, x-7, y+1, 15, 15);
     rest(100);
     blit(ex02, screen, 0, 0, x-5, y+1, 10, 10);
     rest(100);
     blit(clearMe,screen,0,0,x-7,y+1,15,15);
}


void eatN(int x, int y)
{
     blit(eatC,screen,0,0,x-3,y-7+1, 7, 7);
}
     


void loadRandom(BITMAP *map, int nrows, int ncols, int color, int percentFill) 
{
     int j, k;
     
     for(j=0;j<nrows;j++){
        for(k=0;k<ncols;k++) {
            if ((rand()%100) < percentFill) {
               putpixel(map, k, j, color);
            }
            else {
               putpixel(map, k, j, backColor);
            }
        }
     }
}
           
     
char checkForObstacle(int tx, int ty, char head) 
{
     char blocked = FALSE;
     int j;
     int x0, x1, y0, y1;
     int b;
     
     if ((head == 'n')|| (head == 's')) {
         if (head == 'n') {
            x0 = tx - 10;
            x1 = tx + 10;
            y0 = ty - 15;
         }
         else if (head == 's') {
            x0 = tx - 10;
            x1 = tx + 10;
            y0 = ty + 15;
         }
     
         for(j=x0;j<=x1;j++) {
            b = getpixel(screen, j, y0);
            if (b != backColor) {
               blocked = TRUE;
            } 
         }
     }
     else {
          if (head == 'e') {
            x0 = tx + 15;
            y0 = ty - 10;
            y1 = ty + 10;
         }
         else if (head == 'w') {
            x0 = tx - 15;
            y0 = ty - 10;
            y1 = ty + 10;
         }
     
         for(j=y0;j<=y1;j++) {
            b = getpixel(screen, x0, j);
            if (b != backColor) {
               blocked = TRUE;
            } 
         }
     }

     
     return blocked;
}
              
     
     
     

TANK initTank(int x, int y, char head, int color)
{
     TANK newTank;
     
     newTank.x = x;
     newTank.y = y;
     newTank.px = x;
     newTank.py =y;
     newTank.head = head;
     newTank.color = color;
     newTank.draw = TRUE;
     newTank.head = head;
     
     return newTank;
}

void drawTank(int x, int y, int head, int color)
{
     /* Tank primitives. */
     /*
        int leftTreadNS[4] = {-10, -10, -6, 10};
        int leftTreadEW[4] = {-10, -10, 10, -6};
        int bodyNSEW[4] = {-6, -6, 6, 6};
        int rightTreadNS[4] = {6, -10, 10, 10};
        int rightTreadEW[4] = {-10, 6, 10, 10};
        int turretNSEW[3] = {0, 0, 4};
        int gunN[4] = {-2, -12, 2, 2};
        int gunE[4] = {2, 2, 12, -2};
        int gunW[4] = {-12, -2, -2, 2};
        int gunS[4] = {-2, 2, 2, 12};
     */
     
     if (head == 'n') {
         rect(screen, leftTreadNS[0]+x,leftTreadNS[1]+y,leftTreadNS[2]+x,leftTreadNS[3]+y, color);
         rect(screen, bodyNSEW[0]+x,bodyNSEW[1]+y,bodyNSEW[2]+x,bodyNSEW[3]+y, color);
         rect(screen, rightTreadNS[0]+x,rightTreadNS[1]+y,rightTreadNS[2]+x,rightTreadNS[3]+y, color);
         circle(screen, turretNSEW[0]+x, turretNSEW[1]+y, turretNSEW[2], color);
         rect(screen, gunN[0]+x,gunN[1]+y,gunN[2]+x,gunN[3]+y, color);
     }
     else if (head == 's') {
         rect(screen, leftTreadNS[0]+x,leftTreadNS[1]+y,leftTreadNS[2]+x,leftTreadNS[3]+y, color);
         rect(screen, bodyNSEW[0]+x,bodyNSEW[1]+y,bodyNSEW[2]+x,bodyNSEW[3]+y, color);
         rect(screen, rightTreadNS[0]+x,rightTreadNS[1]+y,rightTreadNS[2]+x,rightTreadNS[3]+y, color);
         circle(screen, turretNSEW[0]+x, turretNSEW[1]+y, turretNSEW[2], color);
         rect(screen, gunS[0]+x,gunS[1]+y,gunS[2]+x,gunS[3]+y, color);
     }
     else if (head == 'e') {
         rect(screen, leftTreadEW[0]+x,leftTreadEW[1]+y,leftTreadEW[2]+x,leftTreadEW[3]+y, color);
         rect(screen, bodyNSEW[0]+x,bodyNSEW[1]+y,bodyNSEW[2]+x,bodyNSEW[3]+y, color);
         rect(screen, rightTreadEW[0]+x,rightTreadEW[1]+y,rightTreadEW[2]+x,rightTreadEW[3]+y, color);
         circle(screen, turretNSEW[0]+x, turretNSEW[1]+y, turretNSEW[2], color);
         rect(screen, gunE[0]+x,gunE[1]+y,gunE[2]+x,gunE[3]+y, color);
     }
     else if (head == 'w') {
         rect(screen, leftTreadEW[0]+x,leftTreadEW[1]+y,leftTreadEW[2]+x,leftTreadEW[3]+y, color);
         rect(screen, bodyNSEW[0]+x,bodyNSEW[1]+y,bodyNSEW[2]+x,bodyNSEW[3]+y, color);
         rect(screen, rightTreadEW[0]+x,rightTreadEW[1]+y,rightTreadEW[2]+x,rightTreadEW[3]+y, color);
         circle(screen, turretNSEW[0]+x, turretNSEW[1]+y, turretNSEW[2], color);
         rect(screen, gunW[0]+x,gunW[1]+y,gunW[2]+x,gunW[3]+y, color);
     }
          
}


void eraseTank(int x, int y)
{
     rectfill(screen, x - 13, y - 13, x + 13, y + 13, backColor);
}
     
     


void loadPlayingBoard(char *filename)
{
     FILE *in, *out;
     int j, k;
     int num;
     
     printf("filename = %s \n", filename);
     in = fopen(filename, "r");
     
     if (in == NULL) {
        printf("Trouble opening file: %s \n", filename);
        system("PAUSE");
        exit(0);
     }
     
     for(j=0;j<GSIZE;j++) {
         for(k=0;k<GSIZE;k++) {
            fscanf(in, "%d ", &num);
            printf("num = %d \n", num);
            board[j][k] = num;
         }
     }
     fclose(in);
}


void showBoard(void)
{
     int j, k;
     
     printf("Game board...\n\n");
     for(j=0;j<GSIZE;j++) {
         for(k=0;k<GSIZE;k++) {
            printf("%d ", board[j][k]);
         }
         printf("\n");
     }
     printf("\n");
}


void drawPlayingBoard(int borderColor, int color)
{
     int j, k;
     int tlx, tly, lrx, lry;
     int h, w;
     
     w = (640 - BWIDTH*2)/GSIZE;
     h = (480 - BWIDTH*2)/GSIZE;
     
     /* Draw border around playing board. */
     /* Top and bottom. */
     rectfill(screen, 0, 0, 640, BWIDTH, borderColor);
     rectfill(screen, 0, (480 - BWIDTH), 640, 480, borderColor);
     /* Sides. */
     rectfill(screen, 0, 0, BWIDTH, 480, borderColor);
     rectfill(screen, 640 - BWIDTH, 0, 640, 480, borderColor);
     
     /* Make some slots so agents can move from one side to the other. */
     rectfill(screen, 0, 220, BWIDTH, 260, backColor);
     rectfill(screen, 620, 220, 640, 260, backColor);
     
     for(j=0;j<GSIZE;j++){ 
        for(k=0;k<GSIZE;k++){
           if (board[j][k] != 0) {
              tlx = BWIDTH + (k * w);
              tly = BWIDTH + (j * h);
              lrx = tlx + w;
              lry = tly + h;
              rectfill(screen, tlx, tly, lrx, lry, color);
           }
        }
     }
}
        
                 
           
