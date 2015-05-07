#include <iostream>
#include "catapult.h"
#include "utils.h"

/*
 * Définition des constantes de pesanteur
 */
#define G_TERRE 9.81;       //m.s^-2
#define G_LUNE 1.62;        //m.s^-2
#define G_JUPITER 24.90;    //m.s^-2

/*
 * Génération d'une population de X individu
 * Test de chaque individus
 * Selection des meilleurs
 * Création d'hybrides dans une nouvelle population
 * Boucler tant que résultat n'évolue plus
 * 
 * OBJECTIF : éclater une cible à une distance d (energie cinétique)
 */


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    srand(time(NULL));
        
    int nbrGeneration = 10;
    
    float** generation = Catapult::genererGeneration(nbrGeneration);
    
    for(int i = 0; i < nbrGeneration; i++)
            for(int j = 0; j < CATAPULT_ARRAY_SIZE; j++)
                std::cout << i << ":" << j << " > " << generation[i][SCORE] << std::endl;

    
    Utils::sort(generation, nbrGeneration);
     
    for(int j = 0; j < nbrGeneration; j++)
        cout << generation[j][SCORE] << endl;
    
    return 0;
}

