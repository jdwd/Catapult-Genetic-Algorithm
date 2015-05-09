#include "catapult.h"

//TODO Tableau de float

/* Fonctions relatives à la catapulte */
/** A FAIRE
 * FORCE DE TRACTION
 * MOMENT DU BRAS
 * MOMENT D'INERTIE DU BRAS
 * ACCELERATION ANGULAIRE UNIFORME
 * VELICITE
 * PORTEE
 * ENERGIE D'INPACTE
 * Formule determinant si la constructione est VIABLE
 * EQUIVALENCE Joule et TNT
 */

int Catapult::pointCoupe = 0;


float Catapult::randomBetween(int min, int max){
    
    return rand() % max + min;
}

int genererGene(int gene){
    
    switch(gene){
        case LB:
            return Catapult::randomBetween(1, 1000);
        case MB:
            return Catapult::randomBetween(1, 2000);
        case BETA:
            return Catapult::randomBetween(0, 180);
        case MC:
            return Catapult::randomBetween(0, 10000);
        case MP:
            return Catapult::randomBetween(0, 10000);
        case LR:
            return Catapult::randomBetween(1, 1000);
        case ALPHA:
            return Catapult::randomBetween(0, 180);
        default:
            return 0;
    }
}

void Catapult::genererCatapulte(float* &catapulte){
    
    catapulte[LB] = genererGene(LB);
    catapulte[MB] = genererGene(MB);
    catapulte[BETA] = genererGene(BETA);
    catapulte[MC] = genererGene(MC);
    catapulte[MP] = genererGene(MP);
    catapulte[LR] = genererGene(LR);
    catapulte[ALPHA] = genererGene(ALPHA);
}

float** Catapult::genererGeneration(int nbrGeneration){
    
    float** generation = new float *[nbrGeneration];
    
    for(int i = 0; i < nbrGeneration; i++){
                
        float* catapulte = new float[CATAPULT_ARRAY_SIZE];
        
        Catapult::genererCatapulte(catapulte);
        catapulte[SCORE] = Catapult::randomBetween(0, 1000);
        
        generation[i] = catapulte;
    }
    
    return generation;
}

int Catapult::getPointCoupe(){
    
    int changement = randomBetween(0, 1);

    if(changement == 1 || pointCoupe == 0){
        
        pointCoupe = randomBetween(1, CATAPULT_ELEM_NBR -1);
    }
    
    return pointCoupe;
}

float* Catapult::croiserCatapultes(float* maman1, float* maman2){
    
    float* fiston = new float[CATAPULT_ARRAY_SIZE];
    
    bool mutation = false;
    int pointCoupe = Catapult::getPointCoupe();
    
    for(int chromosome = 0; chromosome <= pointCoupe; chromosome++)
        fiston[chromosome] = maman1[chromosome];
    
    for(int chromosome = pointCoupe+1; chromosome <= CATAPULT_ELEM_NBR; chromosome++)
        fiston[chromosome] = maman2[chromosome];
    
    fiston[SCORE] = Catapult::randomBetween(0, 1000);
    
    return fiston;
}

void Catapult::mutation(float* catapulte){
    
    for(int i = 0; i < CATAPULT_ELEM_NBR; i++)
        if(randomBetween(1, 100) <= 5)
            catapulte[i] = genererGene(i);
}

//Force de traction F (en N))
float forceTraction(float* catapult, float gravite){
    return((catapult[MC]*gravite)*sin(catapult[BETA])-(catapult[MP]*gravite)*cos(catapult[ALPHA]));
}

//Moment du bras M en (en N.m)
float momentBras(float* catapult, float gravite){
    return (forceTraction(catapult, gravite)*catapult[LB]);
}

//Moment d'inertie du bras I (en kg/m²)
float momentInertieBras(float* catapult){
    return ((catapult[MB]*sqrt(catapult[LB]))/3);
}

//Accélération angulaire uniforme a (en rad/s²)
float accelerationAngulaire(float* catapult, float gravite){
    return (momentBras(catapult, gravite)/momentInertieBras(catapult));
}

//Vélocité V (en m/s)
float velocite(float* catapult, float gravite){
    return (accelerationAngulaire(catapult, gravite)*catapult[LB]);
}

//Portée P (en M)
float portee(float* catapult, float gravite){
    return ((sqrt(velocite(catapult, gravite))/gravite)*sin(2*(90-catapult[ALPHA])));
}

//Energie d'impact (en joules) assimilée à la force cinétique transformée à l'impact
float energieImpact(float* catapult, float gravite){
    return (0.5*catapult[MP]*sqrt(velocite(catapult, gravite)));
}

//Indique si la construction est viable
float isViable(float* catapult, float gravite){
    float lessPart = ((sqrt(sin(catapult[ALPHA])*catapult[LB])+sqrt((cos(catapult[ALPHA])*catapult[LB])-catapult[LR]))*sin(catapult[ALPHA])*(catapult[MP]*gravite));
    float morePart  = catapult[LR]*(catapult[MC]*gravite);
    return (lessPart <= morePart);
}

float energieTNT(float energieJoule){
    return (energieJoule/TNT_DENOMINATEUR);
}