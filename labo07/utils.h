/* Fichier : utils.h
 * Auteur : Yohann Meyer - Sven Rouvinez / HEIG-VD
 * Date: 06.12.2016
 *
 * But:
 *
 *
 * Modifications : 06.12.2016 / Sven Rouvinez / Updating the commentary
 *
 */

#ifndef LABO07_UTILS_H
#define LABO07_UTILS_H


#include <string>
#include <iostream>
#include <iomanip>
#include <climits>



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


#endif //LABO07_UTILS_H
