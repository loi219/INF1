//
// Created by nyahon on 06.12.16.
//

#include "IO.h"
#include "utils.h"


void printState(State state, int explo, int step) {
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
        default:
            actualState = "en chemin";
            break;

    }
    if(!first)
        cout << "Explorateur" << " | " << setw(WIDTH_INT_BASE) << "Etat"<< " | " << setw(WIDTH_INT_BASE) << " #Pas" << endl;
    first = true;
    cout << "Explorateur " << "  "<< setw(WIDTH_INT_BASE)   << actualState << "  "<< setw(WIDTH_INT_BASE)  << step << endl;

}

void printStats(int foundTreasure, int nbExplo, int avgSteps){
    cout << "Nombre de chercheurs fructueux : " << foundTreasure << endl
         << "Probabilité de succès : " << 100.*foundTreasure/nbExplo << "%" << endl
         << "Nombre de pas moyens au succès : " << (!foundTreasure ? 0 : avgSteps/foundTreasure) << endl;
}


