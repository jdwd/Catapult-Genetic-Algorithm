#ifndef CATAPULT_H
#define	CATAPULT_H

#include <math.h>
#include <stdlib.h> 
#include <iostream>

#define CATAPULT_ELEM_NBR 7
#define CATAPULT_ARRAY_SIZE 10

#define LB 0           //la longueur du bras Lb (en mètres)
#define MB 1           //la masse du bras mb (en kilos)
#define BETA 2         //l'angle de la force de traction avec le bras β (en degrés)
#define MC 3           //la masse du contrepoids responsable de la force de traction mc (en kilos)
#define MP 4           //la masse du projectile mp (en kilos)
#define LR 5          //la longueur de la base Lr (en mètres)
#define ALPHA 6        //l'angle α (en degrés)

#define SCORE 7
#define PORTEE 8
#define ENERGIE 9

#define TNT_DENOMINATEUR 4184

const float PONDERATION_VIABLE = 0.5;
const float PONDERATION_ENERGIE = 0.35;
const float PONDERATION_PORTEE = 0.65;

class Catapult{
    
public:
    static void genererCatapulte(float*&, float);
    static float randomBetween(int, int);
    static float** genererGeneration(int, float);
    static float forceTraction(float*, float);
    static float momentBras(float*, float);
    static float momentInertieBras(float*);
    static float accelerationAngulaire(float*, float);
    static float velocite(float*, float);
    static float portee(float*, float);
    static float energieImpact(float*, float);
    static bool isViable(float*, float);
    static float energieTNT(float);
    static float* croiserCatapultes(float*, float*, float);
    static void mutation(float*);
    static int getPointCoupe();
    static float calculScore(float*&, float);
    
private:
    static int pointCoupe;
};

#endif

