/**
  ******************************************************************************************************************
  * @file    main.c 
  * @author  R.NOHE     IUT Informatique La Rochelle
  * @version v1.0
  * @date    20 mai 2013
  * @modification	rien pour le moment
  * @brief   programme simple pour utiliser les fonctions graphiques de l'affiche LCD de la carte MCBSTM32EXL
  ******************************************************************************************************************/

#include "stm32f10x.h"                                                   /* STM32F10x.h definitions                */
#include "GLCD.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jeu.h"
#include "boule.h"
#include "globales.h"
#include "ext_globales.h"
#include "food.h"




#define SETENA0 *(volatile unsigned long *)0xE000E100
#define SETENA1 *(volatile unsigned long *)0xE000E104
#define AFIO_EXTICR1 *(volatile unsigned long *)0x40010008
#define AFIO_EXTICR4 *(volatile unsigned long *)0x40010014

/*----------------------------------------------------------------------------
  Config Timer
 *----------------------------------------------------------------------------*/
void cfgTimer1(void){
	RCC->APB2ENR |= (1<<11);                                               /* Mise en service du timer 1             */
	TIM1->PSC = 71;                                                        /* Valeur du prescaler                    */
	TIM1->ARR = 10000;                                                     /* Valeur de retour automatique           */
	TIM1->DIER |= (1<<0);                                                  /* Activation des interuptions            */
	TIM1->CR1 |= (1<<0);                                                   /* Activation du compteur 1               */
	SETENA0 |= (1<<25);                                                    /* Activation de l'interruption "TIM1_UP" */
}

void cfgTimer8(void){
	RCC->APB2ENR |= (1<<13);
	TIM8->PSC = 287;
	TIM8->ARR = 50000;
	TIM8->DIER |= (1<<0);
	TIM8->CR1 |= (1<<0);
	SETENA1 |= (1<<12);
}

/*----------------------------------------------------------------------------
  Config GPIO
 *----------------------------------------------------------------------------*/
void cfgGPIO(void){
	unsigned int temp;
	RCC->APB2ENR |= (1<<0);
	
		/* Config JOYSTICK_LEFT */
	RCC->APB2ENR |= (1 << 8);
	temp = GPIOG->CRH &= 0xF0FFFFFF;
	GPIOG->CRH = temp |= 0x04000000;
	
	SETENA1 |= (1<<8);
	temp = AFIO_EXTICR4 & 0xF0FF;
	AFIO_EXTICR4 = temp |= 0x0600;
	EXTI->IMR |= (1<<14);
	EXTI->FTSR |= (1<<14);
	
		/* Config JOYSTICK_RIGHT */
	temp = GPIOG->CRH &= 0xFF0FFFFF;
	GPIOG->CRH = temp |= 0x00400000;
	
	temp = AFIO_EXTICR4 & 0xFF0F;
	AFIO_EXTICR4 = temp |= 0x0060;
	EXTI->IMR |= (1<<13);
	EXTI->FTSR |= (1<<13);
	
		/* Config JOYSTICK_UP */
	temp = GPIOG->CRH &= 0x0FFFFFFF;
	GPIOG->CRH = temp |= 0x40000000;
	
	temp = AFIO_EXTICR4 & 0x0FFF;
	AFIO_EXTICR4 = temp |= 0x6000;
	EXTI->IMR |= (1<<15);
	EXTI->FTSR |= (1<<15);
	
		/* Config JOYSTICK_DOWN */
	RCC->APB2ENR |= (1 << 5);
	temp = GPIOD->CRL &= 0xFFFF0FFF;
	GPIOD->CRL = temp |= 0x00004000;
	
	SETENA0 |= (1<<9);
	temp = AFIO_EXTICR1 & 0x0FFF;
	AFIO_EXTICR1 = temp |= 0x3000;
	EXTI->IMR |= (1<<3);
	EXTI->FTSR |= (1<<3);
	
}
	
/*----------------------------------------------------------------------------
  Interruption
 *----------------------------------------------------------------------------*/
