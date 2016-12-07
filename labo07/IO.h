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

using namespace std;
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
 * @brief print the statistics when the program end, and optionally the map
 *
 * @param [in] foundTreasure number of explo who found the treasure
 * @param [in] nbExplo total number of explo
 * @param [in] avgSteps average steps from explo who found the treasure
 * @param [in/out] map contains the map to be print on console. We pass it by reference
 *                  to avoid a costly copy.
 */
void printStats(const int foundTreasure, const int nbExplo, const int avgSteps, const string& map);

#endif //LABO07_IO_H
