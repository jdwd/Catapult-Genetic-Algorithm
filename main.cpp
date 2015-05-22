#include <iostream>
#include "catapult.h"
#include "utils.h"

/*
 * Définition des constantes de pesanteur
 */
#define G_TERRE 9.81        //m.s^-2
#define G_LUNE 1.62         //m.s^-2
#define G_JUPITER 24.90     //m.s^-2

#define GENERATION_NBR_MINIMUM 10
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
bool isEvoluting(int generationNbr, long double indicesGeneration[3][3]) {
    
    if(generationNbr < GENERATION_NBR_MINIMUM)
        return true;
    
    // Determiner si la génération est à même de produire une génération plus performante
    // revient à définir si :
    // - La moyenne augmente : cela signifie que la génération entière évolue, mais pas forcément que la meilleure caatapute de chaque génération évolue donc l'indice n'est pas suffisant : NOTION d'ECART
    // - La médiane augmente : autre indicateur de l'évolution d'une population, n'est pas affectée par les valeurs extremes, nous lui donnons donc tout autant de crédit : NOTION DE DISPERSION
    // - La variance diminue : cet indicateur permet de vérifier si l'évolution des individus convergent vers un seul et même individut, les évolutions vont donc dans le même sens, à l'inverse l'évolution se disperse et n'arrvie pas à s'orienter
     
    //MOYENNE
    long double generationPrecMoyenne = Utils::coefDirecteur(indicesGeneration[MOYENNE][0], indicesGeneration[MOYENNE][1]);
    long double generationCurrMoyenne = Utils::coefDirecteur(indicesGeneration[MOYENNE][1], indicesGeneration[MOYENNE][2]);
    long double evolutionMoyenne = generationCurrMoyenne - generationPrecMoyenne;
    
    //MEDIANE
    long double generationPrecMediane = Utils::coefDirecteur(indicesGeneration[MEDIANE][0], indicesGeneration[MEDIANE][1]);
    long double generationCurrMediane = Utils::coefDirecteur(indicesGeneration[MEDIANE][1], indicesGeneration[MEDIANE][2]);    
    long double evolutionMediane = generationCurrMediane - generationPrecMediane;
    
    //VARIANCE
    long double generationPrecVariance = Utils::coefDirecteur(indicesGeneration[VARIANCE][0], indicesGeneration[VARIANCE][1]);
    long double generationCurrVariance = Utils::coefDirecteur(indicesGeneration[VARIANCE][1], indicesGeneration[VARIANCE][2]);    
    long double evolutionVariance = generationCurrVariance - generationPrecVariance;
    
    
    cout << "evolutionMoyenne: "<<evolutionMoyenne<<endl;
    cout << "evolutionMediane: "<<evolutionMediane<<endl;
    cout << "evolutionVariance: "<<evolutionVariance<<endl;
    
    //Si le variance diminue, et ce de plus de 2% alors la génération évolue toujours
    bool variance = (evolutionVariance < -0.02);
    //Si la médiane ou la moyenne est toujours en augmentation alors la génération évolue
    bool med = (evolutionMediane > 0.06 || evolutionMoyenne > 0.08);
    
    return (variance || med);
}

/*
 * 
 */
