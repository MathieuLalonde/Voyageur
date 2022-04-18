/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#include "carte.h"

#include <limits.h>

#include <algorithm>
#include <queue>

#include "lieu.h"
#include "objetpq.h"

using namespace std;

void Carte::ajouterLieu(const string& nomLieu, const Coordonnee& c) {
    lieux[nomLieu] = Lieu(nomLieu, c);
}

// TODO: serait possible de stocker une route sous plusieurs tailles et que l'algo favorise le chemin le plus long qui mene plus loin en premier? Aussi, reduire la carte pour les noeuds qui on juste 1/2 liens (qui ne sont pas des intersections)
void Carte::ajouterRoute(const string& nomRoute, const list<string>& route) {
    list<string>::const_iterator iter = route.begin();

    Lieu* lieuDepart = &lieux[*iter];

    for (long unsigned int i = 1; i < route.size(); i++) {
        // Incremente la liste, trouve le lieu d'arrivee
        ++iter;
        Lieu* lieuArrivee = &lieux[*iter];

        // Ajoute le segment de route courrant et ses infos
        Lieu::SegRoute nouveauSegment(nomRoute, lieuDepart, lieuArrivee);
        lieuDepart->voisins.push_back(nouveauSegment);

        // Le lieu d'arrivee du segment courrant est le depart du prochain segment
        lieuDepart = lieuArrivee;
    }
}

// Prepare les estimes pour diriger les recherches
double Carte::calculerTrajet(const string& nomOrigine, const set<string>& destinationsUniques,
                             std::list<string>& out_cheminNoeuds, std::list<string>& out_cheminRoutes) const {
    // Cree tableau 2D de toutes les combinaisons de trajets:
    const Lieu* lieuOrigine = &(lieux.find(nomOrigine)->second);
    int tailleTableau = destinationsUniques.size() + 1;
    Trajet trajets[tailleTableau][tailleTableau];
    for (int i = 0; i < tailleTableau; i++) {
        trajets[0][i].depart = lieuOrigine;
        trajets[i][0].arrivee = lieuOrigine;
    }
    set<string>::const_iterator iter = destinationsUniques.begin();
    for (int i = 1; i < tailleTableau; i++) {
        const Lieu* lieuDestination = &(lieux.find(*iter)->second);
        for (int j = 0; j < tailleTableau; j++) {
            trajets[i][j].depart = lieuDestination;
            trajets[j][i].arrivee = lieuDestination;
        }
        iter++;
    }

    map<const Lieu*, set<Trajet*>> trajetsPossibles;

    // calcule toutes les distances a vol d'oiseau:
    for (int i = 0; i < tailleTableau; i++) {
        for (int j = i + 1; j < tailleTableau; j++) {
            if (i != j) {
                trajets[j][i].distanceEstimee = trajets[i][j].distanceEstimee =
                    trajets[i][j].depart->coor.distance(trajets[i][j].arrivee->coor);

                trajetsPossibles[trajets[i][j].depart].insert(&trajets[i][j]);
                trajetsPossibles[trajets[j][i].depart].insert(&trajets[j][i]);
            }
        }
    }
    list<Trajet*> trajetsParcourus;
    double distanceParcourue = 0;
    int toursRetants = destinationsUniques.size();
    list<Trajet*> trajetsParcourMin;
    double distanceParcourMin = numeric_limits<double>::infinity();

    // Calcule toutes les permutations avec ces chiffres-la:
    calculMeilleurTrajet(lieuOrigine, trajetsPossibles, trajetsParcourus, distanceParcourue, toursRetants,
                         trajetsParcourMin, distanceParcourMin);

    // Recupere et assemble les directives de parcours:
    string noeudPrecedent = "";
    string routePrecedente = "";
    for (Trajet* trajet : trajetsParcourMin) {
        for (string lieu : trajet->out_cheminNoeuds) {
            if (lieu != noeudPrecedent) {
                out_cheminNoeuds.push_back(lieu);
                noeudPrecedent = lieu;
            }
        }
        for (string route : trajet->out_cheminRoutes) {
            if (route != routePrecedente) {
                out_cheminRoutes.push_back(route);
                routePrecedente = route;
            }
        }
    }

    return distanceParcourMin;
}

// Calcul recursif des meilleurs combinaisons de trajets
void Carte::calculMeilleurTrajet(const Lieu* lieuDepart,
                                 map<const Lieu*, set<Trajet*>> trajetsPossibles,
                                 list<Trajet*> trajetsParcourus,
                                 double distanceParcourue,
                                 int toursRetants,
                                 list<Trajet*>& trajetsParcourMin,
                                 double& distanceParcourMin) const {
    if (toursRetants == 0) {
        const Lieu* origine = (*trajetsParcourus.begin())->depart;

        for (Trajet* voisin : trajetsPossibles[lieuDepart]) {
            if (voisin->arrivee == origine) {
                if (voisin->distanceReele < 0) {
                    voisin->distanceReele = calculerCheminEntreDeuxLieux(voisin->depart, voisin->arrivee,
                                                                         voisin->out_cheminNoeuds,
                                                                         voisin->out_cheminRoutes);
                }
                if (distanceParcourue + voisin->distanceReele < distanceParcourMin) {
                    trajetsParcourus.push_back(voisin);
                    distanceParcourue += voisin->distanceReele;

                    trajetsParcourMin = trajetsParcourus;
                    distanceParcourMin = distanceParcourue;
                }
                break;
            }
        }

    } else {
        // TODO: a tester
        for (Trajet* voisin : trajetsPossibles[lieuDepart]) {
            bool dejaVisite = false;
            for (Trajet* trajet : trajetsParcourus) {
                if (voisin->arrivee == trajet->arrivee || voisin->arrivee == trajet->depart) {
                    dejaVisite = true;
                    break;
                }
            }
            if (!dejaVisite) {
                if (voisin->distanceReele < 0) {
                    voisin->distanceReele = calculerCheminEntreDeuxLieux(voisin->depart, voisin->arrivee,
                                                                         voisin->out_cheminNoeuds,
                                                                         voisin->out_cheminRoutes);
                }
                list<Trajet*> nouvelleListe = trajetsParcourus;
                nouvelleListe.push_back(voisin);
                double nouvelleDistanceParcourue = distanceParcourue;
                nouvelleDistanceParcourue += voisin->distanceReele;

                if (distanceParcourue < distanceParcourMin) {
                    calculMeilleurTrajet(voisin->arrivee, trajetsPossibles, nouvelleListe, nouvelleDistanceParcourue,
                                         toursRetants - 1, trajetsParcourMin, distanceParcourMin);
                } else {
                    break;
                }
            }
        }
    }

    // retourne distance du parcoours minimum et son parcours
}

// Calcul trajet entre deux points sur les routes de la carte
double Carte::calculerCheminEntreDeuxLieux(const Lieu* origine, const Lieu* destination,
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

    // Traverse precedent pour retrouver le trajet utilise:
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
