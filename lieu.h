/*
   Classe Lieu/SegRoute
*/

#if !defined(__LIEU_H__)
#define __LIEU_H__

#include <iostream>
#include <list>
#include <string>

#include "coordonnee.h"

using namespace std;

class Lieu {
   public:
    //  Lieu();
    //  ~Lieu();

    class SegRoute;

    Coordonnee coor;
    list<SegRoute> voisins;

    // mutable bool isVisited = false;

    class SegRoute {
       public:
        SegRoute();
        SegRoute(const string nom, Lieu* depart, Lieu* arrivee);
        //   ~SegRoute();

        string nom;
        // Lieu* depart; // Utiliser au besoin...
        Lieu* arrivee;
        double longueur;

       private:
    };

   private:
};

#endif
