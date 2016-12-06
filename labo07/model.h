/* Fichier : model.h
 * Auteur : Yohann Meyer - Sven Rouvinez / HEIG-VD
 * Date: 06.12.2016
 *
 * But: ce fichier ne contient que les déclarations mises à disposition par votre librairie
 *
 * Remarque(s) :
 *
 * Modifications : 05.12.2016 / Sven Rouvinez / Updating the commentary
 *
 */

#ifndef LABO07_MODEL_H
#define LABO07_MODEL_H

#include "IO.h"

/**
 * @brief generate and place the explorators, lakes and treasure
 *
 * @param [in,out] posExploX generate the position in X of the explorators
 * @param [in,out] posExploY generate the position in Y of the explorators
 * @param [in,out] posExploX generate the position in X of the treasure
 * @param [in,out] posExploX generate the position in Y of the treasure
 * @param [in,out] posLake1..3X generate the position in X for the lake
 * @param [in,out] posLake1..3Y generate the position in Y for the lake
 * @param [in,out] radLake1..3 generate the radius for the lakes
 * @param [in] LAKE_R_MIN LAKE_R_MAX maximum and minimum size for the lakes
 * @param [in] minX, minY, maxX, maxY maximum and minimum X and Y
 * @param [in] first check if the spawn was already used;
 *
 * @return if the function was terminate with success
 *
 * @details this function generate and create the position of the elements on the map.
 * Check if the lakes are separated and the treasure isn't in one of the lakes.
 */
int spawn(int& posExploX, int& posExploY, int& posTreasureX, int& posTreasureY,
		int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X,
		int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y,
		int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX,
		const int minX, const int minY, const int maxX, const int maxY,
		bool first);

/**
 * @brief move the explorators on the map
 *
 * @param [in,out]  posExploX, posExploY initial position and randomize it
 *
 * @return if the function was terminate with success
 *
 * @details randomize the position of the explorators between -1 to 1 and move them
 */
int move(int& posExploX, int& posExploY);

/**
 *@brief check the state of the explorators
 *@brief
 *@param [in] posExplo position of the explorator
 *@param [in] posTreasure  position of the treasure
 *@param [in] posLake1..3 position of the lakes
 *@param [in] radLake1..3 radius of the lakes
 *@param [in] min minimum coordinates of the map
 *@param [in] max maximum coordinates of the map
 *
 *@return the state of one explorator
 *@return
 *@details after each move this function return the state for each explo from his x,y coordinates, like is he drown, lost,
 * spent of he found the treasure. The use of enum is very useful because each state can be his real state name not just a number
 */
State checkPos(int& posExplo, int& posTreasure, int& posLake1, int& radLake1,
		int& posLake2, int& radLake2, int& posLake3, int& radLake3,
		const int& min, const int& max);

/**
 * @brief link the state with the enum class
 *
 *@param [in] stateX give the state for X
 *@param [in] stateY give the state for Y
 *@param [in,out] finalState the state from the X and Y state
 *
 *@details each coordinates define where the explo is. If he's outside of the map in X he has to be lost or when the position in Y is in a lake it means he's drown
 * or if he X and Y are equals to the X,Y position it means that the treasure is found
 */
int defineState(State stateX, State stateY, State& finalState);

/**
 *@brief calculate the area of the map
 *
 *@param [in] mapX length of the X
 *@param [in] mapY length of the Y
 *
 *return area of the map
 */
int area(const int mapX, const int mapY);

/**
 *@brief randomize a value from a given range
 *@brief
 *@param [in] minVal minimal boundary
 *@param [in] maxVal maximum boundary
 *
 *@return a randomize value
 */
int genRandomVal(const int minVal, const int maxVal);

/**
 *@brief check if the lakes aren't one over the other
 *
 *@param [in] x coordinate X
 *@param [in] y coordinate Y
 *
 *@return pythagore equation solution
 *  */
int norme(const int x, const int y);

#endif //LABO07_MODEL_H