void TIM1_UP_IRQHandler(void){
	if (TIM1->SR & (1<<0)){
		unsigned char message[] = "bonjour";
		GLCD_AfficheString(1, 1, 0, message);
		if (xBoule + LARGEUR_BOULE > WIDTH){
			directionH = 0;
			xBoule = WIDTH - LARGEUR_BOULE;
			bmpBoule = (unsigned char *) bmpBouleDroite;
		}
		if (xBoule < 0){
			directionH = 0;
			xBoule = 0;
			bmpBoule = (unsigned char *) bmpBouleGauche;
		}
		if (yBoule + HAUTEUR_BOULE > HEIGHT){
			directionV = 0;
			yBoule = HEIGHT - HAUTEUR_BOULE;
			bmpBoule = (unsigned char *) bmpBouleBas;
		}
		if (yBoule < 0){
			directionV = 0;
			yBoule = 0;
			bmpBoule = (unsigned char *) bmpBouleHaut;
		}
		if (directionH != 0 || directionV != 0)
		GLCD_Bmp(xBoule, yBoule, LARGEUR_BOULE, HAUTEUR_BOULE, (unsigned char *) bmpBouleMask);
		xBoule += directionH;
		yBoule += directionV;
		if ((xBoule < xFood + LARGEUR_FOOD && xBoule > xFood) && (yBoule < yFood + HAUTEUR_FOOD && yBoule > yFood)){
			GLCD_Bmp(xFood, yFood, LARGEUR_FOOD, HAUTEUR_FOOD, (unsigned char *) bmpFoodMask);
			xFood = rand()%305;
			yFood = rand()%225;
			GLCD_Bmp(xFood, yFood, LARGEUR_FOOD, HAUTEUR_FOOD, (unsigned char *) bmpFood);
			score++;
			if (score == 4){
				
			}
		}
		GLCD_Bmp(xBoule, yBoule, LARGEUR_BOULE, HAUTEUR_BOULE, (unsigned char *) bmpBoule);
		TIM1->SR &= ~(1<<0);
	}
}

void TIM8_UP_IRQHandler(void){
	if (TIM8->SR & (1<<0)){
		if (bmpBoule == (unsigned char *) bmpBouleNormal || (directionH == 0 && directionV == 0)){
			if (directionH == -1)
			bmpBoule = (unsigned char *)bmpBouleGauche;
			else if (directionH == 1)
				bmpBoule = (unsigned char *)bmpBouleDroite;
			if (directionV == -1)
				bmpBoule = (unsigned char *)bmpBouleHaut;
			else if (directionV == 1)
				bmpBoule = (unsigned char *)bmpBouleBas;
		}
		else
			bmpBoule = (unsigned char *)bmpBouleNormal;
		TIM8->SR &= ~(1<<0);
	}
}

void EXTI15_10_IRQHandler(void){
	if (EXTI->PR & (1<<14))
	{
		if (directionH > -1)
			directionH--;
		directionV = 0;
		if(directionH == 0)
			bmpBoule = (unsigned char *) bmpBouleDroite;
		EXTI->PR |= (1<<14);
	}
	if (EXTI->PR & (1<<13)){
		if (directionH < 1)
			directionH++;
		directionV = 0;
		if(directionH == 0)
			bmpBoule = (unsigned char *) bmpBouleGauche;
		EXTI->PR |= (1<<13);
	}
	if (EXTI->PR & (1<<15)){
		if (directionV > -1)
			directionV--;
		directionH = 0;
		if(directionV == 0)
			bmpBoule = (unsigned char *) bmpBouleBas;
		EXTI->PR |= (1<<15);
	}
}

void EXTI3_IRQHandler(void){
	if (EXTI->PR & (1<<3)){
		if (directionV < 1)
			directionV ++;
		directionH = 0;
		if(directionV == 0)
			bmpBoule = (unsigned char *) bmpBouleHaut;
		EXTI->PR |= (1<<3);
	}
}

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	
  GLCD_Init();                                                           /* Initialize graphical LCD display       */
  GLCD_Clear(BACK_COLOR);                                                /* Clear graphical LCD display            */
  GLCD_SetBackColor(BACK_COLOR);
	
	xBoule = 150;
	yBoule = 70;
	
	xFood = rand()%305;
	yFood = rand()%225;
	GLCD_Bmp(xFood, yFood, LARGEUR_FOOD, HAUTEUR_FOOD, (unsigned char *) bmpFood);
	
	score = 0;
	
	directionH = 0;
	directionV = 0;
	
	bmpBoule = (unsigned char *)bmpBouleNormal;
	
	cfgGPIO();
	cfgTimer1();
	cfgTimer8();

	while(1);
	
}
