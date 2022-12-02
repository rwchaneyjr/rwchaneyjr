#include <allegro.h>
#include "GLOBALS.h"
#include <stdio.h>
#include "mappyal.h"

BITMAP *grabframe(BITMAP *source,int width, int height, int startx, int starty, int columns, int frame)
{
       BITMAP *temp = create_bitmap(width,height);
       int x = startx + (frame%columns)*width;
       int y = starty + (frame/columns)*height;
       blit(source,temp,x,y,0,0,width,height);
       return temp;
}

int anibeeskeeter(void)
{  
   
   
        xb -= 5;
       
       if (xb <  0 )
          xb = 640;

		//update the frame
		if (framecount1++ >framedelay1)
		{
			framecount = 6;
			curframe1++;
			if (curframe1 >5)
				curframe1 = 0;
        }
        if(x <6565)
        {
        if((key[KEY_SPACE])&& ((y+38 <= 154) && ( y+38 >=132))&&(xb-20 >sx + 120)&&(xb+20 <= sx +205))
        {
        rest(20);
       
        a1 = true;
        
        }
        else if(!a1)
        {
        if (ya == 120) 
          draw_sprite(scene,beeimg[curframe1],xb-20,ya);    
        }
        
       // rect(scene,xb-20,132,xb+20,154,makecol(255,0,255));
       if((key[KEY_SPACE])&& ((y+38 <= 410) && ( y+38 >=390))&&(xb + 10 > sx + 120)&&(xb+40 <= sx + 205))
        {rest(20);
        
        a2 = true;
         
        }
        else if (!a2)
        {
          if (yb ==380)   
          draw_sprite_h_flip(scene,skeeterimg[curframe1],xb,yb);  
         }
        
        //rect(scene,xb+10,390,xb+40,410,makecol(255,255,255));
        if((key[KEY_SPACE])&& ((y+38 <= 354)&& ( y+38 >=332))&& (xb - 100 > sx + 120)&&(xb -60 < sx +205))
        {rest(20);
        
        
         a3 = true;
         
        }
        else if (!a3)
        {
         if(yc == 320)    
            draw_sprite(scene,beeimg[curframe1],xb-100,yc);
            
         }
        
        //rect(scene,xb-100,332,xb-60,354,makecol(255,255,255));
        if((key[KEY_SPACE])&& ((y+38 <= 100) && ( y+38 >=80))&& (xb+60>sx + 120)&&(xb + 90 <= sx + 205))
        {rest(20);
        
        a4 = true;
        
        }
        else if (!a4)
        {
           if(yd == 70)  
         draw_sprite_h_flip(scene,skeeterimg[curframe1],xb+50,yd);   
         }
        
        //rect(scene,xb+60,80,xb+90,100,makecol(255,255,255));
		
    }
     return curframe1;
       
     }
