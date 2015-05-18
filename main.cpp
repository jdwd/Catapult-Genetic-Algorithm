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


// Méthode permettant de déterminer si les générations évoluent dans le bon sens 
//et sont capable de produire une nouvelle génération plus évoluée
bool isEvoluting(int generationNbr, float moyennesGeneration[3][GENERATION_NBR_MINIMUM]) {

    // Determiner si la génération est à même de produire une génération plus performante
    // revient à définir si :
    // - La moyenne augmente : cela signifie que la génération entière évolue, mais pas forcément que la meilleure caatapute de chaque génération évolue donc l'indice n'est pas suffisant : NOTION d'ECART
    // - La médiane augmente : autre indicateur de l'évolution d'une population, n'est pas affectée par les valeurs extremes, nous lui donnons donc tout autant de crédit : NOTION DE DISPERSION
    // - La variance diminue : cet indicateur permet de vérifier si l'évolution des individus convergent vers un seul et même individut, les évolutions vont donc dans le même sens, à l'inverse l'évolution se disperse et n'arrvie pas à s'orienter
     
    //1ere étape : calcul du coefficient directeur
    //2eme étape : calcul du pourcentage d'évolution
    //3eme étape : calcul du coefficient d'évolution positif

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
            cin.ignore(10000, '\n');
        }
    } while ((nbrElementsPerPopulation == 0) || (!Utils::isPairNumber(nbrElementsPerPopulation)));

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
    do {
        //Tri de la génération du plus haut score au plus faible
        Utils::sort(generation, nbrElementsPerPopulation);

        //Si la première génération a été traitée, purge des éléments
        if (generationNbr > 0) {
            for (int i = 0; i < nbrElementsPerPopulation; i++) {
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
        for (int cpt = 0; cpt < nbrElementsPerPopulation; cpt += 2) {

            //On ajoute le score de l'élément A et B
            scoreTotal += ancienneGeneration[cpt][SCORE] + ancienneGeneration[cpt + 1][SCORE];

            //On croise les catapultes A et B pour en créer un enfant
            generation[cpt] = Catapult::croiserCatapultes(ancienneGeneration[cpt], ancienneGeneration[cpt + 1], G_TERRE);
            //Mutation du nouveau né
            Catapult::mutation(generation[cpt]);

            //Idem pour le frère
            generation[cpt + 1] = Catapult::croiserCatapultes(ancienneGeneration[cpt], ancienneGeneration[cpt + 1], G_TERRE);
            Catapult::mutation(generation[cpt + 1]);
        }

        double scoreMoyenGeneration = scoreTotal / nbrElementsPerPopulation;

        //Mesure de la variance, necessite la moyenne des scores
        // 1/EFFECTIF*Epsilon((xn-MOYENNE)²)
        double varianceGeneration = 0;
        for (int cpt = 0; cpt < nbrElementsPerPopulation; cpt++) {
            varianceGeneration += (pow((ancienneGeneration[cpt][SCORE] - scoreMoyenGeneration), 2));
        }
        varianceGeneration = (varianceGeneration / nbrElementsPerPopulation);

        //Mesure de la médiane
        //Effectif de population forcément paire
        float premierTerme = ancienneGeneration[(nbrElementsPerPopulation / 2)][SCORE];
        float secondTerme = ancienneGeneration[(nbrElementsPerPopulation / 2) + 1][SCORE];
        //centre de l'intervalle formé par les deux termes
        double medianeGeneration = premierTerme + ((premierTerme - secondTerme) / 2);

        //Si les 3 premières générations n'ont pas encore été générées, on les ajoute "naturellement" au tableau        
        if (generationNbr <= 3) {
            indicateursGeneration[MOYENNE][generationNbr] = scoreMoyenGeneration;
            indicateursGeneration[VARIANCE][generationNbr] = varianceGeneration;
            indicateursGeneration[MEDIANE][generationNbr] = medianeGeneration;
        } else {
            //Déplacement necessaire des résultats, car nous ne conservons que les 3 derniers
            //On décale les scores sur la gauche, on cherche à avoir le score le plus récent en dernier

            //MOYENNE
            indicateursGeneration[MOYENNE][0] = indicateursGeneration[MOYENNE][1];
            indicateursGeneration[MOYENNE][1] = indicateursGeneration[MOYENNE][2];
            indicateursGeneration[MOYENNE][3] = scoreMoyenGeneration;

            //VARIANCE
            indicateursGeneration[VARIANCE][0] = indicateursGeneration[VARIANCE][1];
            indicateursGeneration[VARIANCE][1] = indicateursGeneration[VARIANCE][2];
            indicateursGeneration[VARIANCE][3] = varianceGeneration;

            //MEDIANE
            indicateursGeneration[MEDIANE][0] = indicateursGeneration[MEDIANE][1];
            indicateursGeneration[MEDIANE][1] = indicateursGeneration[MEDIANE][2];
            indicateursGeneration[MEDIANE][3] = medianeGeneration;
        }

        //if(generationNbr > 3)
        //    cout << moyennesGeneration[0] << ":" << moyennesGeneration[1] << ":" << moyennesGeneration[3] << endl;

        cout << "Génération n°" << generationNbr << endl;
        cout << "  -Moyenne: " << scoreMoyenGeneration << endl;
        cout << "  -Variance: " << varianceGeneration << endl;
        cout << "  -Médiane: " << medianeGeneration << endl;

        //Augmentation du nombre de générations ayant existé
        generationNbr++;

    } while (isEvoluting(generationNbr, indicateursGeneration));
    return 0;
}

