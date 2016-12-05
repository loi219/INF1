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


#include <iostream>
#include <iomanip>
#include <climits>
#include <string>
#include <cmath>

#define CLEAR_BUFFER cin.ignore(INT_MAX, '\n')
#define WIDTH_INT_BASE 4u
#define WIDTH_TEXT_BASE 30u

enum class State {RICH,LOST,DROWND,SPENT,WALK};

using namespace std;


/*
 * Goal: asks the user if he wants to restart or exit the program
 *       checks if the inputs are valid
 *
 * parameters:
 *      none
 *
 * @return:
 *      isValid: boolean containing the answer of the user to the question
 *               "do you want to start again?"
 */
bool doAgain();

/*
 * Goal: asks the user which values he wants to use for the program
 *       checks if the inputs are valid
 *       if the inputs are not valid, asks again the user to enter the values
 *
 * parameters:
 *      @param message   : string that contains the message asking the user about
 *                         the values needed in the program
 *      @param limitMin  : int that contains the lowest integer that the user
 *                         is allowed to enter
 *      @param limitMax  : int that contains the highest integer that the user
 *                         is allowed to enter
 *      @param error     : string that contains a message noticing the user that
 *                         he entered an invalid value
 *      @param WIDTH_INT : const int that contains the width of the left margin
 *      @param WIDTH_TEXT: const int that contains a width that will be used
 *                         to align the text that is displayed
 *
 *
 * @return:
 *      userInput : int contianing the value that the user entered
 */
int input(const string& message, int limitMin, int limitMax, const int WIDTH_INT=WIDTH_INT_BASE, const int WIDTH_TEXT=WIDTH_TEXT_BASE, const string error="Mauvaise saisie. Veuillez reessayez");

int spawn(int& posExploX, int& posExploY, int& posTreasureX, int& posTreasureY, int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X, int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y, int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX, const int minX, const int minY, const int maxX, const int maxY);
int move(int& posExploX, int& posExploY);
<<<<<<< HEAD
State checkPos(int& posExplo, int& posTreasure, int& posLake1, int& radLake1, int& posLake2, int& radLake2, int& posLake3, int& radLake3, const int& min, const int& max);
=======
int checkPos(int posExplo, int posTreasure, int posLake1, int radLake1, int posLake2, int radLake2, int posLake3, int radLake3, const int min, const int max);

>>>>>>> master

string printPos(State intState);
/*
 * Goal: Show a prompt for the user to definitely quit the program.
 *
 * parameters:
 *      @param message : string containing the exit message
 *
 * @return:
 *      nothing
 */
void toQuit(string message);


