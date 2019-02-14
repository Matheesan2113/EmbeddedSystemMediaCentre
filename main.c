#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include <stdio.h>
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
extern unsigned char drake[];
extern unsigned char SMILE_pixel_data[];
#include "type.h"
#include "menu.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"
#include "usbdmain.h"
#include "game.h"

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
		#ifdef __USE_LCD
  GLCD_Clear(Black); 
	GLCD_SetBackColor(Black);
  GLCD_SetTextColor(Red);
  GLCD_DisplayString(0, 3, __FI, " Photo gallery");
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(5, 0, __FI, "Slide right to view");
#endif  
	
		while(1){
		button = get_button();
		
		if (button == KBD_RIGHT){
			while (a<10)
			{
				GLCD_Bitmap (0, 0, 318,  240, drake);
				a++;
			}
			if (a == 10){
				GLCD_Clear  (Black);
				GLCD_Bitmap (65, 50, 160,  160, SMILE_pixel_data);
			}
		}
		
		if (button == KBD_LEFT){
			#ifdef __USE_LCD
				GLCD_Clear(Black); 
			#endif 
			return;
  
		}
	}

}

//GAME MENU
void gamemenu(){
int button;	
GLCD_Clear(Black); 

while(1){
button = get_button();
				#ifdef __USE_LCD
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, __FI, "    Marvins Room    ");
				GLCD_SetTextColor(White);
				GLCD_SetBackColor(Black);	
				GLCD_DisplayString(3, 0, __FI, "    INSTRUCTIONS:");	
				GLCD_DisplayString(4, 1, __FI, "Cheer up Drake by");	
				GLCD_DisplayString(5, 1, __FI, "catching his tears");
				GLCD_DisplayString(7, 0, __FI, "Press select to play");
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
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
  GLCD_SetTextColor(White);
  GLCD_DisplayString(0, 5, __FI, "Main Menu");
	GLCD_SetTextColor(White);
	GLCD_SetBackColor(Red);	
	GLCD_DisplayString(3, 0, __FI, "1) Photo Gallery");
	GLCD_SetTextColor(White);
	GLCD_SetBackColor(Black);
	GLCD_DisplayString(4, 0, __FI, "2) Music Player");
	GLCD_DisplayString(5, 0, __FI, "3) Game               ");	
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
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 5, __FI, "Main Menu");
				GLCD_SetTextColor(White);
				GLCD_SetBackColor(Red);	
				GLCD_DisplayString(3, 0, __FI, "1) Photo Gallery");
				GLCD_SetTextColor(White);
				GLCD_SetBackColor(Black);
				GLCD_DisplayString(4, 0, __FI, "2) Music Player");
				GLCD_DisplayString(5, 0, __FI, "3) Game               ");	
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
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 5, __FI, "Main Menu");
				GLCD_SetTextColor(White);
				GLCD_SetBackColor(Black);	
				GLCD_DisplayString(3, 0, __FI, "1) Photo Gallery");
				GLCD_DisplayString(5, 0, __FI, "3) Game               ");		
				GLCD_SetTextColor(White);
				GLCD_SetBackColor(Red);
				GLCD_DisplayString(4, 0, __FI, "2) Music Player");
			#endif  
		if(button == KBD_SELECT){
				#ifdef __USE_LCD
				GLCD_Clear(Black);
				GLCD_DisplayString(5, 1, __FI, "Enjoy the music!");
			
				#endif  
				music();
				GLCD_Clear(Black);
			
		}
	}

		else if(pos == 3){
			#ifdef __USE_LCD
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 5, __FI, "Main Menu");
				GLCD_SetTextColor(White);
				GLCD_SetBackColor(Black);	
				GLCD_DisplayString(3, 0, __FI, "1) Photo Gallery");	
				GLCD_DisplayString(4, 0, __FI, "2) Music Player");
				GLCD_SetTextColor(White);
				GLCD_SetBackColor(Red);
				GLCD_DisplayString(5, 0, __FI, "3) Game                     ");
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
 GLCD_SetBackColor(Black);
  GLCD_SetTextColor(Red);
  GLCD_DisplayString(0, 0, __FI, "    Media Project      ");
	GLCD_SetTextColor(Red);
  GLCD_DisplayString(1, 0, __FI, "    Zuhaib Bhatti      ");
  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Red);
	GLCD_DisplayString(5, 1, __FI, "Move the joystick!");
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