void dynamicbugfall(void)
{
     
          sample[1] = load_sample("explode.wav");
    

         /* Play the sound, full volume, even balance, original pitch, and looping. */
         int j;
   
        //play_sample(sample[1], 255, 127, 1000, TRUE);

         if(b1)
          {
            for(n = 0; n < 6; n++){
                  rest(1);
           draw_sprite(scene,explosionimg[n],xc-20,y1);
          //sample[1] = load_sample("explode.wav");
          }
        /* Play the sound, full volume, even balance, original pitch, and looping. */
  
         play_sample(sample[1], 255, 127, 1000, FALSE);

         xc = xc -480;  
          
          tf1 = true;
          y1 = 120;
          b1 = false;
         
          
          }
         
         if(b2)
         {  for(n = 0; n < 6; n++){
                  rest(1);
         draw_sprite(scene,explosionimg[n],xc+50,y2-50);
         }
          //sample[1] = load_sample("explode.wav");
    

    /* Play the sound, full volume, even balance, original pitch, and looping. */
  
         play_sample(sample[1], 255, 127, 1000, FALSE);

         
         
           xc = xc -480;    
               
               tf2 = true;
          y2 = 120;
          b2 = false;
          
          }
         
         if(b4)
         {   for(n = 0; n < 6; n++){
                  rest(1);
         draw_sprite(scene,explosionimg[n],xc-100,y4);      
         }
         //sample[1] = load_sample("explode.wav");
    

    /* Play the sound, full volume, even balance, original pitch, and looping. */
   
         play_sample(sample[1], 255, 127, 1000, FALSE);

         
         
                xc = xc - 480; 
                
                tf4 = true;
              y4 =320;
                 b4 = false;
                
         }
         
         if(b3)
         {  for(n = 0; n < 6; n++){
                  rest(1);
         draw_sprite(scene,explosionimg[n],xc,y3+60);
         }
        // sample[1] = load_sample("explode.wav");
    

    /* Play the sound, full volume, even balance, original pitch, and looping. */
    
         play_sample(sample[1], 255, 127, 1000, FALSE);

         
          xc = xc -480;
          
          tf3 = true;
          y3 = 320;
           b3 = false;
           
         }
}         
void staticfall (void)
{
     int j;
      sample[1] = load_sample("explode.wav");
    
        if(a1)
        {
           for(n = 0; n < 6; n++){
                  rest(1);
         draw_sprite(scene,explosionimg[n],xb-20,ya);
         }
    

    /* Play the sound, full volume, even balance, original pitch, and looping. */
   
        play_sample(sample[1], 255, 127, 1000, FALSE);

         
               a1 = false;
          ya = 120;xb = xb -480;
          }
         
         if(a2)
         {   for(n = 0; n < 6; n++){
                  rest(1);
         draw_sprite(scene,explosionimg[n],xb,yb);
         // sample[1] = load_sample("explode.wav");
         }

    /* Play the sound, full volume, even balance, original pitch, and looping. */
  
         play_sample(sample[1], 255, 127, 1000, FALSE);

         
               a2 = false;
          yb = 380;xb = xb -480;
          }
         
         if(a3)
         {
                 for(n = 0; n < 6; n++){
                  rest(1);
         draw_sprite(scene,explosionimg[n],xb-100,yc);
         // sample[1] = load_sample("explode.wav");
         }

    /* Play the sound, full volume, even balance, original pitch, and looping. */
    
        play_sample(sample[1], 255, 127, 1000, FALSE);

        
                a3 = false; 
                yc = 320;xb = xb - 480;
         }
         
         if(a4)
         {
           for(n = 0; n < 6; n++){
                  rest(1);
         draw_sprite(scene,explosionimg[n],xb+50,yd);
         // sample[1] = load_sample("explode.wav");
         }

    /* Play the sound, full volume, even balance, original pitch, and looping. */
   
         play_sample(sample[1], 255, 127, 1000, FALSE);

         
          a4 = false; 
          yd = 70;xb = xb -480;
         }
         
}   
int anidragon (char tf)
     {
              tf = tf;
     
        
            
		//update the frame
		if (framecount++ > framedelay)
	{
			framecount = 0;
			curframe++;
			if (curframe >5)
				curframe = 0;
   }
        if((!key[KEY_RIGHT]) && (!key[KEY_LEFT])){
                             
        draw_sprite_h_flip(scene, dragonimg[curframe], x, y);
       
        }
       
     
       return curframe;
}
char collided1 (void)
{   
    tempx = x;
    tempy = y;
     if((((sx+120))>=(xb-20))&&((sx+120) <= (xb+20)) &&(y+20<=155)&& (y+50>= 135)){//
      	
      return 1;
      }
      
      if ((((sx+120))>= (xb +10))&&(((sx+120))<= (xb +40)) &&(y+20 <= 410)&& (y+40 >=390)){//
      	
      return 1;
      }
      
      if((((sx+120)) >= (xb-100))&&(((sx+120)) <=(xb - 60))&& (y + 20 <= 350) && (y+50 >=330)){//&& 
      	
      return 1;
      }
      
      if((((sx+120)) >= (xb + 60))&&(((sx+120)) <=(xb+90))&& (y+20 <= 100) && (y+40 >= 80)){//
     	
      return 1; 
      }
      else
      return 0;
      
}      


 
  void dragonfall (void)

{  
     d = true;
   
  
    
       y = y + 50;
     
    
    clear_to_color(scene,makecol(0,0,0));
    rest(10);
    draw_sprite(scene,dragonimg[3],sx,y);
    rest(10);
    
  
   }    
 
   

