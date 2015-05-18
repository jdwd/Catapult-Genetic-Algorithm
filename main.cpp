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

#define MOYENNE 0
#define VARIANCE 1
#define MEDIANE 2

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
      
    //MOYENNE 0
    //VARIANCE 1
    //MEDIANE 2
    float indicateursGeneration[3][GENERATION_NBR_MINIMUM];
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
        
        double scoreMoyenGeneration = scoreTotal / nbrElementsPerPopulation;

        //Mesure de la variance, necessite la moyenne des scores
        // 1/EFFECTIF*Epsilon((xn-MOYENNE)²)
        double varianceGeneration = 0;
        for(int cpt = 0; cpt < nbrElementsPerPopulation; cpt++){
            varianceGeneration += (pow(ancienneGeneration[cpt][SCORE]-scoreMoyenGeneration),2);
        }
        varianceGeneration = (varianceGeneration/nbrElementsPerPopulation);
        
        //Mesure de la médiane
        //Effectif de population forcément paire
        int premierTerme = ancienneGeneration[(nbrElementsPerPopulation/2)];
        int secondTerme = ancienneGeneration[(nbrElementsPerPopulation/2)+1];
        //centre de l'intervalle formé par les deux termes
        double medianeGeneration = premierTerme + ((premierTerme - secondTerme)/2);
                
        if(generationNbr <= 3){
            indicateursGeneration[MOYENNE][generationNbr]  = scoreMoyenGeneration;
            indicateursGeneration[VARIANCE][generationNbr] = varianceGeneration;
            indicateursGeneration[MEDIANE][generationNbr]  = medianeGeneration;
        }else {
            //Déplacement necessaire des résultats, car nous ne conservons que les 3 derniers
            
            indicateursGeneration[0] = indicateursGeneration[1];
            indicateursGeneration[1] = indicateursGeneration[2];
            indicateursGeneration[3] = scoreMoyenGeneration;

        }


        //if(generationNbr > 3)
        //    cout << moyennesGeneration[0] << ":" << moyennesGeneration[1] << ":" << moyennesGeneration[3] << endl;
        
        cout << "Génération n°" << generationNbr << ", score moyen:" << scoreMoyenGeneration << endl;
        
        generationNbr++;

        //Augmentation du nombre de générations ayant existé
        generationNbr++;
        
    }while( isEnEvolution(generationNbr, indicateursGeneration) );
    return 0;
}

