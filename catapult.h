#ifndef CATAPULT_H
#define	CATAPULT_H

#include <stdlib.h> 
#include <iostream>

#define CATAPULT_ELEM_NBR 7
#define CATAPULT_ARRAY_SIZE 8

#define LB 0           //la longueur du bras Lb (en mètres)
#define MB 1           //la masse du bras mb (en kilos)
#define BETA 2         //l'angle de la force de traction avec le bras β (en degrés)
#define MC 3           //la masse du contrepoids responsable de la force de traction mc (en kilos)
#define MP 4           //la masse du projectile mp (en kilos)
#define LR 5          //la longueur de la base Lr (en mètres)
#define ALPHA 6        //l'angle α (en degrés)

#define score 7;

class Catapult{
    
public:
    static float* genererCatapulte(float*);
    static float randomBetween(int, int);
    static float** genererGeneration(float**, int);
};

#endif

