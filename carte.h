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

class Carte {
   public:
    void ajouterLieu(const string& nom, const Coordonnee& c);
    void ajouterRoute(const string& nom, const list<string>& noms);

    double calculerTrajet(const string& origine, const set<string>& destination,
                          list<string>& out_cheminnoeuds, list<string>& out_cheminroutes) const;
   private:
    map<string, Lieu> lieux;

    // A* selon pseudocode https://www.wikiwand.com/en/A*_search_algorithm
    double calculerCheminEntreDeuxLieux(const Lieu* nomOrigine,
                                        const Lieu* nomsDestinations,
                                        std::list<string>& out_cheminNoeuds,
                                        std::list<string>& out_cheminRoutes) const;

    void calculMeilleurTrajet(const Lieu* lieuOrigine,
                              const Lieu* lieuDepart,
                              map<const Lieu*, set<Trajet*>> trajetsPossibles,
                              list<Trajet*> trajetsParcourus,
                              double distanceParcourue,
                              int toursRetants,
                              list<Trajet*>& trajetsParcourMin,
                              double& distanceParcourMin) const;

    friend istream& operator>>(istream& is, Carte& carte);

    // Struct permetant d'initialiser un map a infini par defaut :
    struct Infini {
        double value = numeric_limits<double>::infinity();
    };
};

#endif
