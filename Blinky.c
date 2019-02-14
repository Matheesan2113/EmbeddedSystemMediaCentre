#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include <stdio.h>
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
extern unsigned char kakashi[];
extern unsigned char sasuke[];
extern unsigned char goku[];
extern unsigned char gokus[];
//extern unsigned char vegeta[];
#include "type.h"
#include "menu.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"
#include "usbdmain.h"
#include "game.h"
extern void music(void);
extern uint8_t  clock_ms;
//------- ITM Stimulus Port definitions for printf ------------------- //
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

#define __FI        1  
#define __USE_LCD   0	

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

//DELAY FUNCTION
void delay(){
	int i, j;
	
	for(i=0; i<1000000; i++){
		j = j * 2;
		j--;
	}
}

//PHOTO GALLERY
void pictures(){
	int button;
	int a = 0;
	int count12=0;
	int rew=0;
	int rew2=0;
	int rew3=0;
		#ifdef __USE_LCD
  GLCD_Clear(White); 
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
  GLCD_DisplayString(0, 3, __FI, " Photo gallery");
	GLCD_DisplayString(5, 0, __FI, "Slide right to view");
#endif  
	for(count12=0;count12<10;count12++){
		delay();
	}
	GLCD_Clear(Black);
		while(1){
		button = get_button();
		
		if (button == KBD_RIGHT){
			a++;}
		if (button ==KBD_LEFT){
			a--;
		}
		if(a<0){
			a=0;
			#ifdef __USE_LCD
				GLCD_Clear(White); 
			#endif
			return;
		}
		if(a==4){
			#ifdef __USE_LCD
				GLCD_Clear(White); 
			#endif
			return;
		}
			if (a==0)
			{
				GLCD_Bitmap (0, 0, 256,  230, kakashi);
				for(rew=0;rew<2;rew++){
					delay();
				}
			}
			if (a == 1){
				GLCD_Bitmap (0, 0, 256,  256, sasuke);
				for( rew2=0;rew2<2;rew2++){
					delay();
				}
			}
				if (a == 2){
				GLCD_Bitmap (0, 0, 256,  230, goku);
				for( rew3=0;rew3<2;rew3++){
					delay();
				}
			}

			
		if (button == KBD_UP){
			#ifdef __USE_LCD
				GLCD_Clear(White); 
			#endif 
			return;
		}
	}

}

//GAME MENU
void gamemenu(){
int button;	
GLCD_Clear(Black); 
SystemInit();
while(1){
button = get_button();
				#ifdef __USE_LCD
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "    IQ Game    ");
				GLCD_DisplayString(2, 0, __FI, "INSTRUCTIONS:");	
				GLCD_DisplayString(3, 0, __FI, "Kakashi=left,sasuke=");	
				GLCD_DisplayString(4, 0, __FI, "up, Goku=Right. Move");
				GLCD_DisplayString(5, 0, __FI, "the joystick quickly");
				GLCD_DisplayString(6, 0, __FI, "and correctly to win");
				GLCD_DisplayString(8, 0, __FI, "Press select to play");
			#endif
	
	if (button == KBD_SELECT)
	{
					#ifdef __USE_LCD
						GLCD_Clear(Black);  
					#endif  
					game();
	}
		if (button == KBD_LEFT)
	{
					#ifdef __USE_LCD
						GLCD_Clear(Black);  
					#endif  
					menu();
	}
}
}

//MAIN MENU
void menu(){
	int pos = 1;
	int button;
	
		#ifdef __USE_LCD
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
  GLCD_DisplayString(0, 5, __FI, "Main Menu");
	GLCD_SetTextColor(Blue);
	GLCD_SetBackColor(White);	
	GLCD_DisplayString(2, 0, __FI, "        Photo Gallery");
	GLCD_SetTextColor(Blue);
	GLCD_SetBackColor(White);
	GLCD_DisplayString(3, 0, __FI, "        Music        ");
	GLCD_DisplayString(4, 0, __FI, "        Game         ");	
#endif  

	while(1){
		button = get_button();
		if(button == KBD_DOWN){
			if(pos == 4){
				pos = 0;
			}
			else {
				pos++;
			}
		}
		else if(button == KBD_UP){
			if(pos == 1){
				pos = 4;
			}
			else {
				pos--;
			}
		}
		
		if(pos == 1){
			#ifdef __USE_LCD
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(0, 5, __FI, "Main Menu");
				GLCD_SetTextColor(Blue);
				GLCD_SetBackColor(White);	
				GLCD_DisplayString(2, 0, __FI, "    -->Photo Gallery");
				GLCD_SetTextColor(Blue);
				GLCD_SetBackColor(White);
				GLCD_DisplayString(3, 0, __FI, "       Music        ");
				GLCD_DisplayString(4, 0, __FI, "       Game         ");	
			#endif  
			if(button == KBD_SELECT){
				#ifdef __USE_LCD
					GLCD_Clear(Black);  
				#endif  
				pictures();
			}
		}
		
		else if(pos == 2){
			#ifdef __USE_LCD
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(0, 5, __FI, "Main Menu");
				GLCD_SetTextColor(Blue);
				GLCD_SetBackColor(White);	
				GLCD_DisplayString(2, 0, __FI, "       Photo Gallery");
				GLCD_DisplayString(4, 0, __FI, "       Game         ");		
				GLCD_SetTextColor(Blue);
				GLCD_SetBackColor(White);
				GLCD_DisplayString(3, 0, __FI, "     -->Music       ");
			#endif  
		if(button == KBD_SELECT){
				#ifdef __USE_LCD
				GLCD_Clear(White);
			  GLCD_SetBackColor(White);
			  GLCD_SetTextColor(Black);
				GLCD_DisplayString(4, 1, __FI, "Enjoy the music!");
				#endif  
		 		music();
				GLCD_Clear(Black);
			
		}
	}

		else if(pos == 3){
			#ifdef __USE_LCD
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(0, 5, __FI, "Main Menu");
				GLCD_SetTextColor(Blue);
				GLCD_SetBackColor(White);	
				GLCD_DisplayString(2, 0, __FI, "       Photo Gallery");	
				GLCD_DisplayString(3, 0, __FI, "       Music        ");
				GLCD_SetTextColor(Blue);
				GLCD_SetBackColor(White);
				GLCD_DisplayString(4, 0, __FI, "     -->Game        ");
			#endif  
			
		if(button == KBD_SELECT){
		#ifdef __USE_LCD
			GLCD_Clear(Black);
		#endif  
		gamemenu();
		}
		}	

	
}
	
}

//STARTS GAME
int main (void) {                       /* Main Program                       */
	
	int buttons;
	LED_Init ();
	

	#ifdef __USE_LCD
  GLCD_Init();                               /* Initialize graphical LCD (if enabled */

  GLCD_Clear(White);                         /* Clear graphical LCD display   */
 GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
  GLCD_DisplayString(0, 0, __FI, "    Media Project      ");
	GLCD_SetTextColor(Blue);
  GLCD_DisplayString(1, 0, __FI, " Matheesan Manokaran");
  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
	GLCD_DisplayString(5, 1, __FI, "Click select for");
	GLCD_DisplayString(6, 0, __FI, "      Main Menu      ");
#endif  
	
	while(1){
	
	buttons = get_button();
	if(buttons == KBD_SELECT || buttons == KBD_RIGHT || buttons == KBD_LEFT || buttons == KBD_UP || buttons == KBD_DOWN){
			#ifdef __USE_LCD
				GLCD_Clear(White);  
			#endif  
		menu();
	}
	
		
}

}
