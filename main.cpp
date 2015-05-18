#include <iostream>
#include "catapult.h"
#include "utils.h"

/*
 * Définition des constantes de pesanteur
 */
#define G_TERRE 9.81        //m.s^-2
#define G_LUNE 1.62         //m.s^-2
#define G_JUPITER 24.90     //m.s^-2
#define DISTANCE 300        //m

#define GENERATION_NBR_MINIMUM 3
#define ECART_VARIATION 0.05f

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
 
    if(generationNbr <= GENERATION_NBR_MINIMUM)
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
    
    //Initialisation du random
    srand(time(NULL));
    
    //Récupération du nombre d'individus à mettre en génération
    int nbrElementsPerPopulation;
    do {
        cout << "Enter a number (pair, n > 0) : ";
        if (!(cin >> nbrElementsPerPopulation)) {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }    
    }
    while ((nbrElementsPerPopulation == 0) || (!Utils::isPairNumber(nbrElementsPerPopulation)));
      
    //Permet le stockage des moyennes
    float moyennesGeneration[GENERATION_NBR_MINIMUM];
    //Nombre de générations
    int generationNbr = 0;
    
    //Contient l'ancienne génération
    float** ancienneGeneration;
    //Contient la génération en cours, initialisation aléatoire de la 1ère population
    float** generation = Catapult::genererGeneration(nbrElementsPerPopulation, G_TERRE);
      
    //Tant que nos éléments évoluent
    do{
        //Tri de la génération du plus haut score au plus faible
        Utils::sort(generation, nbrElementsPerPopulation);

        //Si la première génération a été traitée, purge des éléments
        if(generationNbr > 0){
            for(int i = 0; i < nbrElementsPerPopulation; i++){
                delete ancienneGeneration[i];
            }
            delete ancienneGeneration;
        }
        
        //La génération a été calculée, on les passe donc en anciens (à reproduire)
        ancienneGeneration = generation;
        
        //Initialisation de la nouvelle génération
        generation = new float *[nbrElementsPerPopulation];

        //Score total de la génération
        double scoreTotal = 0;

        //Pour tous les 2 éléments de la population
        for(int cpt = 0; cpt < nbrElementsPerPopulation; cpt+=2){
            
            //On ajoute le score de l'élément A et B
            scoreTotal += ancienneGeneration[cpt][SCORE] + ancienneGeneration[cpt+1][SCORE];
            
            //On croise les catapultes A et B pour en créer un enfant
            generation[cpt] = Catapult::croiserCatapultes( ancienneGeneration[cpt], ancienneGeneration[cpt+1], G_TERRE );
            //Mutation du nouveau né
            Catapult::mutation(generation[cpt]);
            
            //Idem pour le frère
            generation[cpt+1] = Catapult::croiserCatapultes( ancienneGeneration[cpt], ancienneGeneration[cpt+1], G_TERRE );
            Catapult::mutation(generation[cpt+1]);
        }
        
        //Calcul de la moyenne de la génération
        double scoreMoyenGeneration = scoreTotal / nbrElementsPerPopulation;
        
        //Si les 3 premières générations n'ont pas encore été générées, on les ajoute "naturellement" au tableau
        if(generationNbr < 3)
            moyennesGeneration[generationNbr] = scoreMoyenGeneration;
        else {          
            //Sinon, on décale les scores sur la gauche, on cherche à avoir le score le plus récent en dernier
            moyennesGeneration[0] = moyennesGeneration[1];
            moyennesGeneration[1] = moyennesGeneration[2];
            moyennesGeneration[2] = scoreMoyenGeneration;
        }

        //Augmentation du nombre de générations ayant existé
        generationNbr++;
        
        cout << "Generation: " << generationNbr << endl;

    }while( isEnEvolution(generationNbr, moyennesGeneration) );
    return 0;
}