void move (void)
{ 
     int wTile = 208; int hTile = 15;
     int fw = wTile * 32;
      int fh = hTile * 32;
     int INC; 
     INC = 8;
    
       tempX = x;
       tempY = y; 
         
       if (key[KEY_RIGHT]) 
        { 
             tf = true;       
              
        
               
         if (x < (fw - INC - 32)) {
            x = x+INC;
            
              
             if ((x > (5* 32))&&(x < (206 * 32))) {
              
               xoffset = x - (5 * 32);//mapblockwidth);
              
               sx = (5* 32);
               
               
              
              sy = y;
            }
            /* Here we are approaching the right edge of the map. */
            else if (x >= (206 * 32)) {
               sx = x - (20*32);
              
            }
            /* Here we move the sprite only, 
               we are in the first 0 to 480 of the map (left edge). */
            else if (x < 480) {
               sx = x;
            }
            }        
            }
          
         
      /* Left. */
         else if (key[KEY_LEFT]){
           tf = false;
         if (x > INC) {
            x = x-INC;
         
         //draw_sprite(scene,dragonimg[curframe],x,y);
          if ((x > (5 * 32))&&(x < (208 * 32))) {
               xoffset = x - (5 * 32);
               sx = (5 * 32);
               sy = y;
               
            }
            /* Here we are approaching the right edge of the map. */
            else if (x >= (208 * 32)) {
               sx = x - (20*32);
              
            }
            /* Here we move the sprite only, 
               we are in the first 0 to 480 of the map (left edge). */
            else {
               sx = x;
            }
        }
        }

      /* Up. */
         if (key[KEY_UP]) {
         if (y > INC) {
            y = y-INC;
         }
         }
      /* Down. */
         else if (key[KEY_DOWN]) {
         if (y < (fh - INC - 32)) {
            y = y+INC;
         }
      }     
   
}
void drawDragonScroll(BITMAP *b)
   { 
   if (framecount++ > framedelay)
		{
			framecount = 0;
			curframe++;
			if (curframe >5)
				curframe = 0;
    }
      if((!key[KEY_RIGHT])&&(!key[KEY_LEFT])&& (tf))
      draw_sprite_h_flip(scene, dragonimg[curframe], sx, y);
      if (tf)
      draw_sprite_h_flip(scene, dragonimg[curframe], sx, y);
      if(!tf)
      draw_sprite(scene,dragonimg[curframe],sx,y);

}  

 void sky (void)
{
    scene= load_bitmap("background.bmp", NULL);   
    blit(scene,screen,0,0,0,0,640,448);
  
}
void fire (void)
{   int j;
    int n;
j = sx;

if(key[KEY_SPACE])
{ 
     ellipsefill(screen,j+160,y+38,45,5,makecol(255,(rand()%200),0)); 
        
  rest(1);   
     }
     //rect(screen,sx+120,y+32,sx+205,y+42,makecol(255,255,255));
}
char collide2(void)

{ 
     
      if((((sx+120))>=(xc-20))&&((sx+120) <= (xc+20)) &&(y+22<=y1+34)&& (y+54>= y1+12)){//
      return 1;
      // rect(scene,xb-20,132,xb+20,154,makecol(255,0,255)); 
      }
      if ((((sx+120))>= (xc +10)) &&(((sx+120))<= (xc +40))&&(y+22 <= y3+90)&& (y+54 >=y3+70)){//
      	//rect(scene,xb+10,390,xb+40,410,makecol(255,255,255));
      return 1;
      }
      if((((sx+120)) >= (xc-100))&& (((sx+120)) <=(xc - 60))&& (y + 22 <= y4+34) && (y+54 >=y4+12)){//
      	//rect(scene,xb-100,332,xb-60,354,makecol(255,255,255));
      return 1;
      }
      if((((sx+120)) >= (xc + 60))&&(((sx+120)) <=(xc+90))&& (y+22 <=y2-20) && (y+54 >= y2-40)){//
     	//rect(scene,xb+60,80,xb+90,100,makecol(255,255,255));
      return 1; 
      }
      else
      return 0;
      
}      
                                         
