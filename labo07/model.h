//
// Created by nyahon on 06.12.16.
//

#ifndef LABO07_MODEL_H
#define LABO07_MODEL_H

#include "IO.h"


int spawn(int& posExploX, int& posExploY, int& posTreasureX, int& posTreasureY, int& posLake1X, int& posLake1Y, int& radLake1, int& posLake2X, int& posLake2Y, int& radLake2, int& posLake3X, int& posLake3Y, int& radLake3, const int LAKE_R_MIN, const int LAKE_R_MAX, const int minX, const int minY, const int maxX, const int maxY, bool first);

int move(int& posExploX, int& posExploY);

State checkPos(int& posExplo, int& posTreasure, int& posLake1, int& radLake1, int& posLake2, int& radLake2, int& posLake3, int& radLake3, const int& min, const int& max);

int defineState(State stateX, State stateY, State& finalState);



#endif //LABO07_MODEL_H
