#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include <stdio.h>
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define __FI        1 

int i,n; 
int n=5; 
int score=0; 
long m;
int iqnum=0;
int buttons; 
int rounds=0;
uint32_t cc1=0;
uint32_t cc2=0;
int a=0,b=0,e=0,target=0;
unsigned char text[20],text2[20],text3[20],text4[14],text5[15],iq[4];
extern uint8_t  clock_ms;
extern int c,ticks;
extern unsigned char kakashi[];
extern unsigned char sasuke[];
extern unsigned char goku[];
void delay2(){
	int i, j;
	
	for(i=0; i<1000000; i++){
		j = j * 2;
		j--;
	}
}
//delay 10 times longer
void d2(){ 
int i, j;
	
	for(i=0; i<10000000; i++){
		j = j * 2;
		j--;
	}
}	

//GG
void over(){
	rounds=0;
while(1)
{
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
buttons = get_button();
	GLCD_DisplayString(8, 0, __FI, "your iq is");
	sprintf (text2, " iq=%d", iqnum);
	GLCD_DisplayString(8, 10, __FI, text2);
if (buttons == KBD_SELECT)
{
gamemenu(); 	
}
}
}

//CHECK IF THE TEAR WENT INTO THE BASKET
void check(){
	delay2();
if(buttons == KBD_LEFT && target==0){
	rounds++;
	target=	rand()%3;
	ticks=0;
	GLCD_Clear(Black);
}
else if(buttons ==KBD_UP && target==1){
	rounds++;
	target=	rand()%3;
	ticks=0;
	GLCD_Clear(Black);
}
else if(buttons ==KBD_RIGHT && target==2){
	rounds++;
	target=	rand()%3;
	ticks=0;
	GLCD_Clear(Black);
}
else if(buttons ==KBD_DOWN && target==3){
	rounds++;
	target=	rand()%3;
	ticks=0;
	GLCD_Clear(Black);
}
else{
	iqnum=iqnum-50;
}
if (rounds==5){
	sprintf(iq,"%d",iqnum);
	GLCD_DisplayString(7, 0, __FI, iq);
	over();
}
}
//change iq
void changescr(uint32_t scr){
	scr=scr/10;
	if(scr<1){
		iqnum+=50;
	}
	else if(scr<2){
		iqnum=iqnum+30;
	}
	else if(scr<3){
		iqnum=iqnum+20;
	}
	else if(scr>3){
		iqnum=iqnum-5;
	}
}
//change image randomly
void setImage(int b){
	delay2();
	switch(b) {
   case 0  :
      GLCD_Bitmap (0, 0, 256,  180, kakashi);
      break; 
	
   case 1  :
      GLCD_Bitmap (0, 0, 256,  180, sasuke);
      break; 
	 case 2  :
      GLCD_Bitmap (0, 0, 256,  180, goku);
      break; 
  
   /* you can have any number of case statements */
   default : 
    GLCD_Bitmap (0, 0, 256,  180, kakashi);
}
}
//GAME FUNCTION
void game (){
	c=0;
	iqnum=0;
	rounds=0;
	ticks=0;
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
  SysTick_Config(SystemCoreClock/10);
	target=	rand()%3;
while(1){
	SystemInit();
	setImage(target);
	d2();
	buttons = get_button();
	check();
	changescr(ticks);
	sprintf (text2, "target= %d", target);
	sprintf (text3, " iqnum= %d", iqnum);
	sprintf (text4, " ticks= %d", ticks);
	GLCD_DisplayString(8, 0, __FI, text2);
	GLCD_DisplayString(9, 0, __FI, text3);
	GLCD_DisplayString(9, 10, __FI, text4);
}
score=0; 	

}

