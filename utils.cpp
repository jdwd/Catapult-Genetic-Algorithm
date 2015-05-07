/* 
 * File:   utils.cpp
 * Author: jdwd
 *
 */

#include "utils.h"


    //Fonction permettant de vérifier si un nombre est pair
    bool Utils::isPairNumber(int number){
        return ((number%2)==0);
    }

    //Fonction permettant de trier le tableau de catapulte par son score
    void Utils::sort(float** tab, int length){
        //Principe : tri par permutation des éléments du tableau
        float* temp = 0;
        int j, i;
        //Parcours de chaque élément du tableau
        for(i = 0 ; i < length ; i++){

            //Récupération du score courant
            float currIndexScore = tab[i][SCORE];
            float compareScore;

            //Parcours des éléments précédents celui courant
            for(j=0; j<(i); j++){
                //Récupéeation du score de l'élément à comparer
                compareScore = tab[j][SCORE];  
                if(currIndexScore > compareScore){
                    temp = tab[j];
                    tab[j] = tab[i];
                    tab[i] = temp;
                }
            }


        }
    }
