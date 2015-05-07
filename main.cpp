#include <iostream>
#include "catapult.h"
#include "utils.h"

/*
 * Définition des constantes de pesanteur
 */
#define G_TERRE 9.81;       //m.s^-2
#define G_LUNE 1.62;        //m.s^-2
#define G_JUPITER 24.90;    //m.s^-2

#define GENERATION_NBR_MINIMUM 3
#define ECART_VARIATION 0.05f

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

//TODO A VERIFIER
bool isEnEvolution(int generationNbr, float moyennesGeneration[GENERATION_NBR_MINIMUM]){
 
    if(generationNbr < GENERATION_NBR_MINIMUM)
        return true;
    
    int meilleurScoreIndex = -1;
    
    for(int i = 0; i < GENERATION_NBR_MINIMUM; i++)
        if(moyennesGeneration[i] > moyennesGeneration[meilleurScoreIndex] || meilleurScoreIndex == -1)
            meilleurScoreIndex = i;
    
    float coefficient[GENERATION_NBR_MINIMUM -1];
    int cpt = 0;
    for(int i = 0; i < GENERATION_NBR_MINIMUM; i++){
        if(i != meilleurScoreIndex){
            coefficient[cpt] = 1 - (moyennesGeneration[i] / moyennesGeneration[meilleurScoreIndex]);
            cpt++;
        }
    }
    
    return (coefficient[0] < ECART_VARIATION && coefficient[1] < ECART_VARIATION);
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    srand(time(NULL));
    
    //Récupération du nombre d'individus à mettre en génération
    int nbrGeneration;
    do {
        cout << "Enter a number (pair, n > 0) : ";
        if (!(cin >> nbrGeneration)) {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }    
    }
    while ((nbrGeneration == 0) || (!Utils::isPairNumber(nbrGeneration)));
      
    float moyennesGeneration[GENERATION_NBR_MINIMUM];
    int generationNbr = 1;
    
    float** ancienneGeneration;
    float** generation = Catapult::genererGeneration(nbrGeneration);
      
    do{
        Utils::sort(generation, nbrGeneration);
        /*
        for(int i = 0; i < nbrGeneration; i++)
                for(int j = 0; j < CATAPULT_ARRAY_SIZE; j++)
                    std::cout << i << ":" << j << " > " << generation[i][j] << std::endl;
        */
        //for(int j = 0; j < nbrGeneration; j++)
        //    cout << generation[j][SCORE] << endl;

        ancienneGeneration = generation;
        generation = new float *[nbrGeneration];

        //TODO CALCUL MOYENNE
        for(int cpt = 0; cpt < nbrGeneration; cpt+=2){
            generation[cpt] = Catapult::croiserCatapultes( ancienneGeneration[cpt], ancienneGeneration[cpt+1] );
            Catapult::mutation(generation[cpt]);
            generation[cpt+1] = Catapult::croiserCatapultes( ancienneGeneration[cpt], ancienneGeneration[cpt+1] );
            Catapult::mutation(generation[cpt+1]);
        }
        
        generationNbr++;

        /*cout << "ENFANTS" << endl;
        for(int i = 0; i < nbrGeneration; i++)
                for(int j = 0; j < CATAPULT_ARRAY_SIZE; j++)
                    std::cout << i << ":" << j << " > " << generation[i][j] << std::endl;
        */
    }while( isEnEvolution(generationNbr, moyennesGeneration) );
    return 0;
}

