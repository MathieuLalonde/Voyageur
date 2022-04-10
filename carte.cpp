/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#include "carte.h"

#include <limits>

#include "lieu.h"

using namespace std;

void Carte::ajouterLieu(const string& nomLieu, const Coordonnee& c) {
    lieux[nomLieu].coor = c;
}

void Carte::ajouterRoute(const string& nomRoute, const list<string>& route) {
    list<string>::const_iterator iter = route.begin();

    Lieu* lieuDepart = &lieux[*iter];

    for (long unsigned int i = 1; i < route.size(); i++) {
        // Incremente la liste, trouve le lieu d'arrivee
        ++iter;
        Lieu* lieuArrivee = &lieux[*iter];

        // Ajoute le segment de route courrant et ses infos
        // TODO: C'est un peu bizard ici, je crois que c'est fait par copie...?
        Lieu::SegRoute ajout(nomRoute, lieuDepart, lieuArrivee);
        lieuDepart->voisins.push_back(ajout);

        // Le lieu d'arrivee du segment courrant est le depart du prochain segment
        lieuDepart = lieuArrivee;
    }
}

double Carte::calculerTrajet(const string& nomOrigine, const list<string>& nomsDestinations,
                             std::list<string>& out_cheminNoeuds, std::list<string>& out_cheminRoutes) const {
    // À compléter.
    // La version actuelle génère un trajet valide, mais généralement non optimal pour plusieurs destinations.
    string position = nomOrigine;
    double total = 0;

    for (list<string>::const_reverse_iterator iter = nomsDestinations.rbegin(); iter != nomsDestinations.rend(); ++iter) {
        total += calculerChemin(*iter, position, out_cheminNoeuds, out_cheminRoutes);
        position = *iter;
    }

    total += calculerChemin(nomOrigine, position, out_cheminNoeuds, out_cheminRoutes);
    cout << total << endl;
    return total;
}

double Carte::calculerChemin(const string& nomOrigine, const string& nomDestination,
                             std::list<string>& out_cheminNoeuds, std::list<string>& out_cheminRoutes) const {
    // À compléter.
    return numeric_limits<double>::infinity();
}

/* Lire une carte. */
istream& operator>>(istream& is, Carte& carte) {
    // Lire les lieux
    while (is) {
        string nomLieu;
        is >> nomLieu;
        if (nomLieu == "---") break;
        Coordonnee coor;
        is >> coor;
        carte.ajouterLieu(nomLieu, coor);
    }

    // Lire les routes
    while (is) {
        string nomRoute;
        is >> nomRoute;
        if (nomRoute == "---" || nomRoute == "" || !is) break;

        char deuxpoints;
        is >> deuxpoints;
        assert(deuxpoints == ':');

        list<string> listeNomslieux;

        string nomLieu;
        while (is) {
            is >> nomLieu;
            if (nomLieu == ";") break;
            assert(nomLieu != ":");
            assert(nomLieu.find(";") == string::npos);
            listeNomslieux.push_back(nomLieu);
        }

        assert(nomLieu == ";");
        carte.ajouterRoute(nomRoute, listeNomslieux);
    }

    return is;
}
