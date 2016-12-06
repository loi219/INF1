/* Fichier : IO.cpp
 * Auteur : Yohann Meyer - Sven Rouvinez / HEIG-VD
 * Date: 06.12.2016
 *
 * But: print the information of the program
 *
 *
 * Modifications : 06.12.2016 / Sven Rouvinez / Updating the commentary
 *
 */

#include "IO.h"
#include "utils.h"

void printState(const State state, const int explo,const int step) {
	string actualState;
	static bool first;

	switch (state) {
	case State::RICH:
		actualState = "Riche!";
		break;
	case State::LOST:
		actualState = "Perdu";
		break;
	case State::DROWND:
		actualState = "Noye";
		break;
	case State::SPENT:
		actualState = "Epuise";
		break;
	case State::WALK:
		actualState = "Marche";
		break;

	}
	//print the steps
	if (!first)
		cout << "Explorateur" << " | " << setw(WIDTH_INT_BASE) << "Etat"
				<< " | " << setw(WIDTH_INT_BASE) << " #Pas" << endl;
	first = true;
	//print 0 step
	cout << "Explorateur " << "  " << setw(WIDTH_INT_BASE) << actualState
			<< "  " << setw(WIDTH_INT_BASE) << step << endl;

}

void printStats(const int foundTreasure, const int nbExplo,
		const int avgSteps) {
	cout << "Nombre de chercheurs fructueux : " << foundTreasure << endl
			<< "Probabilité de succès : " << 100. * foundTreasure / nbExplo
			<< "%" << endl << "Nombre de pas moyens au succès : "
			<< (!foundTreasure ? 0 : avgSteps / foundTreasure) << endl;
}

