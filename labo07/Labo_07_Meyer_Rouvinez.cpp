/*
---------------------------------------------------------------------------------------
Laboratoire : Labo07

Fichier     : Labo07_Meyer_Rouvinez.cpp

Auteur(s)   : 

Date        : Nov 29, 2016

But         : 

Remarque(s) : 

Compilateur : gcc version 6.2.1 20160916 (Red Hat 6.2.1-2) (GCC)
---------------------------------------------------------------------------------------
*/



#include <cmath>
#include "IO.h"
#include "utils.h"






int spawn(int& posExploX, int& posExploY, int& posTreasureX, int& posTreasureY, int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X, int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y, int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX, const int minX, const int minY, const int maxX, const int maxY);
int move(int& posExploX, int& posExploY);
State checkPos(int& posExplo, int& posTreasure, int& posLake1, int& radLake1, int& posLake2, int& radLake2, int& posLake3, int& radLake3, const int& min, const int& max);
int defineState(State stateX, State stateY, State& finalState);





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
            LAKE_R_MAX =  min(MAP_X_MAX,MAP_Y_MAX)/2;


    do {
        cout << "Ce programme calcule la probabilité pour N chercheurs de trouver un trésor sur une carte de taille X Y."
             << endl << endl;

        nbExplo = input("Entrez le nombre d'explorateurs", NB_EXPLO_MIN, NB_EXPLO_MAX);

    /*    mapX    = input("Entrez la largeur de la carte :",MAP_X_MIN, MAP_X_MAX );
        mapY    = input("Entrez la hauteur de la carte :",MAP_Y_MIN, MAP_Y_MAX ); */

        int foundTreasure = 0,
            avgSteps      = 0;

        State finalState=State::WALK,
                               stateX,
                               stateY;

        for(int explo=0;explo<nbExplo;explo++){

            spawn(posExploX, posExploY,
                  posTreasureX,  posTreasureY,
                  posLake1X,  posLake1Y,  radLake1,
                  posLake2X,  posLake2Y,  radLake2,
                  posLake3X,  posLake3Y,  radLake3,
                  LAKE_R_MIN, LAKE_R_MAX,
                  MAP_X_MIN,  MAP_Y_MIN, MAP_X_MAX, MAP_Y_MAX);
            int step;
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

int area(int mapX, int mapY){
    static int area;
    if(!area)
        area = mapX*mapY;
    return area;
}
int genRandomVal(const int minVal, const int maxVal){

    /*TODO CHANGE RESPONSE TO SOMETHING MORE CIVILISED THAN KILL*/
    if(minVal>=maxVal){
        return EXIT_FAILURE;
    }
    int range;
    range = maxVal-minVal;
    return rand()%((range*2 +1)-range);

}

int norme(int x, int y){
    return (int)sqrt(x*x+y*y);
}
int spawn(int& posExploX, int& posExploY, int& posTreasureX, int& posTreasureY, int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X, int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y, int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX, const int minX, const int minY, const int maxX, const int maxY){
    /*TODO CHANGE OR FOR AND*/
    static bool first;
    if(!first){
        posLake1X = genRandomVal(minX, maxX);
        posLake1Y = genRandomVal(minY, maxY);
        radLake1  = genRandomVal(LAKE_R_MIN, LAKE_R_MAX);

        do{
        posLake2X = genRandomVal(minX, maxX);
        posLake2Y = genRandomVal(minY, maxY);
        radLake2 = genRandomVal(LAKE_R_MIN, min(LAKE_R_MAX, norme(posLake2X-posLake1X,posLake2Y-posLake1Y))-1);
        }while(norme(posLake2X-posLake1X,posLake2Y-posLake1Y)<=radLake1);

        do{
        posLake3X = genRandomVal(minX, maxX);
        posLake3Y = genRandomVal(minY, maxY);
        radLake3 = genRandomVal(LAKE_R_MIN, min(min(LAKE_R_MAX, norme(posLake3X-posLake2X,posLake3Y-posLake2Y)),norme(posLake3X-posLake1X,posLake3Y-posLake1Y))-1);

        }while(norme(posLake3X-posLake1X,posLake3Y-posLake1Y)<=radLake1 ||
               norme(posLake3X-posLake2X,posLake3Y-posLake2Y)<=radLake2 ||
                radLake3+radLake1>=norme(posLake3X-posLake1X, posLake3Y-posLake1Y) ||
                radLake3+radLake2>=norme(posLake3X-posLake2X, posLake3Y-posLake2Y));

/*
        do{
            cout << radLake2+radLake1 << " : " << norme(posLake2X-posLake1X, posLake2Y-posLake1Y) << endl;
        }while(radLake2+radLake1>=norme(posLake2X-posLake1X, posLake2Y-posLake1Y));
        do {
            cout << radLake3+radLake1 << " : " << norme(posLake3X-posLake1X, posLake3Y-posLake1Y) << endl;
            cout << radLake3+radLake2 << " - " << norme(posLake3X-posLake2X, posLake3Y-posLake2Y) << endl;
        }while();
*/

    /*TREASURE*/
        do{
            posTreasureX = genRandomVal(minX, maxX);
            posTreasureY = genRandomVal(minY, maxY);
        }while(norme(posTreasureX-posLake1X, posTreasureY-posLake1Y ) <= radLake1 || norme(posTreasureX-posLake2X, posTreasureY-posLake2Y ) <= radLake2 || norme(posTreasureX-posLake3X, posTreasureY-posLake3Y ) <= radLake3);
    }
    first = true;
    /*EXPLO*/
    do{
        posExploX = genRandomVal(minX, maxX);
        posExploY = genRandomVal(minY, maxY);

    }while((norme(posExploX-posLake1X, posExploY-posLake1Y) <= radLake1) || (norme(posExploX-posLake2X, posExploY-posLake2Y) <= radLake2) || (norme(posExploX-posLake3X, posExploY-posLake3Y) <= radLake3));

    return EXIT_SUCCESS;
}

int move(int& posExploX, int& posExploY){

    int movement = genRandomVal(1,4);
    posExploX += movement%2 ? movement-2 : 0;
    posExploY += movement%2 ? 0 : movement-2;
    return EXIT_SUCCESS;
}
State checkPos(int& posExplo, int& posTreasure, int& posLake1, int& radLake1, int& posLake2, int& radLake2, int& posLake3, int& radLake3, const int& min, const int& max){
    /*riche perdu noyé epuisé nothing*/
    /*  1     2     3    -      0 */

	return posExplo < min ? State::LOST : posExplo > max ? State::LOST :
           posExplo == posTreasure ? State::RICH :
           (norme(posExplo,posLake1) <= radLake1) ? State::DROWND :
           (norme(posExplo,posLake2) <= radLake2) ? State::DROWND :
           (norme(posExplo,posLake3) <= radLake3) ? State::DROWND : State::WALK;

}
int defineState(State stateX, State stateY, State& finalState) {
    if (stateX == State::LOST || stateY == State::LOST) {
        finalState = State::LOST;
        return 1;
    } else if (stateX == State::RICH && stateY == State::RICH) {
        finalState = State::RICH;
        return 1;
    } else if (stateX == State::DROWND && stateY == State::DROWND) {
        finalState = State::DROWND;
        return 1;
    } else {
        finalState = State::WALK;
        return 0;
    }
}
