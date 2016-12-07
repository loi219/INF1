/* Fichier : model.cpp
 * Auteur : Yohann Meyer - Sven Rouvinez / HEIG-VD
 * Date: 06.12.2016
 *
 * But: handle the generation, randomization of all the elements that the program needs
 *
 * Remarque(s) :
 *
 * Modifications : 06.12.2016 / Sven Rouvinez / Updating the commentary
 *
 */

#include "model.h"
#include "utils.h"
#include <cmath>

int area(const int mapX, const int mapY) {
	//to be sure that the area is generate just once
	static int area;
	if (!area)
		area = mapX * mapY;
	return area;
}
int genRandomVal(const int minVal, const int maxVal) {
    static bool first;
    if(!first)
        srand(time(NULL));

	//the minVal cannot be greater than maxVal
	if (minVal >= maxVal) {
		return EXIT_FAILURE;
	}
	int range;
	range = maxVal - minVal;
    first = true;
    //return a negative or a positive number
	return (rand() % ((range * 2 + 1) - range))+minVal ;


}

int norme(const int x,const  int y) {
    //round to 0.5 closest
	return int(sqrt(x * x + y * y)+0.5);
}
int spawn(int& posExploX, int& posExploY, int& posTreasureX, int& posTreasureY,
		int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X,
		int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y,
		int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX,
		const int minX, const int minY, const int maxX, const int maxY,
		string& map) {
    static bool first;
	if (!first) {
		//generate the lakes
		posLake1X = genRandomVal(minX, maxX);
		posLake1Y = genRandomVal(minY, maxY);
		radLake1 = genRandomVal(LAKE_R_MIN, LAKE_R_MAX);

		//check if they're not one over the other
		do {
			posLake2X = genRandomVal(minX, maxX);
			posLake2Y = genRandomVal(minY, maxY);
            //for the max radius, take the min between the set max and the distance from the center of
            //this lake to the border of the other. Same for lake 3.
			radLake2 = genRandomVal(LAKE_R_MIN,
					min(LAKE_R_MAX,
							norme(posLake2X - posLake1X, posLake2Y - posLake1Y)-radLake1)
							- 1);
		} while (norme(posLake2X - posLake1X, posLake2Y - posLake1Y) <= radLake1);

		do {
			posLake3X = genRandomVal(minX, maxX);
			posLake3Y = genRandomVal(minY, maxY);
			radLake3 = genRandomVal(LAKE_R_MIN,
					min(
							min(LAKE_R_MAX,
									norme(posLake3X - posLake2X,
											posLake3Y - posLake2Y)-radLake2),
							norme(posLake3X - posLake1X, posLake3Y - posLake1Y)-radLake1)
							);

		} while (norme(posLake3X - posLake1X, posLake3Y - posLake1Y) <= radLake1
				|| norme(posLake3X - posLake2X, posLake3Y - posLake2Y)
						<= radLake2
				|| radLake3 + radLake1
						>= norme(posLake3X - posLake1X, posLake3Y - posLake1Y)
				|| radLake3 + radLake2
						>= norme(posLake3X - posLake2X, posLake3Y - posLake2Y));

		//generate the treasure
		do {
			posTreasureX = genRandomVal(minX+1, maxX-1);
			posTreasureY = genRandomVal(minY+1, maxY-1);
		// check if it isn't on a lake
		} while (norme(posTreasureX - posLake1X, posTreasureY - posLake1Y)
				<= radLake1
				|| norme(posTreasureX - posLake2X, posTreasureY - posLake2Y)
						<= radLake2
				|| norme(posTreasureX - posLake3X, posTreasureY - posLake3Y)
						<= radLake3);

        //generate the map for print
        char c;
        for(int i=minX;i<=maxX;++i){
            for(int j=minY;j<=maxY;++j){
                c = i == posTreasureX && j == posTreasureY ? 'X' :
                    i== minX || i== maxX ? '-' :
                    j== minY || j==maxY ? '|' :
                    (norme(i-posLake1X,j-posLake1Y) < radLake1) ||
                    (norme(i-posLake2X,j-posLake2Y) < radLake2) ||
                    (norme(i-posLake3X,j-posLake3Y) < radLake3) ? '*' :
                    ' ';
                map += c;
                //uncomment this row to compensate the difference between height and width of a character in console.
                //map += c;

            }
            map += '\n';

        }
	}


	//used to check if the generation was ok
	first = true;

	//generate the explorators
	do {
		posExploX = genRandomVal(minX+1, maxX-1);
		posExploY = genRandomVal(minY+1, maxY-1);

	//it cannot start in a lake
	} while ((norme(posExploX - posLake1X, posExploY - posLake1Y) <= radLake1)
			|| (norme(posExploX - posLake2X, posExploY - posLake2Y) <= radLake2)
			|| (norme(posExploX - posLake3X, posExploY - posLake3Y) <= radLake3));


	return EXIT_SUCCESS;
}

int move(int& posExploX, int& posExploY) {

	int movement = genRandomVal(1, 4);
	posExploX += movement % 2 ? movement - 3 : 0;
	posExploY += movement % 2 ? 0 : movement - 2;
	return EXIT_SUCCESS;
}

State checkPos( int& posExplo, int& posTreasure, int& posLake1, int& radLake1,
	        	int& posLake2, int& radLake2, int& posLake3, int& radLake3,
	        	const int& min, const int& max ) {

/*if the posExplo is min or the max off the map he's lost
 *if the posExplo is equal to the treasure he's rich
 *if the norme of posExplo and center of a lake is less or equal of its radius he's drownd
 *otherwise he's walking
 */
	return  (norme(posExplo, posLake1) <= (radLake1)) ||
            (norme(posExplo, posLake2) <= (radLake2)) ||
            (norme(posExplo, posLake3) <= (radLake3)) ? State::DROWND :
            posExplo == posTreasure ? State::RICH :
            posExplo < min ? State::LOST :
			posExplo > max ? State::LOST :
            State::WALK;


}

int defineState(State stateX, State stateY, State& finalState) {
    if (stateX == State::DROWND && stateY == State::DROWND) {
        finalState = State::DROWND;
        	return 1;

	} else if (stateX == State::RICH && stateY == State::RICH) {
		finalState = State::RICH;
				return 1;

	} else if (stateX == State::LOST || stateY == State::LOST) {
        finalState = State::LOST;
        return 1;

	} else {
		finalState = State::WALK;
		return 0;

	}
}