int main() {
    srand(time(NULL));


    int     nbExplo,
            posExploX = 0,
            posExploY = 0,
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
            LAKE_R_MAX = min(MAP_X_MAX,MAP_Y_MAX)/2;


    do {
        cout << "Ce programme calcule la probabilité pour N chercheurs de trouver un trésor sur une carte de taille X Y."
             << endl << endl;

        nbExplo = input("Entrez le nombre d'explorateurs :", NB_EXPLO_MIN, NB_EXPLO_MAX);
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
                  LAKE_R_MIN, LAKE_R_MAX, MAP_X_MIN,  MAP_Y_MIN, MAP_X_MAX, MAP_Y_MAX);
            cout << "IT HAS SPAWNED " << explo << endl;
            int step;
            for (step=0; step<MAP_X_MAX*MAP_Y_MAX;++step){

                move(posExploX,posExploY);
                stateX = checkPos(posExploX,  posTreasureX,  posLake1X,  radLake1,  posLake2X,  radLake2,  posLake3X,  radLake3, MAP_X_MIN, MAP_X_MAX);
                stateY = checkPos(posExploY,  posTreasureY,  posLake1Y,  radLake1,  posLake2Y,  radLake2,  posLake3Y,  radLake3, MAP_Y_MIN, MAP_Y_MAX);
                if(stateX == State::RICH && stateY == State::RICH){
                    finalState = State::RICH;

                    break;
                }else if(stateX == State::LOST || stateY == State::LOST){
                    finalState = State::LOST;

                    break;
                }else if(stateX == State::DROWND && stateY == State::DROWND){
                    finalState = State::DROWND;
                    break;
                }else{
                    finalState = State::WALK;
                }
            }

            cout << "finalState : "<<printPos(finalState) << endl;
            foundTreasure += finalState == State::RICH ? 1 : 0;
            avgSteps += finalState == State::RICH ? step : 0;

        }
        cout << "Nombre de chercheurs fructueux : " << foundTreasure << endl
             << "Probabilité de succès : " << 100.*foundTreasure/nbExplo << "%" << endl
             << "Nombre de pas moyens au succès : " << (!foundTreasure ? 0 : avgSteps/foundTreasure) << endl;




    }while(doAgain());
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
int genRadius(int& r, const int minR, const int maxR){
    /*TMP*/
}
int norme(int x, int y){
    return (int)sqrt(x*x+y*y);
}
int spawn(int& posExploX, int& posExploY, int& posTreasureX, int& posTreasureY, int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X, int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y, int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX, const int minX, const int minY, const int maxX, const int maxY){
    /*TODO CHANGE OR FOR AND*/
    static bool first = true;
    if(first){
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
        radLake3 = genRandomVal(LAKE_R_MIN, min(norme(posLake3X-posLake2X,posLake3Y-posLake2Y),norme(posLake3X-posLake1X,posLake3Y-posLake1Y))-1);

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
    first = !first;
    /*EXPLO*/
    do{
        posExploX = genRandomVal(minX, maxX);
        posExploY = genRandomVal(minY, maxY);

    }while((norme(posExploX-posLake1X, posExploY-posLake1Y) <= radLake1) || (norme(posExploX-posLake2X, posExploY-posLake2Y) <= radLake2) || (norme(posExploX-posLake3X, posExploY-posLake3Y) <= radLake3));

    return EXIT_SUCCESS;
}
int spawnExplo(int& posExploX, int& posExploY, const int minX, const int maxX, const int minY, const int maxY){


}
int move(int& posExploX, int& posExploY){

    int movement = genRandomVal(1,4);
    posExploX += movement%2 ? movement-2 : 0;
    posExploY += movement%2 ? 0 : movement-2;
    return EXIT_SUCCESS;
}
<<<<<<< HEAD
State checkPos(int& posExplo, int& posTreasure, int& posLake1, int& radLake1, int& posLake2, int& radLake2, int& posLake3, int& radLake3, const int& min, const int& max){
=======
int checkPos(int posExplo, int posTreasure, int posLake1, int radLake1, int posLake2, int radLake2, int posLake3, int radLake3, const int min, const int max){
>>>>>>> master
    /*riche perdu noyé epuisé nothing*/
    /*  1     2     3    -      0 */


    return posExplo < min ? State::LOST :
           posExplo > max ? State::LOST :
           posExplo == posTreasure ? State::RICH :
           posExplo <= posLake1+radLake1 ? State::DROWND :
           posExplo <= posLake2+radLake2 ? State::DROWND :
           posExplo <= posLake3+radLake3 ? State::DROWND :
           State::WALK;
}

string printPos(State state){
	string actualState;

switch(state){
case State::RICH :
actualState="Riche";
	break;
case State::LOST :
	actualState="Perdu";
	break;
case State::DROWND:
	actualState="Noye";
	break;
case State::SPENT:
	actualState="Epuise";
	break;
case State::WALK:
	actualState="Marche";
	break;
default:
	actualState="inconnu";
	break;

}

return actualState;
}
/***************************SAISIE****************************/
bool doAgain(){

    char const YES = 'Y';
    char const NO = 'N';
    char answer;
    bool isValid;


    do{
        cout << "Voulez-vous recommencer ? ["<<YES<<"/"<<NO<<"]";
        isValid = bool(cin >> answer);
        if(isValid)
            cin.clear();
        CLEAR_BUFFER;
        // works even if the user forget the capital letter
    }while(!(isValid || toupper(answer) == YES || toupper(answer) == NO));

    return(toupper(answer)==YES);
}


int input(const string& message, int limitMin, int limitMax, const int WIDTH_INT, const int WIDTH_TEXT, const string error){
    int userInput;
    bool isValid;
    do{
        //shows message that includes the boundaries that the user must respect
        cout  << message << setw(WIDTH_TEXT-message.length()) << ": [ " << setw(WIDTH_INT) << limitMin << " et " << setw(WIDTH_INT) << limitMax <<"] :" ;
        isValid = bool(cin >> userInput);

        if(!isValid || userInput < limitMin || userInput > limitMax ){
            cout << error << endl;
            cin.clear();
        }
        CLEAR_BUFFER;

    }while(!isValid || userInput < limitMin || userInput > limitMax);

    return userInput;
}

void toQuit(string message){
    cout << message;
    cin.get();
}
