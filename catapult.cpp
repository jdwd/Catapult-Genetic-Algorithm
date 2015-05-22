#include "catapult.h"

//Initialisation du point de coupe statique
int Catapult::pointCoupe = 0;

//Génère un nombre aléatoire entre min et max
float Catapult::randomBetween(int min, int max){
    
    return rand() % max + min;
}

//Génère un gène en suivant son ordre de grandeur
int genererGene(int gene){
    
    switch(gene){
        case LB:
            return Catapult::randomBetween(1, 50);
        case MB:
            return Catapult::randomBetween(1, 2000);
        case BETA:
            return Catapult::randomBetween(0, 180);
        case MC:
            return Catapult::randomBetween(0, 10000);
        case MP:
            return Catapult::randomBetween(0, 10000);
        case LR:
            return Catapult::randomBetween(1, 50);
        case ALPHA:
            return Catapult::randomBetween(0, 90);
        default:
            return 0;
    }
}

//Génère une catapulte et calcule son score suivant la gravité
void Catapult::genererCatapulte(float* &catapulte, float gravite){
    
    catapulte[LB] = genererGene(LB);
    catapulte[MB] = genererGene(MB);
    catapulte[BETA] = genererGene(BETA);
    catapulte[MC] = genererGene(MC);
    catapulte[MP] = genererGene(MP);
    catapulte[LR] = genererGene(LR);
    catapulte[ALPHA] = genererGene(ALPHA);
    catapulte[SCORE] = Catapult::calculScore(catapulte, gravite);
}

//Génère toute une génération aléatoirement
float** Catapult::genererGeneration(int nbrGeneration, float gravite){
    
    //Initialisation de la génération
    float** generation = new float *[nbrGeneration];
    for(int i = 0; i < nbrGeneration; i++){
        
        //Génération de la catapulte
        float* catapulte = new float[CATAPULT_ARRAY_SIZE];
        Catapult::genererCatapulte(catapulte, gravite);
        
        //Ajout de la génération
        generation[i] = catapulte;
    }
    
    return generation;
}

//Récupération du point de coupe
int Catapult::getPointCoupe(){
    
    //Une chance sur deux de changer de point de coupe
    int changement = randomBetween(0, 1);

    //Si l'on cherche à changer, ou si le point de coupe n'a pas été initialisé
    if(changement == 1 || pointCoupe == 0){
        
        //On génère un nouveau point de coupe
        pointCoupe = randomBetween(1, CATAPULT_ELEM_NBR -1);
    }
    
    return pointCoupe;
}

//Croisement des catapultes maman1 et maman2
float* Catapult::croiserCatapultes(float* maman1, float* maman2, float gravite){
    
    //Génération du fiston
    float* fiston = new float[CATAPULT_ARRAY_SIZE];
    
    //Récupération du point de coupe
    int pointCoupe = Catapult::getPointCoupe();
    
    //Pour chaque chromosome de maman1 à gauche ou égal au point de coupe, on le donne au fiston
    for(int chromosome = 0; chromosome <= pointCoupe; chromosome++)
        fiston[chromosome] = maman1[chromosome];
    
    //Pour chaque chromosome de maman2 à droite du point de coupe, on le donne au fiston
    for(int chromosome = pointCoupe+1; chromosome <= CATAPULT_ELEM_NBR; chromosome++)
        fiston[chromosome] = maman2[chromosome];
    
    return fiston;
}

//Mutation des gènes du nouveau né
void Catapult::mutation(float* catapulte){
    
    //Pour chacun de ses chromosomes
    for(int i = 0; i < CATAPULT_ELEM_NBR; i++)
        //Avec une chance de 5%, on lui donne un gène aléatoire 
        if(randomBetween(1, 100) <= 5)
            catapulte[i] = genererGene(i);
}

//Force de traction F (en N))
float Catapult::forceTraction(float* catapult, float gravite){
    return ((catapult[MC]*gravite)*sin(catapult[BETA]*(M_PI/180))-(catapult[MP]*gravite)*cos(catapult[ALPHA]*(M_PI/180)));
}

//Moment du bras M en (en N.m)
float Catapult::momentBras(float* catapult, float gravite){
    float ft = forceTraction(catapult, gravite);
    return (ft*catapult[LB]);
}

//Moment d'inertie du bras I (en kg/m²)
float Catapult::momentInertieBras(float* catapult){
    return ((catapult[MB]*pow(catapult[LB], 2))/3);
}

//Accélération angulaire uniforme a (en rad/s²)
float Catapult::accelerationAngulaire(float* catapult, float gravite){
    float mbras = momentBras(catapult, gravite);
    float mInertie = momentInertieBras(catapult);
    return (mbras/mInertie);
}

//Vélocité V (en m/s)
float Catapult::velocite(float* catapult, float gravite){
    float aa = accelerationAngulaire(catapult, gravite);
    return (aa*catapult[LB]);
}

//Portée P (en M)
float Catapult::portee(float* catapult, float gravite){
  
    float v = velocite(catapult, gravite);
    return ((pow(v, 2)/gravite)*sin((2*(90-catapult[ALPHA]))*(M_PI/180)));
}

//Energie d'impact (en joules) assimilée à la force cinétique transformée à l'impact
float Catapult::energieImpact(float* catapult, float gravite){
    float v = velocite(catapult, gravite);
    return (0.5*catapult[MP]*pow(v, 2));
}

//Indique si la construction est viable
bool Catapult::isViable(float* catapult, float gravite){
    float lessPart = (pow(
                            (sin(catapult[ALPHA]*(M_PI/180))
                            *catapult[LB])
                            , 2)
                    +pow(
                            (
                                (cos(catapult[ALPHA]*(M_PI/180))
                                *catapult[LB])
                                -catapult[LR]
                            )
                            , 2)
                        *sin(catapult[ALPHA]*(M_PI/180))
                        *(catapult[MP]*gravite));
    float morePart  = catapult[LR]*(catapult[MC]*gravite);
    return (lessPart <= morePart);
}

//Conversion d'une energie en joue en TNT
float Catapult::energieTNT(float energieJoule){
    return (energieJoule/TNT_DENOMINATEUR);
}

//Définit le score d'une catapulte
float Catapult::calculScore(float* &catapult, float gravite){
    //Une catapulte se doit d'envoyer un boulet à une cible à une distance D avec l'énergie cinétique C la plus élevée
    float score=0;
    float viableInd=1;
    float e = energieImpact(catapult, gravite);
    float p = portee(catapult, gravite);
    float ponderationPortee;
    float ponderationEnergie;

    //Dans un premier temps il nous faut déterminer si la construction est viable
    if(!isViable(catapult, gravite)){
        viableInd=PONDERATION_VIABLE;
    }

   //Indicateur de portée
    float porteeInd = exp(-(pow((p-DISTANCE), 2))/10000000);
    float energieInd = (atan(e/1000000))/(M_PI/2);
    
    ponderationEnergie = (e*PONDERATION_ENERGIE);
    
    catapult[ENERGIE] = e;
    catapult[PORTEE] = p;
    
    return (energieInd+porteeInd)*viableInd;
    
}
