/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#if !defined(__CARTE_H__)
#define __CARTE_H__

#include <assert.h>

#include <istream>
#include <limits>
#include <map>
#include <string>

#include "coordonnee.h"
#include "lieu.h"
#include "trajet.h"

using namespace std;

/**
 * Represente une carte donnee
 */
class Carte {
   public:
   /**
    * Ajoute un lieu/noeud a la carte
    * @param nom Le nom du lieu
    * @param c Ses coordonnees dans la carte
   */
    void ajouterLieu(const string& nom, const Coordonnee& c);
   /**
    * Ajoute une route a la carte.
    * Ceci est fait en creant les segments (<<entre-noeud>>) aux noeuds de la routes.
    * @param nom Le nom de la route
    * @param noms Les noms de noeuds qui sont sur cette route
   */
    void ajouterRoute(const string& nom, const list<string>& noms);

    double calculerTrajet(const string& origine, const set<string>& destination,
                          list<string>& out_cheminnoeuds, list<string>& out_cheminroutes) const;
   private:
    map<string, Lieu> lieux;

    /**
     * Cacul le chemin le plus rapide entre deux Lieu dans la carte.
     * En utilisant l'algorithm de parcours de graphe A*.
     * Notre code est une adaptation du pseudocode suivant: https://www.wikiwand.com/en/A*_search_algorithm
     *
     * @param origine-Lieu d'origine
     * @param destination-Lieu de destination
     * @param out_cheminNoeuds-La liste qui comprend tous les noeuds parcourus pour le resultat
     * @param out_cheminRoutes-La liste qui comprend tous les routes parcourus pour le resultat
    */
    double calculerCheminEntreDeuxLieux(const Lieu* origine,
                                        const Lieu* destination,
                                        std::list<string>& out_cheminNoeuds,
                                        std::list<string>& out_cheminRoutes) const;

    /**
     * Calcul le meilleur trajet pour une liste de destinations en partant d'un point de depart.
     * Cette fonction est recursive!
     *
     * @param lieuOrigine - Le lieu d'origine (lieu de fin/retour), ne change pas a travers les appels
     * @param lieuDepart - Lieu de depart pour la recursion courante
     * @param trajetsPossibles - Trajets possibles a partir du point courant
     * @param trajetsParcourus - Trajets parcourus jusqu'a maintenant
     * @param distanceParcourue - Distance parcourue jusqu'a maintenant
     * @param toursRetants - Destinations restantes a calculer (0=retour a l'origine)
     * @param trajetsParcourMin - Trajet du parcours optimal jusqu'a maintenant
     * @param distanceParcourMin - Distance totale optimale jusqu'a maintenant
     */
    void calculMeilleurTrajet(const Lieu* lieuOrigine,
                              const Lieu* lieuDepart,
                              map<const Lieu*, set<Trajet*>> trajetsPossibles,
                              list<Trajet*>& trajetsParcourus,
                              double distanceParcourue,
                              int toursRetants,
                              list<Trajet*>& trajetsParcourMin,
                              double& distanceParcourMin) const;

    friend istream& operator>>(istream& is, Carte& carte);

    /** Struct permetant d'initialiser un map a infini par defaut : */
    struct Infini {
        double value = numeric_limits<double>::infinity();
    };
};

#endif
