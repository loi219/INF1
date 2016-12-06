/* Fichier : utils.cpp
 * Auteur : Yohann Meyer - Sven Rouvinez / HEIG-VD
 * Date: 06.12.2016
 *
 * But:
 *
 *
 * Modifications : 06.12.2016 / Sven Rouvinez / Updating the commentary
 *
 */

#include "utils.h"

/***************************SAISIE****************************/
bool doAgain() {

	char const YES = 'Y';
	char const NO = 'N';
	char answer;
	bool isValid;

	do {
		cout << "Voulez-vous recommencer ? [" << YES << "/" << NO << "]";
		isValid = bool(cin >> answer);
		if (isValid)
			cin.clear();
		CLEAR_BUFFER;
		// works even if the user forget the capital letter
	} while (!(isValid || toupper(answer) == YES || toupper(answer) == NO));

	return (toupper(answer) == YES);
}

int input(const string& message, int limitMin, int limitMax,
		const int WIDTH_INT, const int WIDTH_TEXT, const string error) {
	int userInput;
	bool isValid;
	do {
		//shows message that includes the boundaries that the user must respect
		cout << message << setw(WIDTH_TEXT - message.length()) << ": [ "
				<< setw(WIDTH_INT) << limitMin << " et " << setw(WIDTH_INT)
				<< limitMax << "] :";
		isValid = bool(cin >> userInput);

		if (!isValid || userInput < limitMin || userInput > limitMax) {
			cout << error << endl;
			cin.clear();
		}
		CLEAR_BUFFER;

	} while (!isValid || userInput < limitMin || userInput > limitMax);

	return userInput;
}

void toQuit(string message) {
	cout << message;
	cin.get();
}
