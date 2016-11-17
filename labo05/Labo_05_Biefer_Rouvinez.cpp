/*
---------------------------------------------------------------------------------------
Laboratoire : Labo_05_Biefer_Rouvinez

Fichier     : Labo_05_Biefer_Rouvinez.cpp

Auteur(s)   : Julien Biefer et Sven Rouvinez

Date        : 15.11.2016

But         : Afficher un calendrier complet pour une année donnée par l'utilisateur

Remarque(s) : Les paramètres donnés aux fonctions ne sont pas vérifiées.
              Dans ce programme, les jours et mois commencent à 0 car en informatique,
              les index commencent à zéro.
              Les fonctions jourSemaine() et nbrJoursMois() utilisent des adaptations
              de certains algorithmes. Ces adaptations sont nécessaires pour concorder
              avec notre programme. Le nom des variables dans ces fonctions a été
              repris de l'algorithme original pour souci de compréhension.

Compilateur : Apple LLVM 8.0
              gcc version 6.2.1 20160916 (Red Hat 6.2.1-2) (GCC)
---------------------------------------------------------------------------------------
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <string>

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

using namespace std;


//=========================================================================================
// Prototypes
//=========================================================================================

// Renvoie le jour de la semaine (0 (lundi) et 6 (dimanche)) pour une date donnée
// Tiré de http://mathforum.org/library/drmath/view/55837.html
int jourSemaine(const int jour, const int mois, const int annee);

// Gère la saisie par l'utilisateur d'un int compris entre deux bornes (incluses)
int saisieInt(const string messageSaisie, const int borneMin, const int borneMax);

// Demande à l'utilisateur s'il souhaite relancer le programme
bool saisieRecommencer(const string messageSaisie, const char valeurVraieParam,
                                                   const char valeurFalseParam);

// Retourne le nombre de jour pour un mois donné en prenant en compte les années bissextiles
// Tiré de http://www.dispersiondesign.com/articles/time/number_of_days_in_a_month
int nbrJoursMois(const int mois, const int annee);

// Retourne le string du mois correspondant au nombre passé en paramètre.
// Affiche un message s'il ne match à aucun mois
string intMoisEnString(const int numMois);

// Retourne la premère lettre (char) du jour de la semaine correspondant au numero passé
// en paramètre. Affiche un message s'il ne match à aucun jour
char intJourEnChar(const int numJourSemaine);

// Affiche un mois donné en fonction du nombre de jours contenu dans celui-ci et
// renvoie le dernier jour affiché de la semaine afin de démarrer le mois suivant
// un jour après la fin du mois précédent
int afficherMois(const int mois, const int annee, const int debutDuMois);


//=========================================================================================
// Programme principal
//=========================================================================================

int main() {

    //==========================================
    // 1. Définition des variables et constantes
    //==========================================

    // 1.1 Définition des variables
    int annee            = 0;   // L'année demandée par l'utilisateur
    int premierJourAnnee = 0;   // 0 correspond au lundi
    bool recommencer;

    // 1.2 Définition des constantes
    const int NB_MOIS = 12;
    const int MIN_ANNEE = 1900;
    const int MAX_ANNEE = 2100;

    //=======================================================
    // 2. Bonjour et présentation programme
    //=======================================================
    cout << "Bonjour, ce programme affiche un calendrier pour une annee donnee." << endl;

    do {
        //=======================================================
        // 3. Saisie de l'année par l'utilisateur
        //=======================================================
        annee = saisieInt("Quelle annee voulez-vous afficher [" + to_string(MIN_ANNEE) +
                          "-" + to_string(MAX_ANNEE) + "] : ", MIN_ANNEE, MAX_ANNEE);

        //=======================================================
        // 4. Détermination du jour de la semaine au 1er janvier
        //=======================================================
        premierJourAnnee = jourSemaine(1, 1, annee);

        //=======================================================
        // 5. Affichage de chaque mois
        //=======================================================
        cout << "Voici le calendrier pour l'annee " << annee << "." << endl;

        for(int mois = 0, premierJourMois = premierJourAnnee; mois < NB_MOIS; ++mois) {
            premierJourMois = afficherMois(mois, annee, premierJourMois);
            cout << endl << endl;
        }

        //=======================================================
        // 6. Demande si l'utilisateur veut relancer le programme
        //=======================================================
        recommencer = saisieRecommencer("Voulez-vous recommencer [o/n] ? ", 'o', 'n');
        cout << endl;

    } while(recommencer);

    //==============
    // 7. Au revoir.
    //==============
    cout << "Merci d'avoir utilise le programme !"       << endl;
    cout << "Pressez ENTER pour quitter le programme..." << endl;
    VIDER_BUFFER;

    return EXIT_SUCCESS;
}


//=========================================================================================
// Fonctions
//=========================================================================================

int jourSemaine(const int jour, const int mois, const int annee) {
    int d = jour,
        m = mois,
        y = annee;

    if (m <= 2) {
        m += 12;
        --y;
    }

    return (d + 2*m + (3*(m+1)/5) + y + (y/4) - (y/100) + (y/400)) % 7;
}

bool estBissextile(const int annee) {
    // Une année est bissextile si elle est multiple de 400 ou elle est multiple de 4
    // et pas de 100.
    return (bool) (!(annee % 400) || (!(annee % 4) && (annee % 100)));
}

int saisieInt(const string messageSaisie, const int borneMin, const int borneMax) {

    // Définition des variables nécessaires à la saisie
    int  saisie;        // Variable qui contiendra la valeur saisie
    bool saisieOK,
         erreurFlux;

    // Définition des constantes
    const string MSG_ERREUR_FLUX = "Veuillez entrer un nombre entier.";
    const string MSG_ERREUR_SAISIE = "La valeur saisie n'est pas comprise dans l'intervalle.";

    do {
        // On récupère la saisie de l'utilisateur
        cout << messageSaisie;
        erreurFlux = bool(cin >> saisie);

        // S'il y a eu une erreur de flux, on la corrige et on reboucle (flag saisieOK à false)
        if (!erreurFlux) {
            cin.clear();
            cout << MSG_ERREUR_FLUX << endl << endl;
            saisieOK = false;
        }
        // Si la valeur n'est pas dans l'intervalle demandé, on reboucle
        else if (saisie < borneMin || saisie > borneMax) {
            cout << MSG_ERREUR_SAISIE << endl << endl;
            saisieOK = false;
        }
        // Sinon on accepte la valeur et on arrête de boucler (flag saisieOK à true)
        else {
            saisieOK = true;
        }

        VIDER_BUFFER;

    } while(!saisieOK);

    // On retourne finalement la valeur saisie
    return saisie;
}

bool saisieRecommencer(const string messageSaisie, const char valeurVraieParam,
                                                   const char valeurFausseParam) {

    // Définition des variables nécessaires à la saisie
    char saisie;        // Variable qui contiendra la valeur saisie
    bool saisieOK,
            erreurFlux;
    char valeurVraie = (char) toupper(valeurVraieParam);
    char valeurFausse = (char) toupper(valeurFausseParam);

    // Définition des constantes
    const string MSG_ERREUR_FLUX = "Veuillez entrer un caractere.";
    const string MSG_ERREUR_SAISIE = "La valeur saisie n'est pas une valeur possible.";

    do {
        // On récupère la saisie de l'utilisateur
        cout << messageSaisie;
        erreurFlux = bool(cin >> saisie);

        // S'il y a eu une erreur de flux, on la corrige et on reboucle (flag saisieOK à false)
        if (!erreurFlux) {
            cin.clear();
            cout << MSG_ERREUR_FLUX << endl << endl;
            saisieOK = false;
        }
        // Si la valeur est pas parmis les valeurs demandées, on reboucle
        else if (toupper(saisie) != valeurVraie && toupper(saisie) != valeurFausse) {
            cout << MSG_ERREUR_SAISIE << endl << endl;
            saisieOK = false;
        }
        // Sinon, on accepte la valeur et on arrête de boucler (flag saisieOK à true)
        else {
            saisieOK = true;
        }

        VIDER_BUFFER;

    } while(!saisieOK);

    // On retourne finalement un booléen en fonction de la valeur saisie (true si 'o' ou 'O')
    return (toupper(saisie) == valeurVraie);
}

int nbrJoursMois(const int mois, const int annee) {
    // On compte 31 pour tous les mois puis
    //      - si c'est février, on déduit 2 si c'est bissextile et 3 si ça ne l'est pas
    //      - si ce n'est pas février, on fait modulo 7 pour "mettre août sur janvier"
    //        ensuite on enlève soit 0 soit 1 avec le modulo 2.
    return (31 - ((mois == 1) ? (3 - (int) estBissextile(annee)) : ((mois) % 7 % 2)));
}

string intMoisEnString(const int numMois) {
    string mois = "";

    switch (numMois) {
        case 0:
            mois = "Janvier";
            break;
        case 1:
            mois = "Fevrier";
            break;
        case 2:
            mois = "Mars";
            break;
        case 3:
            mois = "Avril";
            break;
        case 4:
            mois = "Mai";
            break;
        case 5:
            mois = "Juin";
            break;
        case 6:
            mois = "Juillet";
            break;
        case 7:
            mois = "Aout";
            break;
        case 8:
            mois = "Septembre";
            break;
        case 9:
            mois = "Octobre";
            break;
        case 10:
            mois = "Novembre";
            break;
        case 11:
            mois = "Decembre";
            break;
        default:
            cerr << "Le numero (" << numMois << ") ne correspond a aucun mois de l'annee.";
    }

    return mois;
}

char intJourEnChar(const int numJourSemaine) {
    char jour = ' ';

    // On match le jour de la semaine-1 avec la première lettre du jour en char
    switch (numJourSemaine) {
        case 0:
            jour = 'L';
            break;
        case 1:
        case 2:
            jour = 'M';
            break;
        case 3:
            jour = 'J';
            break;
        case 4:
            jour = 'V';
            break;
        case 5:
            jour = 'S';
            break;
        case 6:
            jour = 'D';
            break;
        default:
            cerr << "Le numero (" << numJourSemaine << ") ne correspond à aucun jour de la semaine.";
    }

    return jour;
}

int afficherMois(const int mois, const int annee, const int debutDuMois) {

    // Définition des variables
    int nbrJours = nbrJoursMois(mois, annee);

    // Définition des constantes
    const int NBR_JOUR_SEMAINE = 7;
    const int ESPACE_NUMERO    = 3;

    cout << intMoisEnString(mois) << " " << annee << endl;

    // On affiche les lettres des jours de la semaine
    for(int jour = 0; jour < NBR_JOUR_SEMAINE; ++jour)
        cout << setw(ESPACE_NUMERO) << intJourEnChar(jour);

    cout << endl;

    // On affiche les jours du mois dans les bonnes colonnes
    // Ici jourMois concorde puisqu'il est affiché
    for(int jourMois = 1, compteur = 1; jourMois <= nbrJours; ++compteur) {

        // On affiche d'abord des espaces pour commencer le mois le bon jour de la semaine
        cout << setw(ESPACE_NUMERO);
        if (compteur <= debutDuMois)
            cout << " ";
        // Puis on affiche les dates
        else
            cout << jourMois++;

        // On retourne à la ligne si on est en fin de ligne sauf si on est à la fin du mois
        if (!(compteur % 7) && jourMois <= nbrJours)
            cout << endl;
    }

    // Pour trouver le jour à retourner, on fait le décalage du mois précédent + le nombre de jour de
    // ce mois et on prend le modulo pour trouver le jour de la semaine auquel il correspond. Le fait
    // que le mois suivant commencera le jour suivant (ce qui serait un +1 normalement) est déjà inclu
    // dans nbrJours puisqu'il commence à 1 et pas à 0. Le décalage est donc garanti.
    return ((nbrJours + debutDuMois) % 7);
}