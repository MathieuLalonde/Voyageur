/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#include "carte.h"

#include <queue>

#include "lieu.h"
#include "objetpq.h"

using namespace std;

void Carte::ajouterLieu(const string& nomLieu, const Coordonnee& c) {
    lieux[nomLieu] = Lieu(nomLieu, c);
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
    double distanceEstimee = origine->coor.distance(destination->coor);
    priority_queue<ObjetPQ, vector<ObjetPQ>, greater<ObjetPQ>> pq;
    pq.push(ObjetPQ(origine, distanceEstimee));

    const Lieu* lieuCourant = origine;
    // const Lieu* lieuPrecedent = origine;

    // Plus court chemin pour arriver a un Lieu donne:
    map<const Lieu*, const Lieu*> precedent;
    // Plus courte distance jusqu'a un Lieu donne:
    map<const Lieu*, Infini> gScore;
    // Estime de la meilleure distance vers la destination en passant par un Lieu donne:
    map<const Lieu*, Infini> fScore;

    gScore[lieuCourant].value = 0;

    list<Lieu::SegRoute>::const_iterator iter;
    // Tant que la destination n'est pas trouvee, trouve le meilleur chemin vers la destination:
    while (!pq.empty()) {
        lieuCourant = pq.top().lieu;

        // Retire le lieuCourant de la liste d'attente:
        pq.pop();

        // Boucle a travers tous les voisins:
        for (iter = lieuCourant->voisins.begin(); iter != lieuCourant->voisins.end(); ++iter) {
            Lieu::SegRoute segmentCourant = *iter;
            const Lieu* voisin = segmentCourant.arrivee;

            // Calcule les distances cumulative et estimee:
            double distanceCumul = gScore[lieuCourant].value + segmentCourant.longueur;
            if (distanceCumul < gScore[voisin].value) {
                // Ajoute nouvel objet dans la queue prioritaire s'il est nouveau ou meilleur qu'avant
                if (distanceCumul < gScore[voisin].value) {
                    pq.push(ObjetPQ(voisin, distanceEstimee));
                }

                precedent[voisin] = lieuCourant;
                gScore[voisin].value = distanceCumul;
                fScore[voisin].value = distanceCumul + segmentCourant.arrivee->coor.distance(destination->coor);
            }
        }
    }
    // TODO: Garde les distances mais pas les estimes et recommence avec les 13 autres destinations ??

    // TODO: Faire une fonction qui reconstruit le parcours a partir du map "precedent" et l'output dans
    // out_cheminNoeuds et out_cheminRoutes.

    cout << gScore[destination].value << " m" << endl;

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