int main(int argc, char** argv) {

    cout.precision(60);
    
    //Initialisation du random
    if(argc > 1)
        srand(atoi(argv[0]));
    else 
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

    int astreChoix;
    do{
        cout << "Sur quel astre voulez-vous effectuer ce test ?" << endl;
        cout << "(1) Terre" << endl << "(2) Lune" << endl << "(3) Jupiter" << endl;
        if (!(cin >> astreChoix)) {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }while( astreChoix < 1 || astreChoix > 3 );
    
    float astre;
    switch(astreChoix){
        case 1:
            astre = G_TERRE;
            break;
        case 2:
            astre = G_LUNE;
            break;
        case 3:
            astre = G_JUPITER;
            break;
    }
    
    //MOYENNE 0
    //VARIANCE 1
    //MEDIANE 2
    long double indicateursGeneration[3][3];
    int generationNbr = 0;

    //Contient l'ancienne génération
    float** ancienneGeneration;
    //Contient la génération en cours, initialisation aléatoire de la 1ère population
    float** generation = Catapult::genererGeneration(nbrElementsPerPopulation, astre);

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

        cout << "Meilleure catapulte de la génération " << generationNbr << endl;
        cout << "\t Score: \t\t" << generation[0][SCORE] << " points" << endl;
        cout << "\t Longueur bras: \t" << generation[0][LB] << " mètres" << endl;
        cout << "\t Masse bras: \t\t" << generation[0][MB] << " kilogrammes" << endl;
        cout << "\t Angle force traction: \t" << generation[0][BETA] << " degrés" << endl;
        cout << "\t Masse contrepoids: \t" << generation[0][MC] << " kilogrammes" << endl;
        cout << "\t Masse projectile: \t" << generation[0][MP] << " kilogrammes" << endl;
        cout << "\t Longueur base: \t" << generation[0][LR] << " mètres" << endl;
        cout << "\t Angle alpha: \t\t" << generation[0][ALPHA] << " degrés" << endl;
        cout << "\t Energie: \t\t" << generation[0][ENERGIE] << " joules" << endl;
        cout << "\t Portée: \t\t" << generation[0][PORTEE] << " mètres" << endl;
        
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
            generation[cpt] = Catapult::croiserCatapultes(ancienneGeneration[cpt], ancienneGeneration[cpt + 1]);
            //Mutation du nouveau né
            Catapult::mutation(generation[cpt]);
            
            //Calcul du score
            generation[cpt][SCORE] = Catapult::calculScore(generation[cpt], astre);
            
            //Idem pour le frère
            generation[cpt + 1] = Catapult::croiserCatapultes(ancienneGeneration[cpt + 1], ancienneGeneration[cpt], astre);
            Catapult::mutation(generation[cpt + 1]);
            
            //Calcul du score
            generation[cpt + 1][SCORE] = Catapult::calculScore(generation[cpt + 1], astre);
            
        }

        long double scoreMoyenGeneration = scoreTotal / nbrElementsPerPopulation;
        
        //Mesure de la variance, necessite la moyenne des scores
        // 1/EFFECTIF*Epsilon((xn-MOYENNE)²)
        long double varianceGeneration = 0;
        for (int cpt = 0; cpt < nbrElementsPerPopulation; cpt++) {
            varianceGeneration += (pow((ancienneGeneration[cpt][SCORE] - scoreMoyenGeneration), 2));
        }
        varianceGeneration = (varianceGeneration / nbrElementsPerPopulation);

        //Mesure de la médiane
        //Effectif de population forcément paire
        long double premierTerme = ancienneGeneration[(nbrElementsPerPopulation / 2)][SCORE];
        long double secondTerme = ancienneGeneration[(nbrElementsPerPopulation / 2) + 1][SCORE];
        //centre de l'intervalle formé par les deux termes
        long double medianeGeneration = premierTerme + ((premierTerme - secondTerme) / 2);

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
            indicateursGeneration[MOYENNE][2] = scoreMoyenGeneration;

            //VARIANCE
            indicateursGeneration[VARIANCE][0] = indicateursGeneration[VARIANCE][1];
            indicateursGeneration[VARIANCE][1] = indicateursGeneration[VARIANCE][2];
            indicateursGeneration[VARIANCE][2] = varianceGeneration;

            //MEDIANE
            indicateursGeneration[MEDIANE][0] = indicateursGeneration[MEDIANE][1];
            indicateursGeneration[MEDIANE][1] = indicateursGeneration[MEDIANE][2];
            indicateursGeneration[MEDIANE][2] = medianeGeneration;
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
    
    cout << "Nombre de générations: " << generationNbr << endl;
    
    return 0;
}

