/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2022
 *  Squelette pour le TP3
 */

#ifndef CARTE_HEADER
#define CARTE_HEADER

#include <assert.h>

#include <istream>
#include <map>
#include <string>

#include "coordonnee.h"
#include "lieu.h"

using namespace std;

class Carte {
   public:
    // À compléter (vous pouvez tout changer).
    void ajouterLieu(const string& nom, const Coordonnee& c);
    void ajouterRoute(const string& nom, const list<string>& noms);

    double calculerTrajet(const string& origine, const list<string>& destination,
                          list<string>& out_cheminnoeuds, list<string>& out_cheminroutes) const;
    double calculerChemin(const string& origine, const string& destination,
                          list<string>& out_cheminnoeuds, list<string>& out_cheminroutes) const;

   private:
    map<string, Lieu> lieux;

    friend istream& operator>>(istream& is, Carte& carte);
    // friend class ObjetPQ;
};

#endif
