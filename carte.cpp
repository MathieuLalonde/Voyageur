/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#include "carte.h"

#include <limits>
#include <queue>

#include "lieu.h"
#include "objetpq.h"

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
    const Lieu* lieuDepart = &(lieux.find(nomOrigine)->second);

    for (const string i : nomsDestinations) {
        // double meilleureDistance = numeric_limits<double>::infinity();
        const Lieu* lieuDest = &(lieux.find(i)->second);
        list<string> out_cheminNoeuds, out_cheminRoutes;

        calculerTrajetEntreDeuxLieux(lieuDepart, lieuDest, out_cheminNoeuds, out_cheminRoutes);
        calculerTrajetEntreDeuxLieux(lieuDest, lieuDepart, out_cheminNoeuds, out_cheminRoutes);

        /*
        // (Version de la structure de base, à tritre d'exemple...)
        string position = nomOrigine;
        double total = 0;

        for (list<string>::const_reverse_iterator iter = nomsDestinations.rbegin(); iter != nomsDestinations.rend(); ++iter) {
            total += calculerChemin(*iter, position, out_cheminNoeuds, out_cheminRoutes);
            position = *iter;
        }

        total += calculerChemin(nomOrigine, position, out_cheminNoeuds, out_cheminRoutes);
        cout << total << endl;
        return total;
        */
    }
    return 0;
}

/*
double Carte::calculerChemin(const string& nomOrigine, const string& nomDestination,
                             std::list<string>& out_cheminNoeuds, std::list<string>& out_cheminRoutes) const {
    // À compléter.
    return numeric_limits<double>::infinity();
}
*/

double Carte::calculerTrajetEntreDeuxLieux(const Lieu* origine, const Lieu* destination,
                                           std::list<string>& out_cheminNoeuds,
                                           std::list<string>& out_cheminRoutes) const {
    // double meilleureDistance = numeric_limits<double>::infinity();
    priority_queue<ObjetPQ, vector<ObjetPQ>, greater<ObjetPQ>> pq;
    double distanceEstimee = origine->coor.distance(destination->coor);
    pq.push(ObjetPQ(origine, 0, distanceEstimee));

    // Lieu* lieuDepart = &(lieux.find(nomOrigine)->second);
    // Lieu* lieuDest = lieux.find(nomsDestination)->second;
    const Lieu* lieuCourant = origine;

    list<Lieu::SegRoute>::const_iterator iter;
    // Tant que la destination n'est pas trouvee, trouve le meilleur chemin vers la destination:
    while (lieuCourant != destination) {
        lieuCourant = pq.top().lieu;
        // Boucle a travers tous les voisins:
        for (iter = lieuCourant->voisins.begin(); iter != lieuCourant->voisins.end(); ++iter) {
            Lieu::SegRoute segmentCourant = *iter;

            // TODO: Pourrait l'empècher de retourner sur ses pas avant calculer la distance.
            // Si lieu précéendent == segmentCourant.arrivee...

            double distCumul = pq.top().distanceCumul + segmentCourant.longueur;
            double distanceEstimee = distCumul + segmentCourant.arrivee->coor.distance(destination->coor);

            // Ajoute nouvel objet dans la queue prioritaire
            pq.push(ObjetPQ(segmentCourant.arrivee, distCumul, distanceEstimee));
            // cout << "Voisins : " << segmentCourant.nom << " = " << distCumul << endl;  // Pour tester
        }
        // retire le lieuCourant maintenant que tous ses voisins ont ete visites
        cout << "While : " << pq.top().distanceCumul << endl;  // Pour tester
        pq.pop();
    }
    // garde les distances mais pas les estimes et recommence avec autres destinations ?

    // cout << "Distance : " << test << endl;  // Pour tester

    return 0;
}

/* Lire une carte. */
istream&
operator>>(istream& is, Carte& carte) {
    // Lire les lieux
    while (is) {
        string nomLieu;
        is >> nomLieu;
        if (nomLieu == "---") break;
        Coordonnee coor;
        is >> coor;
        carte.ajouterLieu(nomLieu, coor);
        cout << "Lieu ajouté : " << nomLieu << endl;  // Pour tester
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
        cout << "Route ajoutée : " << nomRoute << endl;  // Pour tester
    }

    return is;
}
