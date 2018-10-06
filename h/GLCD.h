/******************************************************************************/
/* GLCD.h: Graphic LCD function prototypes and defines                        */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#ifndef _GLCD_H
#define _GLCD_H


/************************** Orientation  configuration ************************/

#define HORIZONTAL  1                   /* If vertical = 0, if horizontal = 1 */

/*********************** Hardware specific configuration **********************/
#ifndef FSMC_Bank1_NORSRAM4             /* defined in ST Peripheral Library   */
  #define FSMC_Bank1_NORSRAM4      ((uint32_t)0x00000006)
#endif

/*------------------------- Speed dependant settings -------------------------*/

/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N    18

/*---------------------- Graphic LCD size definitions ------------------------*/

#if (HORIZONTAL == 1)
	#define WIDTH       320                 /* Screen Width (in pixels)           */
	#define HEIGHT      240                 /* Screen Hight (in pixels)           */
#else
	#define WIDTH       240                 /* Screen Width (in pixels)           */
	#define HEIGHT      320                 /* Screen Hight (in pixels)           */
#endif

#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

/*--------------- Graphic LCD interface hardware definitions -----------------*/

/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
#define LCD_BASE        (0x60000000UL | 0x0C000000UL)
#define LCD_REG16  (*((volatile unsigned short *)(LCD_BASE  ))) 
#define LCD_DAT16  (*((volatile unsigned short *)(LCD_BASE+2)))
 


/*------------------------------------------------------------------------------
  Color coding
  GLCD is coded:   15..11 red, 10..5 green, 4..0 blue  (unsigned short)  GLCD_R5, GLCD_G6, GLCD_B5   
  original coding: 17..12 red, 11..6 green, 5..0 blue                    ORG_R6,  ORG_G6,  ORG_B6

  ORG_R1..5 = GLCD_R0..4,  ORG_R0 = GLCD_R4
  ORG_G0..5 = GLCD_G0..5,
  ORG_B1..5 = GLCD_B0..4,  ORG_B0 = GLCD_B4
 *----------------------------------------------------------------------------*/
                            
/* GLCD RGB color definitions                                                 */
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */

#if (HORIZONTAL == 0)
	#define NB_COLONNE  15
	// cela permet de placer 240/16=15 caract�res par ligne
	#define NB_LIGNE    13
	//                    et 320/24=13,3 soit sur 13 lignes max
#else
	#define NB_COLONNE  53
	// cela permet de placer 320/6=53 caract�res par ligne
	#define NB_LIGNE    30
	//                    et 240/8=30 lignes max

#endif
	
#define Line0           ( 0*24)
#define Line1           ( 1*24)
#define Line2           ( 2*24)
#define Line3           ( 3*24)
#define Line4           ( 4*24)
#define Line5           ( 5*24)
#define Line6           ( 6*24)
#define Line7           ( 7*24)
#define Line8           ( 8*24)
#define Line9           ( 9*24)

extern void GLCD_Init           (void);
extern void GLCD_WindowMax      (void);
extern void GLCD_PutPixel       (unsigned int x, unsigned int y);
extern void GLCD_SetTextColor   (unsigned short color);
extern void GLCD_SetBackColor   (unsigned short color);
extern void GLCD_Clear          (unsigned short color);
//extern void GLCD_DrawChar       (unsigned int x, unsigned int y, unsigned short *c);
extern void GLCD_DisplayChar    (unsigned int ln, unsigned int col, unsigned char fi, unsigned char  c);
extern void GLCD_DisplayString  (unsigned int ln, unsigned int col, unsigned char fi, unsigned char *s);
extern void GLCD_ClearLn        (unsigned int ln, unsigned char fi);
extern void GLCD_Bargraph       (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val);
extern void GLCD_Bitmap         (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap);
extern void GLCD_Bmp            (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bmp);
extern void GLCD_ScrollVertical (unsigned int dy);
extern void GLCD_gotoXY         (unsigned int ln,unsigned int col);
extern void GLCD_AfficheString 	(unsigned int ln, unsigned int col, unsigned char fi, unsigned char *s);
extern void GLCD_DrawChar_U8 		(unsigned int x, unsigned int y, unsigned int cw, unsigned int ch, unsigned char *c);
extern void GLCD_DrawChar_U16 	(unsigned int x, unsigned int y, unsigned int cw, unsigned int ch, unsigned short *c);
#endif /* _GLCD_H */
