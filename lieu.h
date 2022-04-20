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
    list<SegRoute> voisins;

    mutable bool isVisited = false;

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
