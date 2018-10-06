/**
  ******************************************************************************************************************
  * @file    boule.c 
  * @author  R.NOHE     IUT Informatique La Rochelle
  * @version v1.0
  * @date    25 avril 2013
  * @modification
  * @brief   définitions pour la description et le pilotage du vaisseau
  ******************************************************************************************************************/

#include "ext_globales.h"
#include "GLCD.h"
#include "boule.h"
#include "jeu.h"

const unsigned short bmpBouleNormal[HAUTEUR_BOULE*LARGEUR_BOULE*2]=
{
	Black, Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, Black, 
	Black, Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, Black, Black, 
	Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive,
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive,	
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
	Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
	Black, Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, Black, Black, 
	Black, Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, Black, 
};

const unsigned short bmpBouleGauche[HAUTEUR_BOULE*LARGEUR_BOULE*2]=
{
Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, Black, Black, 
Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, Black, Black, Black, 
Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, Black, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
Black, Black, Black, Olive, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
Black, Black, Black, Black, Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
Black, Black, Black, Olive, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, Black, 
Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, Black, Black, 
Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, Black, 
};

const unsigned short bmpBouleDroite[HAUTEUR_BOULE*LARGEUR_BOULE*2]=
{
	Black, Black, Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, 
	Black, Black, Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, Black, 
	Black, Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
	Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Olive, Black, Black, Black, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Olive, Black, Black, Black, Black, Black, Black, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Olive, Black, Black, Black, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, 
	Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Black, Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
	Black, Black, Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, Black, 
	Black, Black, Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, 
};

const unsigned short bmpBouleHaut[HAUTEUR_BOULE*LARGEUR_BOULE*2]=
{
Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
Black, Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, Black, 
Black, Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, Black, Black, 
Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
Black, Olive, Yellow, Yellow, Yellow, Yellow, Olive, Black, Olive, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
Black, Olive, Yellow, Yellow, Yellow, Olive, Black, Black, Black, Olive, Yellow, Yellow, Yellow, Olive, Black, 
Black, Black, Olive, Yellow, Yellow, Olive, Black, Black, Black, Olive, Yellow, Yellow, Olive, Black, Black, 
Black, Black, Black, Olive, Olive, Black, Black, Black, Black, Black, Olive, Olive, Black, Black, Black, 
};

const unsigned short bmpBouleBas[HAUTEUR_BOULE*LARGEUR_BOULE*2]=
{
	Black, Black, Black, Olive, Olive, Black, Black, Black, Black, Black, Olive, Olive, Black, Black, Black, 
	Black, Black, Olive, Yellow, Yellow, Olive, Black, Black, Black, Olive, Yellow, Yellow, Olive, Black, Black, 
	Black, Olive, Yellow, Yellow, Yellow, Olive, Black, Black, Black, Olive, Yellow, Yellow, Yellow, Olive, Black, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Olive, Black, Olive, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, 
	Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, 
	Black, Black, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Black, Black, 
	Black, Black, Black, Olive, Olive, Yellow, Yellow, Yellow, Yellow, Yellow, Olive, Olive, Black, Black, Black, 
	Black, Black, Black, Black, Black, Olive, Olive, Olive, Olive, Olive, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
};

const unsigned short bmpBouleMask[HAUTEUR_BOULE*LARGEUR_BOULE*2]=
{
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, 
};
