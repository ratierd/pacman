/**
  ******************************************************************************************************************
  * @file    boule.h 
  * @author  R.NOHE     IUT Informatique La Rochelle
  * @version v1.0
  * @date    25 avril 2013
  * @modification	rien pour le moment
  * @brief   définition des macros et déclarations des routines 
  ******************************************************************************************************************/


#ifndef __BOULE_H
#define __BOULE_H

#define HAUTEUR_BOULE	15
#define LARGEUR_BOULE	15

extern const unsigned short bmpBouleNormal[HAUTEUR_BOULE*LARGEUR_BOULE*2];
extern const unsigned short bmpBouleGauche[HAUTEUR_BOULE*LARGEUR_BOULE*2];
extern const unsigned short bmpBouleDroite[HAUTEUR_BOULE*LARGEUR_BOULE*2];
extern const unsigned short bmpBouleHaut[HAUTEUR_BOULE*LARGEUR_BOULE*2];
extern const unsigned short bmpBouleBas[HAUTEUR_BOULE*LARGEUR_BOULE*2];
extern const unsigned short bmpBouleMask[HAUTEUR_BOULE*LARGEUR_BOULE*2];


#endif
