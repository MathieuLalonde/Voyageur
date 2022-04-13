/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#include "carte.h"

#include <algorithm>
#include <queue>
#include <limits.h>

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
        Lieu::SegRoute ajout(nomRoute, lieuDepart, lieuArrivee);
        lieuDepart->voisins.push_back(ajout);

        // Le lieu d'arrivee du segment courrant est le depart du prochain segment
        lieuDepart = lieuArrivee;
    }
}

// TODO: fix un cas qui marche pas
double Carte::calculerTrajet(const string& nomOrigine, const list<string>& nomsDestinations,
                             std::list<string>& out_cheminNoeuds, std::list<string>& out_cheminRoutes,
                            double distanceOptimalCourante) const {
    const Lieu* lieuDepart = &(lieux.find(nomOrigine)->second);
    const Lieu* lieuPrecedent = lieuDepart;

    double distanceTotale = 0;

    for (const string nomDestination : nomsDestinations) {
        if(std::find(out_cheminNoeuds.begin(), out_cheminNoeuds.end(), nomDestination) != out_cheminNoeuds.end())
            continue;

        const Lieu* lieuDest = &(lieux.find(nomDestination)->second);
        double distanceAller = 0;

        distanceAller = calculerTrajetEntreDeuxLieux(lieuDest, lieuPrecedent, out_cheminNoeuds, out_cheminRoutes);

        distanceTotale += distanceAller;
        lieuPrecedent = lieuDest;

        if (distanceOptimalCourante < distanceTotale)
            return std::numeric_limits<double>::max();
    }

    double distanceRetour = calculerTrajetEntreDeuxLieux(lieuDepart, lieuPrecedent, out_cheminNoeuds, out_cheminRoutes);
    distanceTotale += distanceRetour;

    return distanceTotale;
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
    map<const Lieu*, const Lieu::SegRoute*> routePrecedente;
    // Plus courte distance jusqu'a un Lieu donne:
    map<const Lieu*, Infini> gScore;
    // Estime de la meilleure distance vers la destination en passant par un Lieu donne:
    map<const Lieu*, Infini> fScore;

    gScore[lieuCourant].value = 0;

    list<Lieu::SegRoute>::const_iterator iter;
    // Tant qu'il y a des Lieux dans la queue, trouve le meilleur chemin vers la destination:
    while (!pq.empty()) {
        lieuCourant = pq.top().lieu;

        // Retire le lieuCourant de la queue prioritaire:
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
                routePrecedente[voisin] = &(*iter);
                gScore[voisin].value = distanceCumul;
                fScore[voisin].value = distanceCumul + segmentCourant.arrivee->coor.distance(destination->coor);
            }
        }
    }
    // TODO: Recommence avec les 13 autres destinations ??

    // TODO: Sortir ca en fonction ? :

    const Lieu* traceRoute = destination;
    out_cheminNoeuds.push_front(destination->nom);
    while (traceRoute != origine) {
        out_cheminNoeuds.push_front(precedent[traceRoute]->nom);

        string routeActuelle = routePrecedente[traceRoute]->nom;
        if (routeActuelle != *out_cheminRoutes.begin()) {
            out_cheminRoutes.push_front(routePrecedente[traceRoute]->nom);
        }
        traceRoute = precedent[traceRoute];
    }

    return gScore[destination].value;
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
