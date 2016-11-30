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

#define CLEAR_BUFFER cin.ignore(INT_MAX, '\n')


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
int input(string message, int limitMin, int limitMax, const int WIDTH_INT=WIDTH_INT_BASE, const int WIDTH_TEXT=WIDTH_TEXT_BASE, const string error="Mauvaise saisie. Veuillez reessayez");
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



















    




    doAgain();
    return EXIT_SUCCESS;
}


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
