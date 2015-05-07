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

float Catapult::randomBetween(int min, int max){
    
    return rand() % max + min;
}

float* Catapult::genererCatapulte(float* catapulte){
    
    catapulte[LB] = randomBetween(1, 1000);
    catapulte[MB] = randomBetween(1, 2000);
    catapulte[BETA] = randomBetween(0, 180);
    catapulte[MC] = randomBetween(0, 10000);
    catapulte[MP] = randomBetween(0, 10000);
    catapulte[LR] = randomBetween(1, 1000);
    catapulte[ALPHA] = randomBetween(0, 180); 
    
    return catapulte;
}

float** Catapult::genererGeneration(float** generation, int generationNbr){
    
    generation = new float *[generationNbr];
    
    for(int i = 0; i < generationNbr; i++){
        
        float catapulte[CATAPULT_ARRAY_SIZE];
        float* pCatapulte = catapulte;
        
        pCatapulte = Catapult::genererCatapulte(pCatapulte);
        
        for(int j = 0; j < CATAPULT_ARRAY_SIZE; j++)
            std::cout << catapulte[j] << std::endl;
        
        generation[i] = catapulte;
    }
    
    return generation;
}

//Force de traction F (en N))
float forceTraction(float[CATAPULT_LENGTH] catapult, float gravite){
    return((catapult[MC]*gravite)*sin(catapult[BETA])-(catapult[MP]*gravite)*cos(catapult[ALPHA]));
}

//Moment du bras M en (en N.m)
float momentBras(float[CATAPULT_LENGTH] catapult, float gravite){
    return (forceTraction(catapult, gravite)*catapult[LB]);
}

//Moment d'inertie du bras I (en kg/m²)
float momentInertieBras(float[CATAPULT_LENGTH] catapult){
    return ((catapult[MB]*sqrt(catapult[LB]))/3);
}

//Accélération angulaire uniforme a (en rad/s²)
float accelerationAngulaire(float[CATAPULT_LENGTH] catapult, float gravite){
    return (momentBras(catapult, gravite)/momentInertieBras(catapult));
}

//Vélocité V (en m/s)
float velocite(float[CATAPULT_LENGTH] catapult, float gravite){
    return (accelerationAngulaure(catapult, gravite)*catapult[LB]);
}

//Portée P (en M)
float portee(float[CATAPULT_LENGTH] catapult, float gravite){
    return ((sqrt(velocite(catapult, gravite))/gravite)*sin(2*(90-catapult[ALPHA])));
}

//Energie d'impact (en joules) assimilée à la force cinétique transformée à l'impact
float energieImpact(float[CATAPULT_LENGTH] catapult, float gravite){
    return (0.5*catapult[MP]*sqrt(velocite(catapult, gravite)));
}

//Indique si la construction est viable
float isViable(float[CATAPULT_LENGTH] catapult, float gravite){
    float lessPart = ((sqrt(sin(catapult[ALPHA])*catapult[LB])+sqrt((cos(catapult[ALPHA])*catapult[LB])-catapult[LR]))*sin(catapult[ALPHA])*(catapult[MP]*gravite));
    float morePart  = catapult[LR]*(catapult[MC]*gravite);
    return lassPart <= morePart;
}

float energieTNT(float engergieJoule){
    return energieJoule/TNT_DENOMINATEUR;
}