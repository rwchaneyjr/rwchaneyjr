
#include <allegro.h>

#ifndef MAIN
#define EXTERN extern
#else 
#define EXTERN
#endif
EXTERN SAMPLE *sample[2];
EXTERN BITMAP *scene,*temp;
EXTERN char  tf,tf1,tf2,tf3,tf4,level0,level1,level2,d,e,a1,a2,a3,a4,b1,b2,b3,b4,end;
EXTERN int Score,curframe, framedelay, framecount ,curframe1,xb,framecount1, framedelay1,sx,xoffset,yoffset,sy;
EXTERN int ya,yb,yc,yd,xc, x,y,y1,y2,y3,y4, n, cur,tempx,tempy, tempX,tempY,collideX,collideY, cur1;
EXTERN BITMAP *skeeterimg[6];
EXTERN BITMAP *beeimg[6];
EXTERN BITMAP *dragonimg[6];
EXTERN BITMAP *explosionimg[6];
EXTERN MIDI *music;
