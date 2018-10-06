#include "ext_globales.h"
#include "GLCD.h"
#include "food.h"
#include "jeu.h"

const unsigned short bmpFood[HAUTEUR_FOOD*LARGEUR_FOOD*2]=
{
	Black, Black, Yellow, Yellow, Black, Black,
	Black, Yellow, Yellow, Yellow, Yellow, Black,
	Yellow, Yellow, Yellow, Yellow, Yellow, Yellow,
	Black, Yellow, Yellow, Yellow, Yellow, Black, 
	Black, Black, Yellow, Yellow, Black, Black,
};

const unsigned short bmpFoodMask[]=
{
	Black, Black, Black, Black, Black, Black,
	Black, Black, Black, Black, Black, Black,
	Black, Black, Black, Black, Black, Black,
	Black, Black, Black, Black, Black, Black, 
	Black, Black, Black, Black, Black, Black,
};