void circle (void)
   {    /* Load the wave file. */
   sample[0] = load_sample("bee.wav");
    

    /* Play the sound, full volume, even balance, original pitch, and looping. */
    play_sample(sample[0], 255, 127, 1000, TRUE);
        circlefill(screen,sx+120,y,14,makecol(255,0,255));
        rest(10);
        circlefill(screen,sx+120,y,25,makecol(0,255,0));
        rest(10);
        circlefill(screen,sx+120,y,50,makecol(255,0,0));  
        rest(10); 
        circlefill(screen,sx+120,y,70,makecol(255,255,255));  
                                           
}                                          
  void level1A (void)
  {      xc = xc -7;
         if (xc <0)
         xc = 640;  
         if (framecount++ > framedelay)
		{
			framecount = 0;
			curframe++;
			if (curframe >5)
				curframe = 0;
    }    if(x < 6565)
          {                              
         if(tf1)
         {  
                y1++;
                
           if((key[KEY_SPACE])&& ((y+38 <= y1+34) && ( y+38 >=y1+12))&&(xb-20 >sx + 120)&&(xb+20 <= sx +205))
           {
            b1 = true;
            }
            else if (!b1)
            {
                 
           draw_sprite(scene,beeimg[curframe],xc-20,y1);
           
           }
           // rect(scene,xb-20,132,xb+20,154,makecol(255,0,255));
          
           //rect(scene,xb+60,80,xb+90,100,makecol(255,255,255));
           if(y1==180)tf1=false;
           }
          if(!tf1)
           
           { 
             y1--;
             if((key[KEY_SPACE])&& ((y+38 <= y1+34) && ( y+38 >=y1+12))&&(xc-20 >sx + 120)&&(xc+20 <= sx +205))
           {
           b1 = true;
           }
           else if (!b1)
           {
           draw_sprite(scene,beeimg[curframe],xc-20,y1);
           
            // rect(scene,xb-20,132,xb+20,154,makecol(255,0,255)); 
            }
            
            if(y1==120)tf1=true;
            }
            
           if(tf2)
           
           {  y2++;
                  
            if((key[KEY_SPACE])&& ((y+38 <= y2-20) && ( y+38 >=y2-40))&& (xc+60>sx + 120)&&(xc + 90 <= sx + 205))
           {
           b2 = true;
           }
           else if (!b2)
           {
           draw_sprite_h_flip(scene,skeeterimg[curframe],xc+50,y2-50);
           
           }//rect(scene,xb+60,80,xb+90,100,makecol(255,255,255));
            if(y2==180)tf2=false;
            }
            if(!tf2)
            {  y2--;
            if((key[KEY_SPACE])&& ((y+38 <= y2-20) && ( y+38 >=y2-40))&& (xc+60>sx + 120)&&(xc + 90 <= sx + 205))
           {
           b2 = true;
           }
           else if (!b2)
           {
           draw_sprite_h_flip(scene,skeeterimg[curframe],xc+50,y2-50);
           }//rect(scene,xb+60,80,xb+90,100,makecol(255,255,255));
           
           if(y2==120)tf2=true;
           }
           if (tf3)
           {
              y3--;
              
           if((key[KEY_SPACE])&& ((y+38 <= y3+90) && ( y+38 >=y3+70))&&(xc + 10 > sx + 120)&&(xc+40 <= sx + 205))
           {
           b3 = true;
           }
           else if (!b3)
           {
           draw_sprite_h_flip(scene,skeeterimg[curframe],xc,y3+60);
           //rect(scene,xb+10,390,xb+40,410,makecol(255,255,255));
            
           }
           if(y3 == 248) tf3 = false;
           }
           if(!tf3)
           {
             y3++;
             if((key[KEY_SPACE])&& ((y+38 <= y3+90) && ( y+38 >=y3+70))&&(xc + 10 > sx + 120)&&(xc+40 <= sx + 205))
            {
            b3 = true;
            }
            else if (!b3)
            {
            draw_sprite_h_flip(scene,skeeterimg[curframe],xc,y3+60);
            //rect(scene,xb+10,390,xb+40,410,makecol(255,255,255));
            }
            if(y3== 320) tf3 = true;
            }
            if(tf4)
            {
                   y4--;
             if((key[KEY_SPACE])&& ((y+38 <= y4+34)&& ( y+38 >=y4+12))&& (xc - 100 > sx + 120)&&(xc -60 < sx +205))
            {
            b4 = true;
            }
            else if (!b4)
            {
            draw_sprite(scene,beeimg[curframe],xc-100,y4);
            //rect(scene,xb-100,332,xb-60,354,makecol(255,255,255));
            }
            if(y4 == 248) tf4 = false;
            }
            if(!tf4)
            {
            y4++;
           if((key[KEY_SPACE])&& ((y+38 <= y4+34)&& ( y+38 >=y4+12))&& (xc - 100 > sx + 120)&&(xc -60 < sx +205))
           {
           b4 = true;
           }
           else if (!b4)
           {
           draw_sprite(scene,beeimg[curframe],xc-100,y4);
           //rect(scene,xb-100,332,xb-60,354,makecol(255,255,255));
           }
           if(y4 == 320) tf4 = true;
           }
           }                                
                                               
}                                            
                                               
