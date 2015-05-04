#define CATAPULT_ELEM_NBR 8;
#define CATAPULT_LENGTH 9;

#define HB 0;           //la hauteur de la butée
#define LB 1;           //la longueur du bras Lb (en mètres)
#define MB 2;           //la masse du bras mb (en kilos)
#define BETA 3;         //l'angle de la force de traction avec le bras β (en degrés)
#define MC 4;           //la masse du contrepoids responsable de la force de traction mc (en kilos)
#define MP 5;           //la masse du projectile mp (en kilos)
#define LR 6;           //la longueur de la base Lr (en mètres)
#define ALPHA 7;        //l'angle α (en degrés)

#define SCORE 8;

#define TNT_DENOMINATEUR 4184;
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



