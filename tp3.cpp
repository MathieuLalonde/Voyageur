/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
    AUTEURS:
        David Genois GEND13119801
        Mathieu Lalonde LALM14127501
*/

#include <bits/stdc++.h>
#include <limits.h>
#include <math.h>

#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "carte.h"

using namespace std;

void tp3(Carte& carte, istream& ismissions) {
    while (ismissions) {
        string nomlieuaffaire;
        char deuxpoints = 0;
        ismissions >> nomlieuaffaire >> deuxpoints;
        if (!ismissions) break;
        assert(deuxpoints == ':');
        // p.s. En utilisant un set, on elimine les doublons et ca reduit la longeur
        set<string> destinations;
        while (ismissions) {
            string destination;
            ismissions >> destination;  // ne pas ajouter « >> std::std » ici.
            if (destination == ";" || !ismissions) break;
            assert(destination.find(";") == string::npos);
            destinations.insert(destination);
        }

        list<string> chemin_noeuds, chemin_routes;
        double distance = carte.calculerTrajet(nomlieuaffaire, destinations, chemin_noeuds, chemin_routes);

        for (list<string>::const_iterator iter = chemin_noeuds.begin(); iter != chemin_noeuds.end(); ++iter)
            cout << *iter << " ";
        cout << endl;
        for (list<string>::const_iterator iter = chemin_routes.begin(); iter != chemin_routes.end(); ++iter)
            cout << *iter << " ";
        cout << endl;
        cout << round(distance) << " m" << endl;
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
