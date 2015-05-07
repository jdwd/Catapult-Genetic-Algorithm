#include "catapult.h"

//TODO Tableau de float

/* Fonctions relatice à la catapulte */


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
