/* Fichier : IO.h
 * Auteur : Yohann Meyer - Sven Rouvinez / HEIG-VD
 * Date: 06.12.2016
 *
 *
 * Modifications : 06.12.2016 / Sven Rouvinez / Updating the commentary
 *
 */

#ifndef LABO07_IO_H
#define LABO07_IO_H
#include <string>
//enum class with different states
enum class State {
	RICH, LOST, DROWND, SPENT, WALK
};

/**
 *@brief print the state from a given State type
 *
 *@param [in] state state type from the enum class
 *@param [in] step number of steps
 */
void printState(const State state, int explo, const int step);

/**
 * @brief print the statistics when the program end
 *
 * @param [in] foundTreasure number of explo who found the treasure
 * @param [in] nbExplo total number of explo
 * @param [in] avgSteps average steps from explo who found the treasure
 */
void printStats(const int foundTreasure, const int nbExplo, const int avgSteps);

#endif //LABO07_IO_H
