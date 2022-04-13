/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
    AUTEURS:
        David Genois GEND13119801
        Mathieu Lalonde LALM14127501
*/

#include <math.h>

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <limits.h>

#include "carte.h"

using namespace std;

void tp3(Carte& carte, istream& isMissions) {
    while (isMissions) {
        string nomLieuAffaire;
        char deuxPoints = 0;

        isMissions >> nomLieuAffaire >> deuxPoints;
        if (!isMissions) break;
        assert(deuxPoints == ':');

        list<string> destinations;

        while (isMissions) {
            string destination;
            isMissions >> destination;
            if (destination == ";" || !isMissions) break;
            assert(destination.find(";") == string::npos);
            destinations.push_back(destination);
        }

        list<string> cheminNoeudsOptimal;
        list<string> cheminRoutesOptimal;
        double distanceOptimal = std::numeric_limits<double>::max();

        // Tente de trouver le trajet le plus petit en trouvant les permutations.
        do {
            list<string> cheminNoeuds;
            list<string> cheminRoutes;
            double distanceTrouver = carte.calculerTrajet(nomLieuAffaire, destinations, cheminNoeuds, cheminRoutes, distanceOptimal);
            if (distanceOptimal > distanceTrouver) {
                distanceOptimal = distanceTrouver;
                cheminNoeudsOptimal = cheminNoeuds;
                cheminRoutesOptimal = cheminRoutes;
            }
        } while (next_permutation(destinations.begin(), destinations.end()));

        string noeudPrecedent = "";
        for (list<string>::const_iterator iter = cheminNoeudsOptimal.begin(); iter != cheminNoeudsOptimal.end(); ++iter)
            if (noeudPrecedent != *iter) {
                cout << *iter << " ";
                noeudPrecedent = *iter;
            }
        cout << endl;
        for (list<string>::const_iterator iter = cheminRoutesOptimal.begin(); iter != cheminRoutesOptimal.end(); ++iter)
            cout << *iter << " ";
        cout << endl;
        cout << round(distanceOptimal) << " m" << endl;
    }
}

int main(int argc, const char** argv) {
    if (argc <= 1 || argc > 3) {
        cout << "Syntaxe: ./tp3 carte.txt [missions.txt]" << endl;
        return 1;
    }

    // Lecture de la carte.
    Carte carte;
    {
        ifstream fichiercarte(argv[1]);
        if (fichiercarte.fail()) {
            cout << "Erreur ouverture du fichier : " << argv[1] << endl;
            return 2;
        }
        fichiercarte >> carte;
    }

    if (argc > 2) {
        // Lecture des missions depuis un fichier.
        ifstream isMissions(argv[2]);
        if (isMissions.fail()) {
            cout << "Erreur d'ouverture du fichier : " << argv[2] << endl;
            return 3;
        } else
            tp3(carte, isMissions);
    } else {
        // Lecture depuis stdin (console).
        tp3(carte, cin);
    }
    return 0;
}
