/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo_04
 Fichier     : Labo_04_meyer_rouvinez.cpp
 Auteur(s)   : Yohann Meyer Sven Rouvinez
 Date        : 06.11.2016

 But         : Permet d'approximer la valeur de pi suite à une précision donnée
               par l'utilisateur.

 Remarque(s) : Utilisation de la suite de Wallis pour approximer pi.
               Gestion complète des erreurs de saisie
               

 Compilateur : g++ (GCC) 6.2.1 20160916 (Red Hat 6.2.1-2)
 -----------------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdlib>
#include <climits>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {


    const int   MIN_COUT_PRECISION  = 1;
    const int   MAX_COUT_PRECISION  = 5;
    const int   SET_W               = 10;
    const int   SET_W_NUM         = 3;
//nombre de chiffres significatifs de l'écart par défaut
    const int   DEFAULT_PRECISION   = 5;

// On définit ici les valeurs de depart de la série
    const int   NUM_INITIAL         = 2;
    const int   DENUM_INITIAL       = 1;

    char        choixContinuer;
    double      product,
                previousProduct,
                ecart,
                precisionCalc;
    int         num,
                denum,
                terme,
                precision;
    bool        saisieCtrl;

    do {

//Boucle de saisie
        do {

            cout << "Quelle precision [ 10^-"  << MIN_COUT_PRECISION << " 10^-" << MAX_COUT_PRECISION << "]: 10^-";
            saisieCtrl = bool(cin >> precision);


            if (!saisieCtrl){
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }


        } while (precision < MIN_COUT_PRECISION || precision > MAX_COUT_PRECISION || !saisieCtrl);
        cin.ignore(INT_MAX, '\n');


        cout << setw(SET_W_NUM) << "No" << setw(SET_W) << "Terme" << setw(SET_W) << "Pi/2" << setw(SET_W) << "Ecart"
             << endl;
/*
 * Initalisations:
 * @previousProduct : prend la valeur NUM_INITIAL pour permettre un écart de 0 lors de la première itération
 * @num             : prend la valeur NUM_INIIAL
 * @denum           : prend la valeur DENUM_INITIAL
 * @product         : prend 1. (double), car 1 est l'élément neutre de la multiplication
 * @terme           : prend 1 car l'incrémentation du nombre de terme se fait après l'impression
 * @precisionCalc   : prend la valeur du calcul de 10^precision pour éviter de le faire dans la boucle
 */
        previousProduct   = NUM_INITIAL;
        num             = NUM_INITIAL;
        denum           = DENUM_INITIAL;
        product             = 1.;
        terme           = 1;
        precisionCalc   = pow(10, -precision);
//Boucle de calcul
        while (true) {
            product *= (double) num / denum;
//abs gare l'écart ne s'intéresse qu'à la magnitude de la différence de n_-1 et n.
            ecart = abs(product - previousProduct);
/*
 * Permet de ne pas calculer un terme de trop.
 * "&& ecart" permet de ne pas sortir de la boucle quand ecart est égal à 0 (première itération)
 * [Comme ecart est une valeur définie par une fonction décroissante limitée en 0, on sait qu'on
 * sortira de la boucle]
 */
            if (ecart <= precisionCalc && ecart)
                break;
/*
 * @SET_W_NUM : définit l'espace sur lequel s'affiche le nbr de terme ainsi que le dénominateur.
 * @SET_W     : définit l'espacement entre chaque colonne. on ajoute precision-1 pour garantir la lisibilité des
 *              données même quand l'écart devient très petit (10⁻⁵).
 */
            cout << setw(SET_W_NUM) << terme << setw(SET_W) << num << "/" << setw(SET_W_NUM) << denum << setw(SET_W)
                 << setprecision(1 + precision) << product << setprecision(DEFAULT_PRECISION) << setw(SET_W+precision-1) << ecart << endl;

            if (num > denum) {
                denum += 2;
            } else {
                num += 2;
            }
/*
 * le produit calculé et affiché devient le produit précédent de la prochaine itération.
 */
            previousProduct = product;
            ++terme;
        }
        cout << "Approximation de de Pi/2: " << setprecision(1 + precision) << product << endl;

        cout << "Nombres de termes: " << terme << endl;


        cout << "Voulez-vous continuer [o/n]:";
        cin  >> choixContinuer;
        cin.ignore(INT_MAX,'\n');
    } while (choixContinuer != 'n');


    return EXIT_SUCCESS;
}
