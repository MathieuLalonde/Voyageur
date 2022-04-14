/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#ifndef CARTE_HEADER
#define CARTE_HEADER

#include <assert.h>

#include <istream>
#include <limits>
#include <map>
#include <string>

#include "coordonnee.h"
#include "lieu.h"

using namespace std;

class Carte {
   public:
    void ajouterLieu(const string& nom, const Coordonnee& c);
    void ajouterRoute(const string& nom, const list<string>& noms);

    double calculerTrajet(const string& origine, const list<string>& destination,
                          list<string>& out_cheminnoeuds, list<string>& out_cheminroutes,
                          double distanceOptimalCourante) const;
    double calculerChemin(const string& origine, const string& destination,
                          list<string>& out_cheminnoeuds, list<string>& out_cheminroutes) const;

   private:
    map<string, Lieu> lieux;

    // Memoized output of calculerTrajetEntreDeuxLieux
    // mutable map<const Lieu*, map<const Lieu*, double>> memoDistances;
    // mutable map<const Lieu*, map<const Lieu*, std::list<string>>> memoNoeuds;
    // mutable map<const Lieu*, map<const Lieu*, std::list<string>>> memoRoutes;

    // A* selon pseudocode https://www.wikiwand.com/en/A*_search_algorithm
    double calculerTrajetEntreDeuxLieux(const Lieu* nomOrigine,
                                        const Lieu* nomsDestinations,
                                        std::list<string>& out_cheminNoeuds,
                                        std::list<string>& out_cheminRoutes) const;

    friend istream& operator>>(istream& is, Carte& carte);

    // Struct permetant d'initialiser un map a infini par defaut :
    struct Infini {
        double value = numeric_limits<double>::infinity();
    };
};

#endif
