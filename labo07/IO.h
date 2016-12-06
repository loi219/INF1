//
// Created by nyahon on 06.12.16.
//

#ifndef LABO07_IO_H
#define LABO07_IO_H

#include <string>
enum class State {RICH,LOST,DROWND,SPENT,WALK};


void printState(State intState, int explo, int step);

void printStats(int foundTreasure, int nbExplo, int avgSteps);

#endif //LABO07_IO_H
