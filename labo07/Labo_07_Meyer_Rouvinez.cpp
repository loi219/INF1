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


int main(){
    srand(time(NULL));


    int nbExplo,
    mapX,
    mapY,
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


const int   NB_EXPLO_MIN = 1,
            NB_EXPLO_MAX = INT_MAX,
            MAP_X_MIN = 1,
            MAP_Y_MIN = 1,
            MAP_Y_MAX = INT_MAX,
            MAP_X_MAX = INT_MAX,
            LAKE_R_MIN = 1,
            LAKE_R_MAX = 50;



    cout << "Ce programme calcule la probabilité pour N chercheurs de trouver un trésor sur une carte de taille X Y." << endl << endl;

    nbExplo = input("Entrez le nombre d'explorateurs :",NB_EXPLO_MIN, NB_EXPLO_MAX );
    mapX    = input("Entrez la largeur de la carte :",MAP_X_MIN, MAP_X_MAX );
    mapY    = input("Entrez la hauteur de la carte :",MAP_Y_MIN, MAP_Y_MAX );





    doAgain();
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
    if(min>=max){
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
int genLake(int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X, int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y, int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX, const int minX, const int minY, const int maxX, const int maxY){
    /*TODO CHANGE OR FOR AND*/
    posLake1X = genRandomVal(minX, maxX);
    posLake1Y = genRandomVal(minY, maxY);
    do{
    posLake2X = genRandomVal(minX, maxX);
    posLake2Y = genRandomVal(minY, maxY);
    }while(posLake2X == posLake1X || posLake2Y == posLake1Y);
    do{
    posLake3X = genRandomVal(minX, maxX);
    posLake3Y = genRandomVal(minY, maxY);
    }while(posLake3X == posLake1X || posLake3Y == posLake1Y || posLake3X == posLake2X || posLake3Y == posLake2Y);


    radLake1  = genRandomVal(LAKE_R_MIN, LAKE_R_MAX);
    do{
    radLake2  = genRandomVal(LAKE_R_MIN, LAKE_R_MAX);
    }while(radLake2+radLake1>=norme(posLake2X-posLake1X, posLake2Y-posLake1Y));
    do {
        radLake3 = genRandomVal(LAKE_R_MIN, LAKE_R_MAX);
    }while(radLake3+radLake1>=norme(posLake3X-posLake1X, posLake3Y-posLake1Y) || radLake3+radLake2>=norme(posLake3X-posLake2X, posLake3Y-posLake2Y));

    






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


int input(const string message, int limitMin, int limitMax,const int WIDTH_INT, const int WIDTH_TEXT, const string error){
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
