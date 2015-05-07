/* 
 * File:   utils.cpp
 * Author: jdwd
 *
 */

//Fonction permettant de vérifier si un nombre est pair
bool isPairNumber(int number){
    return ((number%2)==0);
}

//Fonction permettant de trier le tableau de catapulte par son score
void sort(int* tab, int length){
    //Principe : tri par permutation des éléments du tableau
     int temp = 0, j, i;
     
        //Parcours de chaque élément du tableau
        for(i = 1 ; i < length ; i++){
            //Parcours des éléments précédents celui courant
            for(j=0 ; j<(length-i) ; j++){
                //Si le score du courant est supérieur que son précédent alors on le remonte d'une case
                if(tab[j][SCORE] > tab[j+1][SCORE]){
                    temp = tab[j];
                    tab[j] = tab[j+1];
                    tab[j+1] = temp;
                }
            }
        }
    }
}