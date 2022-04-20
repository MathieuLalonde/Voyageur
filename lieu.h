/*
   Classe Lieu/SegRoute
*/

#if !defined(__LIEU_H__)
#define __LIEU_H__

#include <iostream>
#include <list>
#include <string>

#include "coordonnee.h"
// TODO: inclure carte.h non? mais ca compile pas si on fait ca..

using namespace std;

/**
 * Represente un point sur la Carte
 */
class Lieu {
   public:
    Lieu();
    Lieu(string nom, Coordonnee coor);

    bool operator>(const Lieu& lieu) const;
    bool operator<(const Lieu& lieu) const;
    bool operator==(const Lieu& lieu) const;

   private:
    class SegRoute;

    string nom;
    Coordonnee coor;
    /** Liste de segment vers lesquels on peut se rendre a partir de se point */
    list<SegRoute> voisins;

    mutable bool isVisited = false;

    /** Represente un segment de route vers un autre Lieu */
    class SegRoute {
       public:
        SegRoute();
        SegRoute(const string nom, Lieu* depart, Lieu* arrivee);

        string nom;
        const Lieu* arrivee;
        double longueur;

       private:
    };

    friend class Carte;
};

#endif
