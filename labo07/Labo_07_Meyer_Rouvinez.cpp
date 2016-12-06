/*
---------------------------------------------------------------------------------------
Laboratoire : Labo07

Fichier     : Labo07_Meyer_Rouvinez.cpp

Auteur(s)   : 

Date        : Nov 29, 2016

But         : How many steps are needed to find a treasure on a map with three lake

Remarque(s) : Le programme doit afficher le statut de chaque chercheur
				Le nombre de pas du chercheur
				Son état : Riche, Perdu, Noyé, Epuisé
			  Les lacs ne doivent pas se chevaucher, le centre étant sur la carte mais peuvent dépasser. Les arrondis se feront à 0.5.
			  Le trésor et le départ doivent être distincts, sur la carte hors d’un lac
			  En fin d’expérience, il est possible de recommencer une simulation.

Compilateur : gcc version 6.2.1 20160916 (Red Hat 6.2.1-2) (GCC)
---------------------------------------------------------------------------------------
*/



#include <cmath>
#include "IO.h"
#include "utils.h"
#include "model.h"



int main() {
    srand(time(NULL));


    int     nbExplo,
            posExploX,
            posExploY,
            posTreasureX,
            posTreasureY,
            posLake1X,
            posLake1Y,
            radLake1,
            posLake2X,
            posLake2Y,
            radLake2,
            posLake3X,
            posLake3Y,
            radLake3;


    const int NB_EXPLO_MIN = 1,
            NB_EXPLO_MAX = INT_MAX,
            MAP_X_MIN = 1,
            MAP_Y_MIN = 1,
            MAP_X_MAX = 100,
            MAP_Y_MAX = 200,
            LAKE_R_MIN = 0,
			//limit the area for lake
            LAKE_R_MAX =  min(MAP_X_MAX,MAP_Y_MAX)/2;


    do {
        cout << "Ce programme calcule la probabilité pour N chercheurs de trouver un trésor sur une carte de taille X Y."
             << endl << endl;

        nbExplo = input("Entrez le nombre d'explorateurs", NB_EXPLO_MIN, NB_EXPLO_MAX);

        int foundTreasure = 0,
            avgSteps      = 0;

        State finalState=State::WALK,
                               stateX,
                               stateY;
//generate the position for treasure, lake and explo
        for(int explo=0;explo<nbExplo;explo++){

            spawn(posExploX, posExploY,
                  posTreasureX,  posTreasureY,
                  posLake1X,  posLake1Y,  radLake1,
                  posLake2X,  posLake2Y,  radLake2,
                  posLake3X,  posLake3Y,  radLake3,
                  LAKE_R_MIN, LAKE_R_MAX,
                  MAP_X_MIN,  MAP_Y_MIN, MAP_X_MAX, MAP_Y_MAX,false);

            int step;
            //move the explo and check if they're not drown or lost or found the treasure
            for (step=0; step<MAP_X_MAX*MAP_Y_MAX;++step){

                move(posExploX,posExploY);
                
                stateX = checkPos(posExploX,  posTreasureX,  posLake1X,  radLake1,  posLake2X,  radLake2,  posLake3X,  radLake3, MAP_X_MIN, MAP_X_MAX);
                stateY = checkPos(posExploY,  posTreasureY,  posLake1Y,  radLake1,  posLake2Y,  radLake2,  posLake3Y,  radLake3, MAP_Y_MIN, MAP_Y_MAX);
                if(defineState(stateX, stateY, finalState))
                    break;
            }
            

            printState(finalState, explo, step);
            cout << posExploX << " : "  << posExploY << endl;
            foundTreasure += finalState == State::RICH ? 1 : 0;
            avgSteps += finalState == State::RICH ? step : 0;

        }
        printStats(foundTreasure, nbExplo, avgSteps);
        cout << posTreasureX << " : " << posTreasureY << endl;

    }while(doAgain());

    toQuit("Presser ENTER pour quitter..");
    return EXIT_SUCCESS;
}
