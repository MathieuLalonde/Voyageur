/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
    AUTEURS:
        David Genois GEND13119801
        Mathieu Lalonde LALM14127501
*/

#include <math.h>

#include <fstream>
#include <iostream>
#include <list>
#include <string>

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

        list<string> cheminNoeuds;
        list<string> cheminRoutes;
        string noeudPrecedent = "";
        double distance = carte.calculerTrajet(nomLieuAffaire, destinations, cheminNoeuds, cheminRoutes);

        for (list<string>::const_iterator iter = cheminNoeuds.begin(); iter != cheminNoeuds.end(); ++iter)
            if (noeudPrecedent != *iter) {
                cout << *iter << " ";
                noeudPrecedent = *iter;
            }
        cout << endl;
        for (list<string>::const_iterator iter = cheminRoutes.begin(); iter != cheminRoutes.end(); ++iter)
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
